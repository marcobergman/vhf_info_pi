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
CMAKE_SOURCE_DIR = /home/marcb/vhf_info_pi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcb/vhf_info_pi/build

# Include any dependencies generated for this target.
include libs/jsoncpp/CMakeFiles/JSONCPP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libs/jsoncpp/CMakeFiles/JSONCPP.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/jsoncpp/CMakeFiles/JSONCPP.dir/progress.make

# Include the compile flags for this target's objects.
include libs/jsoncpp/CMakeFiles/JSONCPP.dir/flags.make

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/flags.make
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o: /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_reader.cpp
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcb/vhf_info_pi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o -MF CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o.d -o CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o -c /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_reader.cpp

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JSONCPP.dir/src/json_reader.cpp.i"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_reader.cpp > CMakeFiles/JSONCPP.dir/src/json_reader.cpp.i

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JSONCPP.dir/src/json_reader.cpp.s"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_reader.cpp -o CMakeFiles/JSONCPP.dir/src/json_reader.cpp.s

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/flags.make
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o: /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_value.cpp
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcb/vhf_info_pi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o -MF CMakeFiles/JSONCPP.dir/src/json_value.cpp.o.d -o CMakeFiles/JSONCPP.dir/src/json_value.cpp.o -c /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_value.cpp

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JSONCPP.dir/src/json_value.cpp.i"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_value.cpp > CMakeFiles/JSONCPP.dir/src/json_value.cpp.i

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JSONCPP.dir/src/json_value.cpp.s"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_value.cpp -o CMakeFiles/JSONCPP.dir/src/json_value.cpp.s

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/flags.make
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o: /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_writer.cpp
libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o: libs/jsoncpp/CMakeFiles/JSONCPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcb/vhf_info_pi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o -MF CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o.d -o CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o -c /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_writer.cpp

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JSONCPP.dir/src/json_writer.cpp.i"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_writer.cpp > CMakeFiles/JSONCPP.dir/src/json_writer.cpp.i

libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JSONCPP.dir/src/json_writer.cpp.s"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcb/vhf_info_pi/libs/jsoncpp/src/json_writer.cpp -o CMakeFiles/JSONCPP.dir/src/json_writer.cpp.s

# Object files for target JSONCPP
JSONCPP_OBJECTS = \
"CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o" \
"CMakeFiles/JSONCPP.dir/src/json_value.cpp.o" \
"CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o"

# External object files for target JSONCPP
JSONCPP_EXTERNAL_OBJECTS =

libs/jsoncpp/libJSONCPP.a: libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_reader.cpp.o
libs/jsoncpp/libJSONCPP.a: libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_value.cpp.o
libs/jsoncpp/libJSONCPP.a: libs/jsoncpp/CMakeFiles/JSONCPP.dir/src/json_writer.cpp.o
libs/jsoncpp/libJSONCPP.a: libs/jsoncpp/CMakeFiles/JSONCPP.dir/build.make
libs/jsoncpp/libJSONCPP.a: libs/jsoncpp/CMakeFiles/JSONCPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcb/vhf_info_pi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libJSONCPP.a"
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles/JSONCPP.dir/cmake_clean_target.cmake
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JSONCPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/jsoncpp/CMakeFiles/JSONCPP.dir/build: libs/jsoncpp/libJSONCPP.a
.PHONY : libs/jsoncpp/CMakeFiles/JSONCPP.dir/build

libs/jsoncpp/CMakeFiles/JSONCPP.dir/clean:
	cd /home/marcb/vhf_info_pi/build/libs/jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles/JSONCPP.dir/cmake_clean.cmake
.PHONY : libs/jsoncpp/CMakeFiles/JSONCPP.dir/clean

libs/jsoncpp/CMakeFiles/JSONCPP.dir/depend:
	cd /home/marcb/vhf_info_pi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcb/vhf_info_pi /home/marcb/vhf_info_pi/libs/jsoncpp /home/marcb/vhf_info_pi/build /home/marcb/vhf_info_pi/build/libs/jsoncpp /home/marcb/vhf_info_pi/build/libs/jsoncpp/CMakeFiles/JSONCPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/jsoncpp/CMakeFiles/JSONCPP.dir/depend

