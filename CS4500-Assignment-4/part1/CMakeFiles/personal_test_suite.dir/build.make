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
include CMakeFiles/personal_test_suite.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/personal_test_suite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/personal_test_suite.dir/flags.make

CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o: CMakeFiles/personal_test_suite.dir/flags.make
CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o: personal_test_suite.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o -c /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/personal_test_suite.cpp

CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/personal_test_suite.cpp > CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.i

CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/personal_test_suite.cpp -o CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.s

# Object files for target personal_test_suite
personal_test_suite_OBJECTS = \
"CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o"

# External object files for target personal_test_suite
personal_test_suite_EXTERNAL_OBJECTS =

personal_test_suite: CMakeFiles/personal_test_suite.dir/personal_test_suite.cpp.o
personal_test_suite: CMakeFiles/personal_test_suite.dir/build.make
personal_test_suite: lib/libgtest.a
personal_test_suite: CMakeFiles/personal_test_suite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable personal_test_suite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/personal_test_suite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/personal_test_suite.dir/build: personal_test_suite

.PHONY : CMakeFiles/personal_test_suite.dir/build

CMakeFiles/personal_test_suite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/personal_test_suite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/personal_test_suite.dir/clean

CMakeFiles/personal_test_suite.dir/depend:
	cd /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles/personal_test_suite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/personal_test_suite.dir/depend
