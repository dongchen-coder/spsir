# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dchen/tools/spsir

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dchen/tools/spsir/build

# Include any dependencies generated for this target.
include src/CMakeFiles/spsIR.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/spsIR.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/spsIR.dir/flags.make

src/CMakeFiles/spsIR.dir/spsir.cpp.o: src/CMakeFiles/spsIR.dir/flags.make
src/CMakeFiles/spsIR.dir/spsir.cpp.o: ../src/spsir.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchen/tools/spsir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/spsIR.dir/spsir.cpp.o"
	cd /Users/dchen/tools/spsir/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/spsIR.dir/spsir.cpp.o -c /Users/dchen/tools/spsir/src/spsir.cpp

src/CMakeFiles/spsIR.dir/spsir.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spsIR.dir/spsir.cpp.i"
	cd /Users/dchen/tools/spsir/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dchen/tools/spsir/src/spsir.cpp > CMakeFiles/spsIR.dir/spsir.cpp.i

src/CMakeFiles/spsIR.dir/spsir.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spsIR.dir/spsir.cpp.s"
	cd /Users/dchen/tools/spsir/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dchen/tools/spsir/src/spsir.cpp -o CMakeFiles/spsIR.dir/spsir.cpp.s

# Object files for target spsIR
spsIR_OBJECTS = \
"CMakeFiles/spsIR.dir/spsir.cpp.o"

# External object files for target spsIR
spsIR_EXTERNAL_OBJECTS =

src/libspsIR.so: src/CMakeFiles/spsIR.dir/spsir.cpp.o
src/libspsIR.so: src/CMakeFiles/spsIR.dir/build.make
src/libspsIR.so: src/CMakeFiles/spsIR.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dchen/tools/spsir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libspsIR.so"
	cd /Users/dchen/tools/spsir/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spsIR.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/spsIR.dir/build: src/libspsIR.so

.PHONY : src/CMakeFiles/spsIR.dir/build

src/CMakeFiles/spsIR.dir/clean:
	cd /Users/dchen/tools/spsir/build/src && $(CMAKE_COMMAND) -P CMakeFiles/spsIR.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/spsIR.dir/clean

src/CMakeFiles/spsIR.dir/depend:
	cd /Users/dchen/tools/spsir/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dchen/tools/spsir /Users/dchen/tools/spsir/src /Users/dchen/tools/spsir/build /Users/dchen/tools/spsir/build/src /Users/dchen/tools/spsir/build/src/CMakeFiles/spsIR.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/spsIR.dir/depend
