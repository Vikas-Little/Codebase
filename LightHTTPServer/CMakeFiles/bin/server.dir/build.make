# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/vikash/Documents/Codebase/LightHTTPServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vikash/Documents/Codebase/LightHTTPServer

# Include any dependencies generated for this target.
include CMakeFiles/bin/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bin/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bin/server.dir/flags.make

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o: CMakeFiles/bin/server.dir/flags.make
CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o: src/LightHTTPServer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vikash/Documents/Codebase/LightHTTPServer/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o   -c /home/vikash/Documents/Codebase/LightHTTPServer/src/LightHTTPServer.c

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bin/server.dir/src/LightHTTPServer.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vikash/Documents/Codebase/LightHTTPServer/src/LightHTTPServer.c > CMakeFiles/bin/server.dir/src/LightHTTPServer.c.i

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bin/server.dir/src/LightHTTPServer.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vikash/Documents/Codebase/LightHTTPServer/src/LightHTTPServer.c -o CMakeFiles/bin/server.dir/src/LightHTTPServer.c.s

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.requires:
.PHONY : CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.requires

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.provides: CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.requires
	$(MAKE) -f CMakeFiles/bin/server.dir/build.make CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.provides.build
.PHONY : CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.provides

CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.provides.build: CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o

CMakeFiles/bin/server.dir/src/Parse.c.o: CMakeFiles/bin/server.dir/flags.make
CMakeFiles/bin/server.dir/src/Parse.c.o: src/Parse.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vikash/Documents/Codebase/LightHTTPServer/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/bin/server.dir/src/Parse.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bin/server.dir/src/Parse.c.o   -c /home/vikash/Documents/Codebase/LightHTTPServer/src/Parse.c

CMakeFiles/bin/server.dir/src/Parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bin/server.dir/src/Parse.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vikash/Documents/Codebase/LightHTTPServer/src/Parse.c > CMakeFiles/bin/server.dir/src/Parse.c.i

CMakeFiles/bin/server.dir/src/Parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bin/server.dir/src/Parse.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vikash/Documents/Codebase/LightHTTPServer/src/Parse.c -o CMakeFiles/bin/server.dir/src/Parse.c.s

CMakeFiles/bin/server.dir/src/Parse.c.o.requires:
.PHONY : CMakeFiles/bin/server.dir/src/Parse.c.o.requires

CMakeFiles/bin/server.dir/src/Parse.c.o.provides: CMakeFiles/bin/server.dir/src/Parse.c.o.requires
	$(MAKE) -f CMakeFiles/bin/server.dir/build.make CMakeFiles/bin/server.dir/src/Parse.c.o.provides.build
.PHONY : CMakeFiles/bin/server.dir/src/Parse.c.o.provides

CMakeFiles/bin/server.dir/src/Parse.c.o.provides.build: CMakeFiles/bin/server.dir/src/Parse.c.o

CMakeFiles/bin/server.dir/src/FileUtility.c.o: CMakeFiles/bin/server.dir/flags.make
CMakeFiles/bin/server.dir/src/FileUtility.c.o: src/FileUtility.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vikash/Documents/Codebase/LightHTTPServer/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/bin/server.dir/src/FileUtility.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bin/server.dir/src/FileUtility.c.o   -c /home/vikash/Documents/Codebase/LightHTTPServer/src/FileUtility.c

CMakeFiles/bin/server.dir/src/FileUtility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bin/server.dir/src/FileUtility.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vikash/Documents/Codebase/LightHTTPServer/src/FileUtility.c > CMakeFiles/bin/server.dir/src/FileUtility.c.i

CMakeFiles/bin/server.dir/src/FileUtility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bin/server.dir/src/FileUtility.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vikash/Documents/Codebase/LightHTTPServer/src/FileUtility.c -o CMakeFiles/bin/server.dir/src/FileUtility.c.s

CMakeFiles/bin/server.dir/src/FileUtility.c.o.requires:
.PHONY : CMakeFiles/bin/server.dir/src/FileUtility.c.o.requires

CMakeFiles/bin/server.dir/src/FileUtility.c.o.provides: CMakeFiles/bin/server.dir/src/FileUtility.c.o.requires
	$(MAKE) -f CMakeFiles/bin/server.dir/build.make CMakeFiles/bin/server.dir/src/FileUtility.c.o.provides.build
.PHONY : CMakeFiles/bin/server.dir/src/FileUtility.c.o.provides

CMakeFiles/bin/server.dir/src/FileUtility.c.o.provides.build: CMakeFiles/bin/server.dir/src/FileUtility.c.o

CMakeFiles/bin/server.dir/src/WebPage.c.o: CMakeFiles/bin/server.dir/flags.make
CMakeFiles/bin/server.dir/src/WebPage.c.o: src/WebPage.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vikash/Documents/Codebase/LightHTTPServer/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/bin/server.dir/src/WebPage.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bin/server.dir/src/WebPage.c.o   -c /home/vikash/Documents/Codebase/LightHTTPServer/src/WebPage.c

CMakeFiles/bin/server.dir/src/WebPage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bin/server.dir/src/WebPage.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vikash/Documents/Codebase/LightHTTPServer/src/WebPage.c > CMakeFiles/bin/server.dir/src/WebPage.c.i

CMakeFiles/bin/server.dir/src/WebPage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bin/server.dir/src/WebPage.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vikash/Documents/Codebase/LightHTTPServer/src/WebPage.c -o CMakeFiles/bin/server.dir/src/WebPage.c.s

CMakeFiles/bin/server.dir/src/WebPage.c.o.requires:
.PHONY : CMakeFiles/bin/server.dir/src/WebPage.c.o.requires

CMakeFiles/bin/server.dir/src/WebPage.c.o.provides: CMakeFiles/bin/server.dir/src/WebPage.c.o.requires
	$(MAKE) -f CMakeFiles/bin/server.dir/build.make CMakeFiles/bin/server.dir/src/WebPage.c.o.provides.build
.PHONY : CMakeFiles/bin/server.dir/src/WebPage.c.o.provides

CMakeFiles/bin/server.dir/src/WebPage.c.o.provides.build: CMakeFiles/bin/server.dir/src/WebPage.c.o

# Object files for target bin/server
bin/server_OBJECTS = \
"CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o" \
"CMakeFiles/bin/server.dir/src/Parse.c.o" \
"CMakeFiles/bin/server.dir/src/FileUtility.c.o" \
"CMakeFiles/bin/server.dir/src/WebPage.c.o"

# External object files for target bin/server
bin/server_EXTERNAL_OBJECTS =

bin/server: CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o
bin/server: CMakeFiles/bin/server.dir/src/Parse.c.o
bin/server: CMakeFiles/bin/server.dir/src/FileUtility.c.o
bin/server: CMakeFiles/bin/server.dir/src/WebPage.c.o
bin/server: CMakeFiles/bin/server.dir/build.make
bin/server: CMakeFiles/bin/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bin/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bin/server.dir/build: bin/server
.PHONY : CMakeFiles/bin/server.dir/build

CMakeFiles/bin/server.dir/requires: CMakeFiles/bin/server.dir/src/LightHTTPServer.c.o.requires
CMakeFiles/bin/server.dir/requires: CMakeFiles/bin/server.dir/src/Parse.c.o.requires
CMakeFiles/bin/server.dir/requires: CMakeFiles/bin/server.dir/src/FileUtility.c.o.requires
CMakeFiles/bin/server.dir/requires: CMakeFiles/bin/server.dir/src/WebPage.c.o.requires
.PHONY : CMakeFiles/bin/server.dir/requires

CMakeFiles/bin/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bin/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bin/server.dir/clean

CMakeFiles/bin/server.dir/depend:
	cd /home/vikash/Documents/Codebase/LightHTTPServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vikash/Documents/Codebase/LightHTTPServer /home/vikash/Documents/Codebase/LightHTTPServer /home/vikash/Documents/Codebase/LightHTTPServer /home/vikash/Documents/Codebase/LightHTTPServer /home/vikash/Documents/Codebase/LightHTTPServer/CMakeFiles/bin/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bin/server.dir/depend
