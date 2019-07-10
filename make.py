#!/usr/bin/env python3
#coding: utf-8

import licant
import shutil
import os

version = "1.0.0"

licant.execute("nos.g.py")
#licant.include("igris")

target = "libnos.{}.so".format(version)
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

	cxx_flags = '-fPIC',
	cc_flags = '-fPIC',
)

@licant.routine(deps=[target])
def install():
	os.system("cp {0} {1}".format(target, install_directory_path))
	os.system("rm {}".format(install_library_link))
	os.system("ln -s {0} {1}".format(install_library_path, install_library_link))

	shutil.rmtree(install_include_path, True)
	shutil.copytree("nos", install_include_path, 
		symlinks=False, ignore=shutil.ignore_patterns('*.cpp', '*.c'))
	
	print("successfully installed")
	
licant.ex(target)