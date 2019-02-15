import licant

licant.module("nos.util",
	srcdir="nos/util", 
	sources=[
		"numconvert.c",
		"trace.cpp",
		"osutil.cpp",
		"string.cpp"
	]
)

licant.module("nos.io",
	srcdir="nos/io", 
	sources=[
		"ostream.cpp"
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.inet",
	srcdir="nos/inet", 
	sources=[
		"common.cpp",
		"tcp_server.cpp",
		"tcp_socket.cpp"
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

licant.module("nos.input",
	srcdir="nos/input", 
	sources=[
		"input.cpp",
	],
	mdepends = ["nos.util"]
)

licant.module("nos.fprint",
	srcdir="nos/fprint", 
	sources=[
		"fprint.cpp",
		"stdtype.cpp",
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.current_ostream", impl="stdout", sources=["nos/io/current_ostream_stdout.cpp", "nos/io/stdfile.cpp"])
licant.module("nos.current_ostream", impl="nullptr", sources=["nos/io/current_ostream_nullptr.cpp"])
licant.module_defimpl("nos.current_ostream", "stdout")

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

licant.module("nos.bugon", impl="abort", sources=["nos/util/bugon_abort.c"], mdepends=["nos.dprint"])
licant.module("nos.bugon", impl="error", sources=["nos/util/bugon_error.cpp"], mdepends=["nos.error"])
licant.module_defimpl("nos.bugon", "abort")

licant.module("nos.error", impl="throw", sources=["nos/util/error_throw.cpp"])
licant.module("nos.error", impl="abort", sources=["nos/util/error_abort.cpp"])
licant.module_defimpl("nos.error", "throw")

licant.module_defimpl("nos.dprint", "stdout")

licant.module("nos",
	mdepends=[
		"nos.util",
		"nos.dprint",
		"nos.print",
		"nos.input",
		"nos.fprint",
		"nos.bugon",
		"nos.io",
#		"nos.inet",
	],
	include_paths=["."]
)

licant.module("nos.include",
	include_paths=["."]
)

licant.module("nos.trent", sources=[
	"nos/trent/trent.cpp",
	"nos/trent/json.cpp"
])
