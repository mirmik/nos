#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../nos.g.py")

tests = [
	"print",
	"fprint",
	"trace",
	"log",
]

application("runtests",
	sources = ["main.cpp"],

	ld_flags = "-L/usr/local/lib/",

	include_paths = ["."],
	mdepends = [
		"nos"
	],

	libs = ["igris"]
)

licant.ex("runtests")