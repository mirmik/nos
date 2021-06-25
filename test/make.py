#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../nos.g.py")

application("runtests",
	sources = [ "*.cpp" ],
	ld_flags = "-L/usr/local/lib/",
	include_paths = ["."],
	mdepends = [ "nos" ]
)

licant.ex("runtests")
