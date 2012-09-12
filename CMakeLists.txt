# License & Copyright
# ===================
#
# Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(fprynt)

include_directories(/usr/include/python2.7)
#include_directories(${PROJECT_SOURCE_DIR}/include)

# User code
#file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

SET(LIBRARY_OUTPUT_PATH "../fprynt")
add_library(fprynt "SHARED" lib_fprynt.cc ${sources} ${headers})

target_link_libraries(fprynt /usr/lib/libboost_python.so)
target_link_libraries(fprynt /usr/lib/libpython2.7.so)
target_link_libraries(fprynt /usr/local/lib/libfprint.so)

