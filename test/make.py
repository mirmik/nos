#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../nos.g.py")

application("runtests",
	sources = [
		"main.cpp",
		"print.cpp",
		"fprint.cpp",
		"trace.cpp",
		"log.cpp",
		"circular_rectangle.cpp"
	],

	ld_flags = "-L/usr/local/lib/",

	include_paths = ["."],
	mdepends = [
		"nos",
	],
	libs=["igris"],
)

licant.ex("runtests")
