#!/usr/bin/env python

import cpp
import sys

if len(sys.argv) == 1 :
  print cpp.random_table()
elif len(sys.argv) == 2 :
  print cpp.decode(sys.argv[1])
else :
  print cpp.encode(sys.argv[1], sys.argv[2])
