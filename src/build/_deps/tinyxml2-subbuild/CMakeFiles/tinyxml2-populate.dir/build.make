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
CMAKE_SOURCE_DIR = /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild

# Utility rule file for tinyxml2-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/tinyxml2-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tinyxml2-populate.dir/progress.make

CMakeFiles/tinyxml2-populate: CMakeFiles/tinyxml2-populate-complete

CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-mkdir
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-patch
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-build
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install
CMakeFiles/tinyxml2-populate-complete: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'tinyxml2-populate'"
	/Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles/tinyxml2-populate-complete
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-done

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update:
.PHONY : tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-build: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E echo_append
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-build

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure: tinyxml2-populate-prefix/tmp/tinyxml2-populate-cfgcmd.txt
tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E echo_append
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-gitinfo.txt
tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps && /Applications/CMake.app/Contents/bin/cmake -P /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/tmp/tinyxml2-populate-gitclone.cmake
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E echo_append
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'tinyxml2-populate'"
	/Applications/CMake.app/Contents/bin/cmake -Dcfgdir= -P /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/tmp/tinyxml2-populate-mkdirs.cmake
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-mkdir

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-patch: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'tinyxml2-populate'"
	/Applications/CMake.app/Contents/bin/cmake -E echo_append
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-patch

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update:
.PHONY : tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-test: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E echo_append
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-test

tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'tinyxml2-populate'"
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-src && /Applications/CMake.app/Contents/bin/cmake -P /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/tinyxml2-populate-prefix/tmp/tinyxml2-populate-gitupdate.cmake

tinyxml2-populate: CMakeFiles/tinyxml2-populate
tinyxml2-populate: CMakeFiles/tinyxml2-populate-complete
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-build
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-configure
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-download
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-install
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-mkdir
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-patch
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-test
tinyxml2-populate: tinyxml2-populate-prefix/src/tinyxml2-populate-stamp/tinyxml2-populate-update
tinyxml2-populate: CMakeFiles/tinyxml2-populate.dir/build.make
.PHONY : tinyxml2-populate

# Rule to build all files generated by this target.
CMakeFiles/tinyxml2-populate.dir/build: tinyxml2-populate
.PHONY : CMakeFiles/tinyxml2-populate.dir/build

CMakeFiles/tinyxml2-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tinyxml2-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tinyxml2-populate.dir/clean

CMakeFiles/tinyxml2-populate.dir/depend:
	cd /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild /Users/jcbraz/Projects/CG-project/src/build/_deps/tinyxml2-subbuild/CMakeFiles/tinyxml2-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinyxml2-populate.dir/depend

