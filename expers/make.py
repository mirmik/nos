#!/usr/bin/env python3
#coding: utf-8

import licant

licant.include("nos")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=[
		"nos",
	],	
)

licant.ex("target")