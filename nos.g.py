import licant

licant.module("nos.util",
	srcdir="nos/util", 
	sources=[
		"numconvert.c",
		"error.cpp",
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
		"fprint.cpp",
		"stdtype.cpp",
	],
	mdepends=["nos.current_ostream"]
)

licant.implementation("nos.current_ostream", "stdout",
	sources=["nos/io/current_ostream_cout.cpp", "nos/io/std.cpp"]
)

licant.implementation("nos.current_ostream", "nullptr",
	sources=["nos/io/current_ostream_nullptr.cpp"]
)

licant.module("nos.printf",
	sources=["nos/util/printf_impl.c"]
)

licant.module("nos.dprint.common", "impl", 
	srcdir="nos/dprint",
	sources=["dprint_func_impl.c", "dprintxx.cpp"],
	mdepends=["nos.printf"]
)

licant.implementation("nos.dprint", "stub", 
	srcdir="nos/dprint",
	sources = "dprint_func_stub.c dprint_stub.c dprintxx.cpp".split(" ")
)

#licant.implementation("nos.dprint", "diag", 
#	sources = "dprint_func_impl.c dprint_diag.c dprintxx.cpp".split(" "),
#	cc_flags = "-Wno-pointer-to-int-cast",
#	mdepends = [
#		"gxx.diag",
#		("nos.dprint.common", "impl")
#	],
#)

licant.implementation("nos.dprint", "manually", 
	srcdir="nos/dprint",
	sources = ["dprint_manually.c"],
	mdepends = [("nos.dprint.common","impl")],
)

licant.implementation("nos.dprint", "stdout",
	srcdir="nos/dprint",
	sources = ["dprint_stdout.c"],
	mdepends = [("nos.dprint.common","impl")],
)

licant.module_defimpl("nos.current_ostream", "stdout")
licant.module_defimpl("nos.dprint", "stdout")

licant.module("nos",
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