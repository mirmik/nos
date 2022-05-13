import licant

licant.module("nos.osutil", "unix", default=sys.platform=="linux",
	sources = [
		"nos/util/osutil_unix.cpp"
	]
)

licant.module("nos.osutil", "windows", default=sys.platform=="win32",
	sources = [
		"nos/util/osutil_windows.cpp"
	]
)

licant.module("nos.util",
	srcdir="nos/util", 
	sources=[
		"trace.cpp",
		"nos_numconvert.cpp"
	],
	mdepends=["nos.osutil"]
)

licant.module("nos.io",
	srcdir="nos/io", 
	sources=[
		"istream.cpp",
		"ostream.cpp"
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.log",
	srcdir="nos/log", 
	sources=[
		"level.cpp",
		"tlogger.cpp",
		"target.cpp",
		"targets/stdout.cpp",
		"targets/tcpspam.cpp",
	]
)

licant.module("nos.serial_port",
	sources=["nos/io/serial_port.cpp"] if sys.platform!="win32" else []
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
		"stdtype.cpp",
		"trent.cpp",
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

licant.module("nos.input_timeout", "posix", sources=[ "nos/input/input-timeout-posix.cpp", ], default=True)

licant.module("nos.fprint",
	srcdir="nos/fprint", 
	sources=[
		"fprint.cpp",
		"fstdtype.cpp",
	],
	mdepends=["nos.current_ostream"]
)

licant.module("nos.current_ostream", impl="stdout", 
	sources=["nos/io/impls/current_ostream_stdout.cpp", "nos/io/stdfile.cpp"],
	mdepends = ["nos.io"],
	default = True
)

licant.module("nos.current_ostream", impl="nullptr", 
	sources=["nos/io/impls/current_ostream_nullptr.cpp"],
	mdepends = ["nos.io"]
)


#licant.module("nos.printf", sources=["nos/util/printf_impl.c"])

licant.module("nos.error", impl="throw", sources=["nos/util/error_throw.cpp"])
licant.module("nos.error", impl="abort", sources=["nos/util/error_abort.cpp"])
licant.module_defimpl("nos.error", "throw")

licant.module("nos",
	mdepends=[
		"nos.util",
		"nos.print",
		"nos.input",
		"nos.input_timeout",
		"nos.fprint",
		"nos.io",
		"nos.log",
		"nos.timestamp",
		"nos.serial_port",
		"nos.current_ostream",
	],
	include_paths=["."]
)

licant.module("nos.include",
	include_paths=["."]
)

licant.module("nos.timestamp", "undefined", sources=["nos/util/timestamp-undefined.cpp"], default=True)
licant.module("nos.timestamp", "millis", sources=["nos/util/timestamp-millis.cpp"])
