# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/222/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/222/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user13/Desktop/Github/CG-project/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user13/Desktop/Github/CG-project/src/cmake-build-debug

# Utility rule file for ContinuousConfigure.

# Include any custom commands dependencies for this target.
include _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/progress.make

_deps/tinyxml2-build/CMakeFiles/ContinuousConfigure:
	cd /home/user13/Desktop/Github/CG-project/src/cmake-build-debug/_deps/tinyxml2-build && /var/lib/snapd/snap/clion/222/bin/cmake/linux/x64/bin/ctest -D ContinuousConfigure

ContinuousConfigure: _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure
ContinuousConfigure: _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/build.make
.PHONY : ContinuousConfigure

# Rule to build all files generated by this target.
_deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/build: ContinuousConfigure
.PHONY : _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/build

_deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/clean:
	cd /home/user13/Desktop/Github/CG-project/src/cmake-build-debug/_deps/tinyxml2-build && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousConfigure.dir/cmake_clean.cmake
.PHONY : _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/clean

_deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/depend:
	cd /home/user13/Desktop/Github/CG-project/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user13/Desktop/Github/CG-project/src /home/user13/Desktop/Github/CG-project/src/cmake-build-debug/_deps/tinyxml2-src /home/user13/Desktop/Github/CG-project/src/cmake-build-debug /home/user13/Desktop/Github/CG-project/src/cmake-build-debug/_deps/tinyxml2-build /home/user13/Desktop/Github/CG-project/src/cmake-build-debug/_deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/tinyxml2-build/CMakeFiles/ContinuousConfigure.dir/depend

