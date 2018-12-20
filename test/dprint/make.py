#!/usr/bin/env python3
#coding: utf-8

import sys
import licant

licant.execute("../../nos.g.py")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=["nos"],
	cxx_flags="-Werror=all -Werror=extra -pedantic-errors"
)

licant.ex("target")