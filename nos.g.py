import licant

licant.execute("nos/dprint/dprint.g.py")

licant.module("nos.util",
	srcdir="nos/util", 
	sources=[
		"printf_impl.c",
		"numconvert.c",
		"hexascii.cpp",
		"trace.cpp"
	]
)

licant.module("nos.io",
	srcdir="nos/io", 
	sources=[
		"ostream.cpp"
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.print",
	srcdir="nos/print", 
	sources=[
		"print.cpp",
		"stdtype.cpp"
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.fprint",
	srcdir="nos/fprint", 
	sources=[
		"fprint.cpp"
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.current_ostream", "cout",
	sources=["nos/io/current_ostream_cout.cpp", "nos/io/std.cpp"]
)

licant.module("nos.current_ostream", "nullptr",
	sources=["nos/io/current_ostream_nullptr.cpp"]
)

licant.module_defimpl("nos.current_ostream", "cout")

licant.module("nos",
	sources = ["nos/panic.cpp"],
	mdepends=[
		"nos.io",
		"nos.util",
		"nos.dprint",
		"nos.print",
		"nos.fprint",
	],
	include_paths=["."]
)

licant.module("nos.include",
	include_paths=["."]
)