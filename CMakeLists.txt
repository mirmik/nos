cmake_minimum_required(VERSION 3.5.1)
project(nos)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CC_STANDARD 11)

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

target_include_directories(nos_test PRIVATE .)
target_include_directories(nos PRIVATE .)
target_link_libraries(nos igris)
target_link_libraries(nos_test nos)
target_link_libraries(nos_test igris)
target_link_libraries(nos_test gtest)
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