# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/carlos/Escritorio/Redes/Redes/P2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carlos/Escritorio/Redes/Redes/P2

# Include any dependencies generated for this target.
include CMakeFiles/testPanel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testPanel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testPanel.dir/flags.make

CMakeFiles/testPanel.dir/panel_unittest.cpp.o: CMakeFiles/testPanel.dir/flags.make
CMakeFiles/testPanel.dir/panel_unittest.cpp.o: panel_unittest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlos/Escritorio/Redes/Redes/P2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testPanel.dir/panel_unittest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testPanel.dir/panel_unittest.cpp.o -c /home/carlos/Escritorio/Redes/Redes/P2/panel_unittest.cpp

CMakeFiles/testPanel.dir/panel_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testPanel.dir/panel_unittest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlos/Escritorio/Redes/Redes/P2/panel_unittest.cpp > CMakeFiles/testPanel.dir/panel_unittest.cpp.i

CMakeFiles/testPanel.dir/panel_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testPanel.dir/panel_unittest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlos/Escritorio/Redes/Redes/P2/panel_unittest.cpp -o CMakeFiles/testPanel.dir/panel_unittest.cpp.s

CMakeFiles/testPanel.dir/panel_unittest.cpp.o.requires:

.PHONY : CMakeFiles/testPanel.dir/panel_unittest.cpp.o.requires

CMakeFiles/testPanel.dir/panel_unittest.cpp.o.provides: CMakeFiles/testPanel.dir/panel_unittest.cpp.o.requires
	$(MAKE) -f CMakeFiles/testPanel.dir/build.make CMakeFiles/testPanel.dir/panel_unittest.cpp.o.provides.build
.PHONY : CMakeFiles/testPanel.dir/panel_unittest.cpp.o.provides

CMakeFiles/testPanel.dir/panel_unittest.cpp.o.provides.build: CMakeFiles/testPanel.dir/panel_unittest.cpp.o


CMakeFiles/testPanel.dir/Panel.cpp.o: CMakeFiles/testPanel.dir/flags.make
CMakeFiles/testPanel.dir/Panel.cpp.o: Panel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlos/Escritorio/Redes/Redes/P2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testPanel.dir/Panel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testPanel.dir/Panel.cpp.o -c /home/carlos/Escritorio/Redes/Redes/P2/Panel.cpp

CMakeFiles/testPanel.dir/Panel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testPanel.dir/Panel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlos/Escritorio/Redes/Redes/P2/Panel.cpp > CMakeFiles/testPanel.dir/Panel.cpp.i

CMakeFiles/testPanel.dir/Panel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testPanel.dir/Panel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlos/Escritorio/Redes/Redes/P2/Panel.cpp -o CMakeFiles/testPanel.dir/Panel.cpp.s

CMakeFiles/testPanel.dir/Panel.cpp.o.requires:

.PHONY : CMakeFiles/testPanel.dir/Panel.cpp.o.requires

CMakeFiles/testPanel.dir/Panel.cpp.o.provides: CMakeFiles/testPanel.dir/Panel.cpp.o.requires
	$(MAKE) -f CMakeFiles/testPanel.dir/build.make CMakeFiles/testPanel.dir/Panel.cpp.o.provides.build
.PHONY : CMakeFiles/testPanel.dir/Panel.cpp.o.provides

CMakeFiles/testPanel.dir/Panel.cpp.o.provides.build: CMakeFiles/testPanel.dir/Panel.cpp.o


# Object files for target testPanel
testPanel_OBJECTS = \
"CMakeFiles/testPanel.dir/panel_unittest.cpp.o" \
"CMakeFiles/testPanel.dir/Panel.cpp.o"

# External object files for target testPanel
testPanel_EXTERNAL_OBJECTS =

testPanel: CMakeFiles/testPanel.dir/panel_unittest.cpp.o
testPanel: CMakeFiles/testPanel.dir/Panel.cpp.o
testPanel: CMakeFiles/testPanel.dir/build.make
testPanel: /usr/lib/libgtest.a
testPanel: CMakeFiles/testPanel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carlos/Escritorio/Redes/Redes/P2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testPanel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testPanel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testPanel.dir/build: testPanel

.PHONY : CMakeFiles/testPanel.dir/build

CMakeFiles/testPanel.dir/requires: CMakeFiles/testPanel.dir/panel_unittest.cpp.o.requires
CMakeFiles/testPanel.dir/requires: CMakeFiles/testPanel.dir/Panel.cpp.o.requires

.PHONY : CMakeFiles/testPanel.dir/requires

CMakeFiles/testPanel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testPanel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testPanel.dir/clean

CMakeFiles/testPanel.dir/depend:
	cd /home/carlos/Escritorio/Redes/Redes/P2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carlos/Escritorio/Redes/Redes/P2 /home/carlos/Escritorio/Redes/Redes/P2 /home/carlos/Escritorio/Redes/Redes/P2 /home/carlos/Escritorio/Redes/Redes/P2 /home/carlos/Escritorio/Redes/Redes/P2/CMakeFiles/testPanel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testPanel.dir/depend

