#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../nos.g.py")

application("runtests",
            sources=["*.cpp"],
            ld_flags="-L/usr/local/lib/",
            include_paths=["."],
            mdepends=["nos", "nos.shell.standart", "nos.inet"],

            cxxstd="c++2a -Weffc++",
            ccstd="c11",
            cxx_flags="-g -O0 -Werror=all -Werror=pedantic -Wno-gnu-zero-variadic-macro-arguments",
            cc_flags="-g -O0 -Werror=all -Werror=pedantic -Wno-gnu-zero-variadic-macro-arguments",
            libs=["pthread"],
            )

licant.ex("runtests")
