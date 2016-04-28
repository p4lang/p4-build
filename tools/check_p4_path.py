#!/usr/bin/env python

import os
import sys

if os.path.isabs(sys.argv[1]) and os.path.isfile(sys.argv[1]):
    print "yes"
else:
    print "no"
