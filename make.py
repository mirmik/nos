#!/usr/bin/env python3
#coding: utf-8

import licant
import licant.install
import shutil
import os
import sys

licant.execute("nos.g.py")

target = "libnos.so"
install_include_path = '/usr/include/nos' 
install_directory_path = '/usr/lib/'
install_library_path = os.path.join(install_directory_path, target) 
install_library_link = os.path.join(install_directory_path, 'libnos.so')

licant.cxx_static_and_shared("libraries",
	static_lib="libnos.a",
	shared_lib="libnos.so",
	mdepends = 
	[
		"nos",
		"nos.inet",
		"nos.input",
		"nos.shell.standart",
	],
	cxx_flags = '-fPIC -Weffc++ -Wall -Wextra',
	cc_flags = '-fPIC',
	libs=["ws2_32"] if sys.platform=="win32" else [],
)

licant.cxx_application("runtests",
            sources=["tests/*.cpp"],
            ld_flags="-L/usr/local/lib/",
            include_paths=["tests/."],
            mdepends=["nos", "nos.shell.standart", "nos.inet"],
            cxxstd="c++2a -Weffc++",
            ccstd="c11",
            cxx_flags="-g -O0 -Werror=all -Werror=pedantic -Wno-gnu-zero-variadic-macro-arguments",
            cc_flags="-g -O0 -Werror=all -Werror=pedantic -Wno-gnu-zero-variadic-macro-arguments",
            libs=["pthread"],
            )

licant.install.install_library(	tgt="install", 
								libtgt=["libnos.a", "libnos.so"], 
								headers="nos", 
								hroot="nos")
	
licant.fileset("all", targets=["runtests", "libnos.a", "libnos.so"])

licant.ex("all")
