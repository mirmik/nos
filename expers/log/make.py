#!/usr/bin/env python3
#coding: utf-8

import licant

licant.include("igris")
licant.include("nos")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=[
		"nos",
		"igris",
	],	
#	cxxstd = "c++17"
)

licant.ex("target")
