#!/usr/bin/env python

import filecmp
import sys

if not filecmp.cmp(sys.argv[1], sys.argv[2]):
    print "yes"
else:
    print "no"
