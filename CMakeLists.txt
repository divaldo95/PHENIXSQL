# $Id: CMakeLists.txt Baranyai Dávid | 2020.06.14 20:23:01 $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(PHENIXSQL)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Setup ROOT include directories and compile definitions
#
include(${ROOT_USE_FILE})

# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

set(ROOT_LIBRARIES -L${ROOT_LIBRARY_DIR} -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hpp)

#----------------------------------------------------------------------------
# Locate MySQL sources and libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})
find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
#----------------------------------------------------------------------------
# Add the executable
#
add_executable(PHENIXSQL PHENIXSQL.cpp ${sources} ${headers})
target_link_libraries(PHENIXSQL ${ROOT_LIBRARIES} ${MYSQL_LIBRARY})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS PHENIXSQL DESTINATION bin)
