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
include CMakeFiles/submitted_test_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/submitted_test_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/submitted_test_1.dir/flags.make

CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o: CMakeFiles/submitted_test_1.dir/flags.make
CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o: submitted_test_1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o -c /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/submitted_test_1.cpp

CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/submitted_test_1.cpp > CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.i

CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/submitted_test_1.cpp -o CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.s

# Object files for target submitted_test_1
submitted_test_1_OBJECTS = \
"CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o"

# External object files for target submitted_test_1
submitted_test_1_EXTERNAL_OBJECTS =

submitted_test_1: CMakeFiles/submitted_test_1.dir/submitted_test_1.cpp.o
submitted_test_1: CMakeFiles/submitted_test_1.dir/build.make
submitted_test_1: lib/libgtest.a
submitted_test_1: CMakeFiles/submitted_test_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable submitted_test_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/submitted_test_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/submitted_test_1.dir/build: submitted_test_1

.PHONY : CMakeFiles/submitted_test_1.dir/build

CMakeFiles/submitted_test_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/submitted_test_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/submitted_test_1.dir/clean

CMakeFiles/submitted_test_1.dir/depend:
	cd /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1 /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-4/part1/CMakeFiles/submitted_test_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/submitted_test_1.dir/depend

