# define minimum cmake version
cmake_minimum_required(VERSION 2.8)

project(CxxCCTests)

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS ${WX_COMPONENTS} REQUIRED)

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

# Include paths
include_directories("${CL_SRC_ROOT}/Plugin" 
                    "${CL_SRC_ROOT}/sdk/wxsqlite3/include" 
                    "${CL_SRC_ROOT}/CodeLite" 
                    "${CL_SRC_ROOT}/PCH" 
                    "${CL_SRC_ROOT}/Interfaces")

add_definitions(-DWXUSINGDLL_WXSQLITE3)
add_definitions(-DWXUSINGDLL_CL)
add_definitions(-DWXUSINGDLL_SDK)
add_definitions(-DASTYLE_LIB)

if ( USE_PCH )
    add_definitions(-include "${CL_PCH_FILE}")
    add_definitions(-Winvalid-pch)
endif ( USE_PCH )

if (UNIX AND NOT APPLE)
    set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
endif()

if ( APPLE )
    add_definitions(-fPIC)
endif()

FILE(GLOB SRCS "CCTest/*.cpp")

# Define the output
add_executable(CxxCCTests ${SRCS})

# Remove the "lib" prefix from the plugin name
target_link_libraries(CxxCCTests
                      ${LINKER_OPTIONS}
                      ${wxWidgets_LIBRARIES}
                      libcodelite
                      plugin
                      )
add_definitions(-DCXX_TEST_DIR=\"${CL_SRC_ROOT}/CodeCompletionsTests/CCTest/tests/\")
CL_INSTALL_EXECUTABLE(CxxCCTests)