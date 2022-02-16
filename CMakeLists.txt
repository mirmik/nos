cmake_minimum_required(VERSION 3.5.1)
project(nos)

file(GLOB HEADERS 
	nos/*.h
	nos/**/*.h	
)

file(GLOB NOS_SOURCES 
	nos/print/*.cpp	
	nos/fprint/*.cpp
	nos/util/osutil.cpp
	nos/util/trace.cpp
	nos/util/nos_numconvert.cpp
	nos/meta/*.cpp
	nos/log/*.cpp
	nos/log/targets/*.cpp
	nos/inet/*.cpp
	nos/input/*.cpp
	nos/io/*.cpp
	nos/io/impls/current_ostream_stdout.cpp
	nos/convert/*.cpp
)

file(GLOB NOS_SOURCES_PLUS)

file(GLOB SOURCES_TEST 
	tests/*.cpp
)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})	
	set( CMAKE_VERBOSE_MAKEFILE on )
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CC_STANDARD 11)
	set (PLATFORM_SOURCES )
	
	if (${STATIC_LIBS})
		set(CMAKE_SHARED_LINKER_FLAGS "-static-libstdc++")
	endif()
	
	if (WIN32 OR WIN64)
		set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	endif()

	add_library(nos SHARED ${NOS_SOURCES})
	target_include_directories(nos PRIVATE . ${ADDITIONAL_INCLUDES})
	
	if (NOT DEFINED WITHOUT_TESTS)
		add_executable(nos_test ${SOURCES_TEST} ${NOS_SOURCES})
		target_include_directories(nos_test PRIVATE . tests ${ADDITIONAL_INCLUDES})
	endif()
	
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

else()
	set(NOS_SOURCES ${NOS_SOURCES} ${NOS_SOURCES_PLUS} PARENT_SCOPE)

endif()
	