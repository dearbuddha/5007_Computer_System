# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arthurcai/CLionProjects/CompSys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arthurcai/CLionProjects/CompSys/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CompSys.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CompSys.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CompSys.dir/flags.make

CMakeFiles/CompSys.dir/main.c.o: CMakeFiles/CompSys.dir/flags.make
CMakeFiles/CompSys.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/arthurcai/CLionProjects/CompSys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CompSys.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CompSys.dir/main.c.o   -c /Users/arthurcai/CLionProjects/CompSys/main.c

CMakeFiles/CompSys.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CompSys.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/arthurcai/CLionProjects/CompSys/main.c > CMakeFiles/CompSys.dir/main.c.i

CMakeFiles/CompSys.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CompSys.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/arthurcai/CLionProjects/CompSys/main.c -o CMakeFiles/CompSys.dir/main.c.s

# Object files for target CompSys
CompSys_OBJECTS = \
"CMakeFiles/CompSys.dir/main.c.o"

# External object files for target CompSys
CompSys_EXTERNAL_OBJECTS =

CompSys: CMakeFiles/CompSys.dir/main.c.o
CompSys: CMakeFiles/CompSys.dir/build.make
CompSys: CMakeFiles/CompSys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/arthurcai/CLionProjects/CompSys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CompSys"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CompSys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CompSys.dir/build: CompSys

.PHONY : CMakeFiles/CompSys.dir/build

CMakeFiles/CompSys.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CompSys.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CompSys.dir/clean

CMakeFiles/CompSys.dir/depend:
	cd /Users/arthurcai/CLionProjects/CompSys/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arthurcai/CLionProjects/CompSys /Users/arthurcai/CLionProjects/CompSys /Users/arthurcai/CLionProjects/CompSys/cmake-build-debug /Users/arthurcai/CLionProjects/CompSys/cmake-build-debug /Users/arthurcai/CLionProjects/CompSys/cmake-build-debug/CMakeFiles/CompSys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CompSys.dir/depend

