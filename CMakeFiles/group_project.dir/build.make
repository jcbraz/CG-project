# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bernardocosta/Desktop/CG-project/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bernardocosta/Desktop/CG-project

# Include any dependencies generated for this target.
include CMakeFiles/group_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/group_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/group_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/group_project.dir/flags.make

CMakeFiles/group_project.dir/engine.cpp.o: CMakeFiles/group_project.dir/flags.make
CMakeFiles/group_project.dir/engine.cpp.o: /Users/bernardocosta/Desktop/CG-project/src/engine.cpp
CMakeFiles/group_project.dir/engine.cpp.o: CMakeFiles/group_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardocosta/Desktop/CG-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/group_project.dir/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/group_project.dir/engine.cpp.o -MF CMakeFiles/group_project.dir/engine.cpp.o.d -o CMakeFiles/group_project.dir/engine.cpp.o -c /Users/bernardocosta/Desktop/CG-project/src/engine.cpp

CMakeFiles/group_project.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/group_project.dir/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardocosta/Desktop/CG-project/src/engine.cpp > CMakeFiles/group_project.dir/engine.cpp.i

CMakeFiles/group_project.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/group_project.dir/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardocosta/Desktop/CG-project/src/engine.cpp -o CMakeFiles/group_project.dir/engine.cpp.s

CMakeFiles/group_project.dir/geometricShapes.cpp.o: CMakeFiles/group_project.dir/flags.make
CMakeFiles/group_project.dir/geometricShapes.cpp.o: /Users/bernardocosta/Desktop/CG-project/src/geometricShapes.cpp
CMakeFiles/group_project.dir/geometricShapes.cpp.o: CMakeFiles/group_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardocosta/Desktop/CG-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/group_project.dir/geometricShapes.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/group_project.dir/geometricShapes.cpp.o -MF CMakeFiles/group_project.dir/geometricShapes.cpp.o.d -o CMakeFiles/group_project.dir/geometricShapes.cpp.o -c /Users/bernardocosta/Desktop/CG-project/src/geometricShapes.cpp

CMakeFiles/group_project.dir/geometricShapes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/group_project.dir/geometricShapes.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardocosta/Desktop/CG-project/src/geometricShapes.cpp > CMakeFiles/group_project.dir/geometricShapes.cpp.i

CMakeFiles/group_project.dir/geometricShapes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/group_project.dir/geometricShapes.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardocosta/Desktop/CG-project/src/geometricShapes.cpp -o CMakeFiles/group_project.dir/geometricShapes.cpp.s

# Object files for target group_project
group_project_OBJECTS = \
"CMakeFiles/group_project.dir/engine.cpp.o" \
"CMakeFiles/group_project.dir/geometricShapes.cpp.o"

# External object files for target group_project
group_project_EXTERNAL_OBJECTS =

group_project: CMakeFiles/group_project.dir/engine.cpp.o
group_project: CMakeFiles/group_project.dir/geometricShapes.cpp.o
group_project: CMakeFiles/group_project.dir/build.make
group_project: CMakeFiles/group_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bernardocosta/Desktop/CG-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable group_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/group_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/group_project.dir/build: group_project
.PHONY : CMakeFiles/group_project.dir/build

CMakeFiles/group_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/group_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/group_project.dir/clean

CMakeFiles/group_project.dir/depend:
	cd /Users/bernardocosta/Desktop/CG-project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bernardocosta/Desktop/CG-project/src /Users/bernardocosta/Desktop/CG-project/src /Users/bernardocosta/Desktop/CG-project /Users/bernardocosta/Desktop/CG-project /Users/bernardocosta/Desktop/CG-project/CMakeFiles/group_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/group_project.dir/depend

