# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jcbraz/Projects/CG-project/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jcbraz/Projects/CG-project/src/build

# Utility rule file for ExperimentalCoverage.

# Include any custom commands dependencies for this target.
include _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/progress.make

_deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage:
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /opt/homebrew/Cellar/cmake/3.25.2/bin/ctest -D ExperimentalCoverage

ExperimentalCoverage: _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage
ExperimentalCoverage: _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/build.make
.PHONY : ExperimentalCoverage

# Rule to build all files generated by this target.
_deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/build: ExperimentalCoverage
.PHONY : _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/build

_deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/clean:
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalCoverage.dir/cmake_clean.cmake
.PHONY : _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/clean

_deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/depend:
	cd /Users/jcbraz/Projects/CG-project/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jcbraz/Projects/CG-project/src /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-src /Users/jcbraz/Projects/CG-project/src/build /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/tinyxml2-build/CMakeFiles/ExperimentalCoverage.dir/depend

