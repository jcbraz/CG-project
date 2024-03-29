# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Applications/CMake.app/Contents/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CMake.app/Contents/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/bernardocosta/Desktop/CG-project/CMakeFiles /Users/bernardocosta/Desktop/CG-project//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/bernardocosta/Desktop/CG-project/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named group_project

# Build rule for target.
group_project: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 group_project
.PHONY : group_project

# fast build rule for target.
group_project/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/build
.PHONY : group_project/fast

engine.o: engine.cpp.o
.PHONY : engine.o

# target to build an object file
engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/engine.cpp.o
.PHONY : engine.cpp.o

engine.i: engine.cpp.i
.PHONY : engine.i

# target to preprocess a source file
engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/engine.cpp.i
.PHONY : engine.cpp.i

engine.s: engine.cpp.s
.PHONY : engine.s

# target to generate assembly for a file
engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/engine.cpp.s
.PHONY : engine.cpp.s

geometricShapes.o: geometricShapes.cpp.o
.PHONY : geometricShapes.o

# target to build an object file
geometricShapes.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/geometricShapes.cpp.o
.PHONY : geometricShapes.cpp.o

geometricShapes.i: geometricShapes.cpp.i
.PHONY : geometricShapes.i

# target to preprocess a source file
geometricShapes.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/geometricShapes.cpp.i
.PHONY : geometricShapes.cpp.i

geometricShapes.s: geometricShapes.cpp.s
.PHONY : geometricShapes.s

# target to generate assembly for a file
geometricShapes.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/group_project.dir/build.make CMakeFiles/group_project.dir/geometricShapes.cpp.s
.PHONY : geometricShapes.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... group_project"
	@echo "... engine.o"
	@echo "... engine.i"
	@echo "... engine.s"
	@echo "... geometricShapes.o"
	@echo "... geometricShapes.i"
	@echo "... geometricShapes.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

