# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/clion/310/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug

# Utility rule file for mrproper.

# Include any custom commands dependencies for this target.
include CMakeFiles/mrproper.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mrproper.dir/progress.make

CMakeFiles/mrproper:
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove_directory /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug/zip
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove_directory /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug/bin
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove_directory CMakeFiles
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove CMakeCache.txt
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove CMakeDoxyfile.in
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove CMakeDoxygenDefaults.cmake
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove cmake_install.cmake
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove_directory doc_doxygen
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante && /snap/clion/310/bin/cmake/linux/x64/bin/cmake -E remove_directory quienesquien_autogen

mrproper: CMakeFiles/mrproper
mrproper: CMakeFiles/mrproper.dir/build.make
.PHONY : mrproper

# Rule to build all files generated by this target.
CMakeFiles/mrproper.dir/build: mrproper
.PHONY : CMakeFiles/mrproper.dir/build

CMakeFiles/mrproper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mrproper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mrproper.dir/clean

CMakeFiles/mrproper.dir/depend:
	cd /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug /home/maria/Carrera/Segundo/1cuatri/ED/ED_Repositorios/ED_PRACTICAS/PRACTICA5_quien/practica_final/estudiante/cmake-build-debug/CMakeFiles/mrproper.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mrproper.dir/depend
