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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1

# Include any dependencies generated for this target.
include CMakeFiles/basic_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic_example.dir/flags.make

CMakeFiles/basic_example.dir/basic_example.cpp.o: CMakeFiles/basic_example.dir/flags.make
CMakeFiles/basic_example.dir/basic_example.cpp.o: basic_example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basic_example.dir/basic_example.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_example.dir/basic_example.cpp.o -c /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/basic_example.cpp

CMakeFiles/basic_example.dir/basic_example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_example.dir/basic_example.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/basic_example.cpp > CMakeFiles/basic_example.dir/basic_example.cpp.i

CMakeFiles/basic_example.dir/basic_example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_example.dir/basic_example.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/basic_example.cpp -o CMakeFiles/basic_example.dir/basic_example.cpp.s

# Object files for target basic_example
basic_example_OBJECTS = \
"CMakeFiles/basic_example.dir/basic_example.cpp.o"

# External object files for target basic_example
basic_example_EXTERNAL_OBJECTS =

basic_example: CMakeFiles/basic_example.dir/basic_example.cpp.o
basic_example: CMakeFiles/basic_example.dir/build.make
basic_example: lib/libgtest.a
basic_example: CMakeFiles/basic_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable basic_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic_example.dir/build: basic_example

.PHONY : CMakeFiles/basic_example.dir/build

CMakeFiles/basic_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic_example.dir/clean

CMakeFiles/basic_example.dir/depend:
	cd /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles/basic_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic_example.dir/depend

