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
CMAKE_BINARY_DIR = /home/slinnr/cppworkspace/slinnrserver/build

# Include any dependencies generated for this target.
include CMakeFiles/slinnrserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/slinnrserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/slinnrserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slinnrserver.dir/flags.make

CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o: ../slinnr/log.cpp
CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp

CMakeFiles/slinnrserver.dir/slinnr/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp > CMakeFiles/slinnrserver.dir/slinnr/log.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/log.cpp -o CMakeFiles/slinnrserver.dir/slinnr/log.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o: ../slinnr/config.cpp
CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp

CMakeFiles/slinnrserver.dir/slinnr/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp > CMakeFiles/slinnrserver.dir/slinnr/config.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/config.cpp -o CMakeFiles/slinnrserver.dir/slinnr/config.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o: ../slinnr/thread.cpp
CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/thread.cpp

CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/thread.cpp > CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/thread.cpp -o CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o: ../slinnr/util.cpp
CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/util.cpp

CMakeFiles/slinnrserver.dir/slinnr/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/util.cpp > CMakeFiles/slinnrserver.dir/slinnr/util.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/util.cpp -o CMakeFiles/slinnrserver.dir/slinnr/util.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o: ../slinnr/fiber.cpp
CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/fiber.cpp

CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/fiber.cpp > CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/fiber.cpp -o CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o: ../slinnr/schedule.cpp
CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/schedule.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/schedule.cpp

CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/schedule.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/schedule.cpp > CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/schedule.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/schedule.cpp -o CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.s

CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o: CMakeFiles/slinnrserver.dir/flags.make
CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o: ../slinnr/iomanager.cpp
CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o: CMakeFiles/slinnrserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o -MF CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o.d -o CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o -c /home/slinnr/cppworkspace/slinnrserver/slinnr/iomanager.cpp

CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinnr/cppworkspace/slinnrserver/slinnr/iomanager.cpp > CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.i

CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"slinnr/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinnr/cppworkspace/slinnrserver/slinnr/iomanager.cpp -o CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.s

# Object files for target slinnrserver
slinnrserver_OBJECTS = \
"CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o" \
"CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o"

# External object files for target slinnrserver
slinnrserver_EXTERNAL_OBJECTS =

../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/log.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/config.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/thread.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/util.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/fiber.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/schedule.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/slinnr/iomanager.cpp.o
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/build.make
../lib/libslinnrserver.so: CMakeFiles/slinnrserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library ../lib/libslinnrserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slinnrserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slinnrserver.dir/build: ../lib/libslinnrserver.so
.PHONY : CMakeFiles/slinnrserver.dir/build

CMakeFiles/slinnrserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slinnrserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slinnrserver.dir/clean

CMakeFiles/slinnrserver.dir/depend:
	cd /home/slinnr/cppworkspace/slinnrserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver /home/slinnr/cppworkspace/slinnrserver/build /home/slinnr/cppworkspace/slinnrserver/build /home/slinnr/cppworkspace/slinnrserver/build/CMakeFiles/slinnrserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/slinnrserver.dir/depend

