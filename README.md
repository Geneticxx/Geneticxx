﻿# C++ library for genetic algorithms

## License
This project is licensed under a dual license model:

- GNU General Public License v3.0 (GPLv3) – for open-source, academic, and non-commercial use.

- Commercial License – required for any proprietary, closed-source, or commercial use.

If you intend to use this project in a commercial product or service, you must purchase a commercial license. 
More details available in **LICENSE** file.<br> For licensing inquiries, please contact:<br>
<a href="mailto:contact.geneticxx@gmail.com">
contact.geneticxx@gmail.com
</a>


# Getting started

## Building the library

### Linux


#### 1. Installing dependencies
Firstly, we suggest getting Clang, GCC, Ninja and CMake while Clang must be version 18 or newer, GCC+14 or newer, Ninja 1.11 or newer and CMake 3.26 or newer.
Check if you already have them and if they meet our requirements:
``` bash
clang --version;
gcc --version;
ninja --version;
cmake --version;
```
If you have Clang, GCC, Ninja and CMake and their versions are equal or newer to the ones mentioned then you can proceed to the next point.
If you want to update Clang or Ninja to the newest and stable version then:
``` bash
sudo apt upgrade clang
```
or:
``` bash
sudo apt upgrade gcc
```
or:
``` bash
sudo apt upgrade ninja-build
```
and:
``` bash
sudo apt upgrade cmake
```

Otherwise, we will start with getting Clang:
``` bash
sudo apt install clang
```

then GCC:
``` bash
sudo apt install gcc
```

and then Ninja:
``` bash
sudo apt install ninja-build
```

finally CMake:
``` bash
sudo apt install cmake
```
Now check their versions as we showed you before, and if you don't have obsolete Linux distribution then you should have all what is needed to flawlessly proceed to the next point.

#### 2. Building libcxx
Now, you need to build the libcxx. If you have built it already, then we suggest doing it again with commands provided below unless you are sure it will work with your setup:

``` bash
git clone https://github.com/llvm/llvm-project.git;
cd llvm-project;
mkdir build;
cmake -G Ninja -S runtimes -B build -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind";
ninja -C build;
```

Remember the build path. We will need it right away.

#### 3. Configuring the project
Furthermore, we need to run cmake command, which uses CMakeLists.txt file. Before you run the command below, you have to fill in real
paths to build directory of libc++ and Clang. If you don't know the compiler's path then run:
``` bash
which clang++
```
Next, we should run CMake command using Clang (clang++) and Libc++ (libcxx) paths:

``` bash
cmake -G Ninja -S . -B build -DCMAKE_CXX_COMPILER=<path-to-compiler> -DLIBCXX_BUILD=<build>
```

For instance:
``` bash
cmake -G Ninja -S . -B build -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DLIBCXX_BUILD=/home/aremis/Projects/llvm-project/build
```

#### WARNING!
Use direct paths only. E.g. \~/Projects/llvm-project/built will not work with kind regards to '\~'.

#### WARNING!
The path to the compiler (e.g. /usr/bin/clang++) may not be a symlink, clang-scan-deps does not handle that case properly.

#### 4. Building the project
Finally, the project must be built. We suggest using Ninja build system:

```bash
ninja -C build
```


### Windows
The newest version of MSVC compiler is required to build the project successfully.

#### 1. Compiling std library
You need to compile std files and put given std.ifc, std.obj, std.compat.ifc and std.compat.obj files into the project's cmake folder.
Below is an example how to do it with Visual Studio tools:

https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170#example-how-to-build-and-import-std <br>
https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170#example-how-to-build-and-import-stdcompat

#### 2. Building the project
Now, all you need to do is to build the project in your programming environment using MSVC compiler.
