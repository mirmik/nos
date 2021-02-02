cmake_minimum_required(VERSION 3.5.1)
project(nos)
set( CMAKE_VERBOSE_MAKEFILE on )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CC_STANDARD 11)

set (PLATFORM_SOURCES )

if (WIN32 OR WIN64)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
endif()

file(GLOB HEADERS 
	nos/*.h
	nos/**/*.h	
)

file(GLOB SOURCES 
	nos/print/*.cpp	
	nos/fprint/*.cpp
	
	nos/util/osutil.cpp
	nos/util/trace.cpp

	nos/meta/*.cpp
	nos/log/*.cpp
	nos/inet/*.cpp

	nos/io/*.cpp
	nos/io/impls/current_ostream_stdout.cpp

	nos/convert/*.cpp
)

file(GLOB SOURCES_TEST 
	test/*.cpp
)

add_executable(nos_test ${SOURCES_TEST})
add_library(nos SHARED ${SOURCES})

target_include_directories(nos_test PRIVATE . test)
target_include_directories(nos PRIVATE .)
target_link_libraries(nos igris)
target_link_libraries(nos_test nos)
target_link_libraries(nos_test igris)
target_link_libraries(nos_test pthread)

if (UNIX AND NOT APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()


if (APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/local/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()

enable_testing()
add_test(NAME nos_test COMMAND nos_test)
