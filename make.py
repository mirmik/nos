#!/usr/bin/env python3
#coding: utf-8

import licant
import licant.install
import shutil
import os

licant.execute("nos.g.py")

target = "libnos.so"
install_include_path = '/usr/include/nos' 
install_directory_path = '/usr/lib/'
install_library_path = os.path.join(install_directory_path, target) 
install_library_link = os.path.join(install_directory_path, 'libnos.so')

licant.cxx_shared_library(target,
	mdepends = 
	[
		"nos",
		"nos.inet",
		"nos.input",
	],

	cxx_flags = '-fPIC -Weffc++',
	cc_flags = '-fPIC',
)

licant.install.install_library(tgt="install", libtgt=target, headers="nos", hroot="nos")
	
licant.ex(target)
