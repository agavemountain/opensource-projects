project(xcdb)
cmake_minimum_required(VERSION 2.6)

# Policy flag
set(CMAKE_MACOSX_RPATH 1)

#Setup CMake to run tests
enable_testing()

#Prep ourselves for compiling boost
find_package( Boost COMPONENTS unit_test_framework REQUIRED)

include_directories( include ${Boost_INCLUDE_DIRS} )

add_library(xcdb SHARED
	src/datafile.c
    src/sys.c
    #src/cdata.c
	)

add_executable(schema src/schema.c)

INSTALL_FILES( . .so xcdb )


########################
# Build the unit tests #
########################

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)

        #Add compile target
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName} ${Boost_LIBRARIES} xcdb)

        #I like to move testing binaries into a testBin directory
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)

