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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Aot/Desktop/Kingdom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Aot/Desktop/Kingdom/build

# Include any dependencies generated for this target.
include CMakeFiles/testB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testB.dir/flags.make

CMakeFiles/testB.dir/_test_files/testB.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/_test_files/testB.cpp.o: /Users/Aot/Desktop/Kingdom/_test_files/testB.cpp
CMakeFiles/testB.dir/_test_files/testB.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Aot/Desktop/Kingdom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testB.dir/_test_files/testB.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/_test_files/testB.cpp.o -MF CMakeFiles/testB.dir/_test_files/testB.cpp.o.d -o CMakeFiles/testB.dir/_test_files/testB.cpp.o -c /Users/Aot/Desktop/Kingdom/_test_files/testB.cpp

CMakeFiles/testB.dir/_test_files/testB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testB.dir/_test_files/testB.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Aot/Desktop/Kingdom/_test_files/testB.cpp > CMakeFiles/testB.dir/_test_files/testB.cpp.i

CMakeFiles/testB.dir/_test_files/testB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testB.dir/_test_files/testB.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Aot/Desktop/Kingdom/_test_files/testB.cpp -o CMakeFiles/testB.dir/_test_files/testB.cpp.s

# Object files for target testB
testB_OBJECTS = \
"CMakeFiles/testB.dir/_test_files/testB.cpp.o"

# External object files for target testB
testB_EXTERNAL_OBJECTS =

bin/testB: CMakeFiles/testB.dir/_test_files/testB.cpp.o
bin/testB: CMakeFiles/testB.dir/build.make
bin/testB: lib/libgtest.a
bin/testB: /usr/local/lib/libsfml-graphics.2.5.1.dylib
bin/testB: /usr/local/lib/libsfml-window.2.5.1.dylib
bin/testB: /usr/local/lib/libsfml-system.2.5.1.dylib
bin/testB: CMakeFiles/testB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Aot/Desktop/Kingdom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/testB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testB.dir/build: bin/testB
.PHONY : CMakeFiles/testB.dir/build

CMakeFiles/testB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testB.dir/clean

CMakeFiles/testB.dir/depend:
	cd /Users/Aot/Desktop/Kingdom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Aot/Desktop/Kingdom /Users/Aot/Desktop/Kingdom /Users/Aot/Desktop/Kingdom/build /Users/Aot/Desktop/Kingdom/build /Users/Aot/Desktop/Kingdom/build/CMakeFiles/testB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testB.dir/depend

