# Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
# License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

####################################################################################################
## WARNING: The code is auto-generated. Any changes will be overwritten.
####################################################################################################

import sys

def event1(header, values):
  print(header, " event1"
  , ", param1:", values[1]
  , ", param2:", values[2]
  , sep='')

def event2(header, values):
  print(header, " event2"
  , ", param1:", values[1]
  , ", param2:", values[2]
  , sep='')

def event3(header, values):
  print(header, " event3"
  , ", p1:", values[1]
  , ", p2:", values[2]
  , ", p3:", values[3]
  , ", p4:", values[4]
  , ", p5:", values[5]
  , sep='')

def event4(header, values):
  print(header, " event4"
  , ", u8:", values[1]
  , ", d64:", values[2]
  , ", u16:", values[3]
  , ", d32:", values[4]
  , ", u32:", values[5]
  , ", d16:", values[6]
  , ", u64:", values[7]
  , ", d8:", values[8]
  , ", dbl:", values[9]
  , ", str:", values[10]
  , ", hx:", values[11]
  , ", hx2:", values[12]
  , sep='')


####################################################################################################

if (len(sys.argv) == 1):
  events_in = sys.stdin
else:
  events_in = open(sys.argv[1])

for event in events_in:
  tokens = event.split()
  values = tokens[3].split(",")

  if values[0] == "1":
    event1(" ".join(tokens[0:3]), values)
  elif values[0] == "2":
    event2(" ".join(tokens[0:3]), values)
  elif values[0] == "3":
    event3(" ".join(tokens[0:3]), values)
  elif values[0] == "4":
    event4(" ".join(tokens[0:3]), values)
  
