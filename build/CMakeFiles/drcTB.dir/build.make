# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /cvmfs/sft.cern.ch/lcg/releases/CMake/3.20.0-790a8/x86_64-centos7-gcc11-opt/bin/cmake

# The command to remove a file.
RM = /cvmfs/sft.cern.ch/lcg/releases/CMake/3.20.0-790a8/x86_64-centos7-gcc11-opt/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /u/user/gcho/DRC/TB2024/TB2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /u/user/gcho/DRC/TB2024/TB2024/build

# Include any dependencies generated for this target.
include CMakeFiles/drcTB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/drcTB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/drcTB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/drcTB.dir/flags.make

G__drcTB.cxx: ../include/LinkDef.hh
G__drcTB.cxx: ../include/TBaux.h
G__drcTB.cxx: ../include/TBconfig.h
G__drcTB.cxx: ../include/TBdetector.h
G__drcTB.cxx: ../include/TBevt.h
G__drcTB.cxx: ../include/TBmid.h
G__drcTB.cxx: ../include/TBmonit.h
G__drcTB.cxx: ../include/TBobject.h
G__drcTB.cxx: ../include/TBplotengine.h
G__drcTB.cxx: ../include/TBread.h
G__drcTB.cxx: ../include/TButility.h
G__drcTB.cxx: ../include/TBaux.h
G__drcTB.cxx: ../include/TBconfig.h
G__drcTB.cxx: ../include/TBdetector.h
G__drcTB.cxx: ../include/TBevt.h
G__drcTB.cxx: ../include/TBmid.h
G__drcTB.cxx: ../include/TBmonit.h
G__drcTB.cxx: ../include/TBobject.h
G__drcTB.cxx: ../include/TBplotengine.h
G__drcTB.cxx: ../include/TBread.h
G__drcTB.cxx: ../include/TButility.h
G__drcTB.cxx: ../include/LinkDef.hh
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating G__drcTB.cxx, libdrcTB_rdict.pcm, libdrcTB.rootmap"
	/cvmfs/sft.cern.ch/lcg/releases/CMake/3.20.0-790a8/x86_64-centos7-gcc11-opt/bin/cmake -E env LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/thepeg/2.2.3-18d03/x86_64-centos7-gcc11-opt/lib/ThePEG:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/herwig++/7.2.3-94809/x86_64-centos7-gcc11-opt/lib/Herwig:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/jaxlib/mlir/_mlir_libs:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/torch/lib:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/onnxruntime/capi/:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/contrib/tensor_forest:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/python/framework:/cvmfs/sft.cern.ch/lcg/releases/java/8u312-80070/x86_64-centos7-gcc11-opt/jre/lib/amd64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib64:/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/lib:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/thepeg/2.2.3-18d03/x86_64-centos7-gcc11-opt/lib/ThePEG:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/herwig++/7.2.3-94809/x86_64-centos7-gcc11-opt/lib/Herwig:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/jaxlib/mlir/_mlir_libs:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/torch/lib:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/onnxruntime/capi/:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/contrib/tensor_forest:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/python/framework:/cvmfs/sft.cern.ch/lcg/releases/java/8u312-80070/x86_64-centos7-gcc11-opt/jre/lib/amd64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib64:/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/lib:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/thepeg/2.2.3-18d03/x86_64-centos7-gcc11-opt/lib/ThePEG:/cvmfs/sft.cern.ch/lcg/releases/MCGenerators/herwig++/7.2.3-94809/x86_64-centos7-gcc11-opt/lib/Herwig:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/jaxlib/mlir/_mlir_libs:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/torch/lib:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/onnxruntime/capi/:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/contrib/tensor_forest:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/python3.9/site-packages/tensorflow/python/framework:/cvmfs/sft.cern.ch/lcg/releases/java/8u312-80070/x86_64-centos7-gcc11-opt/jre/lib/amd64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib64:/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib:/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib64:/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/lib:/u/user/gcho/cuda-12.1/lib64:/u/user/gcho/cuda-12.1/lib64:/u/user/gcho/cuda-12.1/lib64::/cvmfs/sft.cern.ch/lcg/releases/R/4.1.2-234e4/x86_64-centos7-gcc11-opt/lib64/R/library/readr/rcon:/u/user/gcho/DRC/TB2024/TB2024Paper/install/lib64:/cvmfs/sft.cern.ch/lcg/releases/R/4.1.2-234e4/x86_64-centos7-gcc11-opt/lib64/R/library/readr/rcon:/u/user/gcho/DRC/TB2024/TB2024Paper/install/lib64:/cvmfs/sft.cern.ch/lcg/releases/R/4.1.2-234e4/x86_64-centos7-gcc11-opt/lib64/R/library/readr/rcon:/u/user/gcho/DRC/TB2024/TB2024/install/lib64 /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/bin/rootcling -v2 -f G__drcTB.cxx -s /u/user/gcho/DRC/TB2024/TB2024/build/libdrcTB.so -rml libdrcTB.so -rmf /u/user/gcho/DRC/TB2024/TB2024/build/libdrcTB.rootmap -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/include -compilerI/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/include -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/include/c++/11.2.0 -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/include/c++/11.2.0/x86_64-pc-linux-gnu -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/include/c++/11.2.0/backward -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include-fixed -compilerI/usr/local/include -compilerI/usr/include -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/include -compilerI/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/include -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include -compilerI/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include-fixed -compilerI/usr/local/include -compilerI/usr/include -I/u/user/gcho/DRC/TB2024/TB2024/include -I/cvmfs/sft.cern.ch/lcg/releases/yamlcpp/0.6.3-d05b2/x86_64-centos7-gcc11-opt/include -I/cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/include -I/u/user/gcho/DRC/TB2024/TB2024 /u/user/gcho/DRC/TB2024/TB2024/include/TBaux.h /u/user/gcho/DRC/TB2024/TB2024/include/TBconfig.h /u/user/gcho/DRC/TB2024/TB2024/include/TBdetector.h /u/user/gcho/DRC/TB2024/TB2024/include/TBevt.h /u/user/gcho/DRC/TB2024/TB2024/include/TBmid.h /u/user/gcho/DRC/TB2024/TB2024/include/TBmonit.h /u/user/gcho/DRC/TB2024/TB2024/include/TBobject.h /u/user/gcho/DRC/TB2024/TB2024/include/TBplotengine.h /u/user/gcho/DRC/TB2024/TB2024/include/TBread.h /u/user/gcho/DRC/TB2024/TB2024/include/TButility.h /u/user/gcho/DRC/TB2024/TB2024/include/LinkDef.hh

libdrcTB_rdict.pcm: G__drcTB.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate libdrcTB_rdict.pcm

libdrcTB.rootmap: G__drcTB.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate libdrcTB.rootmap

CMakeFiles/drcTB.dir/src/TBaux.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBaux.cc.o: ../src/TBaux.cc
CMakeFiles/drcTB.dir/src/TBaux.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/drcTB.dir/src/TBaux.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBaux.cc.o -MF CMakeFiles/drcTB.dir/src/TBaux.cc.o.d -o CMakeFiles/drcTB.dir/src/TBaux.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBaux.cc

CMakeFiles/drcTB.dir/src/TBaux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBaux.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBaux.cc > CMakeFiles/drcTB.dir/src/TBaux.cc.i

CMakeFiles/drcTB.dir/src/TBaux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBaux.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBaux.cc -o CMakeFiles/drcTB.dir/src/TBaux.cc.s

CMakeFiles/drcTB.dir/src/TBdetector.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBdetector.cc.o: ../src/TBdetector.cc
CMakeFiles/drcTB.dir/src/TBdetector.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/drcTB.dir/src/TBdetector.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBdetector.cc.o -MF CMakeFiles/drcTB.dir/src/TBdetector.cc.o.d -o CMakeFiles/drcTB.dir/src/TBdetector.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBdetector.cc

CMakeFiles/drcTB.dir/src/TBdetector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBdetector.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBdetector.cc > CMakeFiles/drcTB.dir/src/TBdetector.cc.i

CMakeFiles/drcTB.dir/src/TBdetector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBdetector.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBdetector.cc -o CMakeFiles/drcTB.dir/src/TBdetector.cc.s

CMakeFiles/drcTB.dir/src/TBevt.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBevt.cc.o: ../src/TBevt.cc
CMakeFiles/drcTB.dir/src/TBevt.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/drcTB.dir/src/TBevt.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBevt.cc.o -MF CMakeFiles/drcTB.dir/src/TBevt.cc.o.d -o CMakeFiles/drcTB.dir/src/TBevt.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBevt.cc

CMakeFiles/drcTB.dir/src/TBevt.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBevt.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBevt.cc > CMakeFiles/drcTB.dir/src/TBevt.cc.i

CMakeFiles/drcTB.dir/src/TBevt.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBevt.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBevt.cc -o CMakeFiles/drcTB.dir/src/TBevt.cc.s

CMakeFiles/drcTB.dir/src/TBmid.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBmid.cc.o: ../src/TBmid.cc
CMakeFiles/drcTB.dir/src/TBmid.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/drcTB.dir/src/TBmid.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBmid.cc.o -MF CMakeFiles/drcTB.dir/src/TBmid.cc.o.d -o CMakeFiles/drcTB.dir/src/TBmid.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBmid.cc

CMakeFiles/drcTB.dir/src/TBmid.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBmid.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBmid.cc > CMakeFiles/drcTB.dir/src/TBmid.cc.i

CMakeFiles/drcTB.dir/src/TBmid.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBmid.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBmid.cc -o CMakeFiles/drcTB.dir/src/TBmid.cc.s

CMakeFiles/drcTB.dir/src/TBobject.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBobject.cc.o: ../src/TBobject.cc
CMakeFiles/drcTB.dir/src/TBobject.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/drcTB.dir/src/TBobject.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBobject.cc.o -MF CMakeFiles/drcTB.dir/src/TBobject.cc.o.d -o CMakeFiles/drcTB.dir/src/TBobject.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBobject.cc

CMakeFiles/drcTB.dir/src/TBobject.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBobject.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBobject.cc > CMakeFiles/drcTB.dir/src/TBobject.cc.i

CMakeFiles/drcTB.dir/src/TBobject.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBobject.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBobject.cc -o CMakeFiles/drcTB.dir/src/TBobject.cc.s

CMakeFiles/drcTB.dir/src/TBplotengine.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBplotengine.cc.o: ../src/TBplotengine.cc
CMakeFiles/drcTB.dir/src/TBplotengine.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/drcTB.dir/src/TBplotengine.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBplotengine.cc.o -MF CMakeFiles/drcTB.dir/src/TBplotengine.cc.o.d -o CMakeFiles/drcTB.dir/src/TBplotengine.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBplotengine.cc

CMakeFiles/drcTB.dir/src/TBplotengine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBplotengine.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBplotengine.cc > CMakeFiles/drcTB.dir/src/TBplotengine.cc.i

CMakeFiles/drcTB.dir/src/TBplotengine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBplotengine.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBplotengine.cc -o CMakeFiles/drcTB.dir/src/TBplotengine.cc.s

CMakeFiles/drcTB.dir/src/TBread.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TBread.cc.o: ../src/TBread.cc
CMakeFiles/drcTB.dir/src/TBread.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/drcTB.dir/src/TBread.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TBread.cc.o -MF CMakeFiles/drcTB.dir/src/TBread.cc.o.d -o CMakeFiles/drcTB.dir/src/TBread.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TBread.cc

CMakeFiles/drcTB.dir/src/TBread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TBread.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TBread.cc > CMakeFiles/drcTB.dir/src/TBread.cc.i

CMakeFiles/drcTB.dir/src/TBread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TBread.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TBread.cc -o CMakeFiles/drcTB.dir/src/TBread.cc.s

CMakeFiles/drcTB.dir/src/TButility.cc.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/src/TButility.cc.o: ../src/TButility.cc
CMakeFiles/drcTB.dir/src/TButility.cc.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/drcTB.dir/src/TButility.cc.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/src/TButility.cc.o -MF CMakeFiles/drcTB.dir/src/TButility.cc.o.d -o CMakeFiles/drcTB.dir/src/TButility.cc.o -c /u/user/gcho/DRC/TB2024/TB2024/src/TButility.cc

CMakeFiles/drcTB.dir/src/TButility.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/src/TButility.cc.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/src/TButility.cc > CMakeFiles/drcTB.dir/src/TButility.cc.i

CMakeFiles/drcTB.dir/src/TButility.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/src/TButility.cc.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/src/TButility.cc -o CMakeFiles/drcTB.dir/src/TButility.cc.s

CMakeFiles/drcTB.dir/G__drcTB.cxx.o: CMakeFiles/drcTB.dir/flags.make
CMakeFiles/drcTB.dir/G__drcTB.cxx.o: G__drcTB.cxx
CMakeFiles/drcTB.dir/G__drcTB.cxx.o: CMakeFiles/drcTB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/drcTB.dir/G__drcTB.cxx.o"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drcTB.dir/G__drcTB.cxx.o -MF CMakeFiles/drcTB.dir/G__drcTB.cxx.o.d -o CMakeFiles/drcTB.dir/G__drcTB.cxx.o -c /u/user/gcho/DRC/TB2024/TB2024/build/G__drcTB.cxx

CMakeFiles/drcTB.dir/G__drcTB.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drcTB.dir/G__drcTB.cxx.i"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/user/gcho/DRC/TB2024/TB2024/build/G__drcTB.cxx > CMakeFiles/drcTB.dir/G__drcTB.cxx.i

CMakeFiles/drcTB.dir/G__drcTB.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drcTB.dir/G__drcTB.cxx.s"
	/cvmfs/sft.cern.ch/lcg/releases/gcc/11.2.0-8a51a/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/user/gcho/DRC/TB2024/TB2024/build/G__drcTB.cxx -o CMakeFiles/drcTB.dir/G__drcTB.cxx.s

# Object files for target drcTB
drcTB_OBJECTS = \
"CMakeFiles/drcTB.dir/src/TBaux.cc.o" \
"CMakeFiles/drcTB.dir/src/TBdetector.cc.o" \
"CMakeFiles/drcTB.dir/src/TBevt.cc.o" \
"CMakeFiles/drcTB.dir/src/TBmid.cc.o" \
"CMakeFiles/drcTB.dir/src/TBobject.cc.o" \
"CMakeFiles/drcTB.dir/src/TBplotengine.cc.o" \
"CMakeFiles/drcTB.dir/src/TBread.cc.o" \
"CMakeFiles/drcTB.dir/src/TButility.cc.o" \
"CMakeFiles/drcTB.dir/G__drcTB.cxx.o"

# External object files for target drcTB
drcTB_EXTERNAL_OBJECTS =

libdrcTB.so: CMakeFiles/drcTB.dir/src/TBaux.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBdetector.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBevt.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBmid.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBobject.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBplotengine.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TBread.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/src/TButility.cc.o
libdrcTB.so: CMakeFiles/drcTB.dir/G__drcTB.cxx.o
libdrcTB.so: CMakeFiles/drcTB.dir/build.make
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libCore.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libImt.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libRIO.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libNet.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libHist.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libGraf.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libGraf3d.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libGpad.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libROOTDataFrame.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libTree.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libTreePlayer.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libRint.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libPostscript.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libMatrix.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libPhysics.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libMathCore.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libThread.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libMultiProc.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/lib/libROOTVecOps.so
libdrcTB.so: /cvmfs/sft.cern.ch/lcg/releases/yamlcpp/0.6.3-d05b2/x86_64-centos7-gcc11-opt/lib/libyaml-cpp.so.0.6.3
libdrcTB.so: CMakeFiles/drcTB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library libdrcTB.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drcTB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/drcTB.dir/build: libdrcTB.so
.PHONY : CMakeFiles/drcTB.dir/build

CMakeFiles/drcTB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/drcTB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/drcTB.dir/clean

CMakeFiles/drcTB.dir/depend: G__drcTB.cxx
CMakeFiles/drcTB.dir/depend: libdrcTB.rootmap
CMakeFiles/drcTB.dir/depend: libdrcTB_rdict.pcm
	cd /u/user/gcho/DRC/TB2024/TB2024/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/user/gcho/DRC/TB2024/TB2024 /u/user/gcho/DRC/TB2024/TB2024 /u/user/gcho/DRC/TB2024/TB2024/build /u/user/gcho/DRC/TB2024/TB2024/build /u/user/gcho/DRC/TB2024/TB2024/build/CMakeFiles/drcTB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/drcTB.dir/depend

