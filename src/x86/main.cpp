// Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL v3

// SYSTEM INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <memory>
#include <sys/stat.h>

#ifdef HAVE_SYS_TIME_H
    #include <sys/time.h>
#endif

#ifdef WIN32
    #include <CTPP2Time.h>
#endif

#include <CTPP2JSONFileParser.hpp>
#include <CTPP2FileOutputCollector.hpp>
#include <CTPP2FileLogger.hpp>
#include <CTPP2SyscallFactory.hpp>
#include <CTPP2VMDebugInfo.hpp>
#include <CTPP2VM.hpp>
#include <CTPP2VMFileLoader.hpp>
#include <CTPP2VMSTDLib.hpp>
#include <CTPP2VMStackException.hpp>
#include <CTPP2GetText.hpp>

// PROJECT INCLUDES
#include "count.hpp"
#include "format_spec.hpp"
#include "type_mapper.hpp"

using namespace CTPP;

void error(const char *format, ...)
{
  va_list argList;
  fflush(stdout); // Flush any pending stdout
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  fflush(stderr);
  exit(EXIT_FAILURE);
}

void is_file(char* file)
{
  struct stat file_stat;

  if (stat(file, &file_stat) == -1 || file_stat.st_size == 0) {
    error("Input: unable to get size of %s\n", file);
  }
}

int main(int argc, char** argv)
{
  if (argc < 3) {
    error("Usage: %s template_file model_file [output_file | 0] [translation_file | 0] "
        "[limit of steps]\n", argv[0]);
  }

  is_file(argv[1]);
  is_file(argv[2]);

  SyscallFactory syscall_factory(100);
  btr::log::Count count;
  syscall_factory.RegisterHandler(&count);
  btr::log::FormatSpec pf;
  syscall_factory.RegisterHandler(&pf);
  btr::log::TypeMapper tm;
  syscall_factory.RegisterHandler(&tm);

  STDLibInitializer::InitLibrary(syscall_factory);

  // Set up output
  std::unique_ptr<FileOutputCollector> output;

  if (argc >= 4 && strncmp(argv[3], "0", strlen(argv[3])) != 0) {
    output.reset(new FileOutputCollector(argv[3], "w+"));
  } else {
    output.reset(new FileOutputCollector(stdout));
  }

  // Set up translation
  CTPP2GetText get_text;

  if (argc >= 5 && strncmp(argv[4], "0", strlen(argv[4])) != 0) {
    is_file(argv[4]);
    get_text.AddTranslation(argv[4], "tran", "unknown");
  }

  get_text.InitSTDLibFunction(syscall_factory);
  get_text.SetLanguage(syscall_factory, "unknown");
  get_text.SetDefaultDomain("tran");

  // Set up steps limit
  UINT_32 steps_limit = 10240;

  if (argc == 6) {
    steps_limit = atoi(argv[5]);
  }

  int rc = -1;

  try {
    VMFileLoader tmpl_loader(argv[1]);
    const VMMemoryCore* mem_core = tmpl_loader.GetCore();

    CDT model(CDT::HASH_VAL);
    CTPP2JSONFileParser json_model_parser(model);
    json_model_parser.Parse(argv[2]);

    // Factory, maxArgStackSize, maxCodeStackSize, maxSteps, debugLevel
    VM vm(&syscall_factory, 10240, 10240, steps_limit, 0);

    FileLogger logger(stderr);
    UINT_32 instr_pointer = 0;
    vm.Init(mem_core, output.get(), &logger);
    vm.Run(mem_core, output.get(), instr_pointer, model, &logger);
    rc = 0;
  } catch (const CDTTypeCastException& e) {
    fprintf(stderr, "ERROR: Type Cast %s\n", e.what());
  } catch (const CDTAccessException& e) {
    fprintf(stderr, "ERROR: Array index out of bounds: %s\n", e.what());
  } catch (const IllegalOpcode& e) {
    fprintf(stderr, "ERROR: Illegal opcode 0x%08X at 0x%08X\n", e.GetOpcode(), e.GetIP());
  } catch (const InvalidSyscall& e) {
    if (e.GetIP() != 0) {
      VMDebugInfo oVMDebugInfo(e.GetDebugInfo());

      fprintf(stderr, "ERROR: %s at 0x%08X (Template file \"%s\", Line %d, Pos %d)\n",
          e.what(), e.GetIP(), e.GetSourceName(), oVMDebugInfo.GetLine(), oVMDebugInfo.GetLinePos());
    } else {
      fprintf(stderr, "Unsupported syscall: \"%s\"\n", e.what());
    }
  } catch (const InvalidCall& e) {
    VMDebugInfo oVMDebugInfo(e.GetDebugInfo());

    fprintf(stderr, "ERROR: at 0x%08X: Invalid block name \"%s\" in file \"%s\", Line %d, Pos %d\n",
        e.GetIP(), e.what(), e.GetSourceName(), oVMDebugInfo.GetLine(), oVMDebugInfo.GetLinePos());
  } catch (const CodeSegmentOverrun& e) {
    fprintf(stderr, "ERROR: %s at 0x%08X\n", e.what(),  e.GetIP());
  } catch (const StackOverflow& e) {
    fprintf(stderr, "ERROR: Stack overflow at 0x%08X\n", e.GetIP());
  } catch (const StackUnderflow& e) {
    fprintf(stderr, "ERROR: Stack underflow at 0x%08X\n", e.GetIP());
  } catch (const ExecutionLimitReached& e) {
    fprintf(stderr,
        "ERROR: Execution limit of %d step(s) reached at 0x%08X\n", steps_limit, e.GetIP());
  } catch (const VMException& e) {
    fprintf(stderr, "ERROR: VM generic exception: %s at 0x%08X\n", e.what(), e.GetIP());
  } catch (const CTPPLogicError& e) {
    fprintf(stderr, "ERROR: %s\n", e.what());
  } catch (const CTPPUnixException& e) {
    fprintf(stderr, "ERROR: I/O in %s: %s\n", e.what(), strerror(e.ErrNo()));
  } catch (const CTPPException& e) {
    fprintf(stderr, "ERROR: CTPP Generic exception: %s\n", e.what());
  }

  STDLibInitializer::DestroyLibrary(syscall_factory);

  // make valgrind happy
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);
  return rc;
}
