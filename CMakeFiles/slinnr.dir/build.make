# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/slinnr/cppworkspace/slinnrserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/slinnr/cppworkspace/slinnrserver

# Include any dependencies generated for this target.
include CMakeFiles/slinnr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/slinnr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/slinnr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slinnr.dir/flags.make

CMakeFiles/slinnr.dir/slinnr/log.cpp.o: CMakeFiles/slinnr.dir/flags.make
CMakeFiles/slinnr.dir/slinnr/log.cpp.o: slinnr/log.cpp
CMakeFiles/slinnr.dir/slinnr/log.cpp.o: CMakeFiles/slinnr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/slinnr.dir/slinnr/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnr.dir/slinnr/log.cpp.o -MF CMakeFiles/slinnr.dir/slinnr/log.cpp.o.d -o CMakeFiles/slinnr.dir/slinnr/log.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp

CMakeFiles/slinnr.dir/slinnr/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnr.dir/slinnr/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp > CMakeFiles/slinnr.dir/slinnr/log.cpp.i

CMakeFiles/slinnr.dir/slinnr/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnr.dir/slinnr/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp -o CMakeFiles/slinnr.dir/slinnr/log.cpp.s

CMakeFiles/slinnr.dir/slinnr/config.cpp.o: CMakeFiles/slinnr.dir/flags.make
CMakeFiles/slinnr.dir/slinnr/config.cpp.o: slinnr/config.cpp
CMakeFiles/slinnr.dir/slinnr/config.cpp.o: CMakeFiles/slinnr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/slinnr.dir/slinnr/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnr.dir/slinnr/config.cpp.o -MF CMakeFiles/slinnr.dir/slinnr/config.cpp.o.d -o CMakeFiles/slinnr.dir/slinnr/config.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp

CMakeFiles/slinnr.dir/slinnr/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnr.dir/slinnr/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp > CMakeFiles/slinnr.dir/slinnr/config.cpp.i

CMakeFiles/slinnr.dir/slinnr/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnr.dir/slinnr/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp -o CMakeFiles/slinnr.dir/slinnr/config.cpp.s

# Object files for target slinnr
slinnr_OBJECTS = \
"CMakeFiles/slinnr.dir/slinnr/log.cpp.o" \
"CMakeFiles/slinnr.dir/slinnr/config.cpp.o"

# External object files for target slinnr
slinnr_EXTERNAL_OBJECTS =

lib/libslinnr.so: CMakeFiles/slinnr.dir/slinnr/log.cpp.o
lib/libslinnr.so: CMakeFiles/slinnr.dir/slinnr/config.cpp.o
lib/libslinnr.so: CMakeFiles/slinnr.dir/build.make
lib/libslinnr.so: CMakeFiles/slinnr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slinnr/cppworkspace/slinnrserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library lib/libslinnr.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slinnr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slinnr.dir/build: lib/libslinnr.so
.PHONY : CMakeFiles/slinnr.dir/build

CMakeFiles/slinnr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slinnr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slinnr.dir/clean

CMakeFiles/slinnr.dir/depend:
	cd /home/slinnr/cppworkspace/slinnrserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver/CMakeFiles/slinnr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/slinnr.dir/depend

