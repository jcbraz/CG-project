# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-src"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-build"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/tmp"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src"
  "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/user13/Desktop/Github/CG-project/src/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
