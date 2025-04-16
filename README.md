# LITEC-Engine

LITEC-Engine is a lightweight game engine written in C for learning and experimentation purposes. The project uses [Premake](https://premake.github.io/) to generate build files for different platforms.

## 🛠️ Building the Project

### 🔷 Linux

1. Install Premake (if not already installed):

   ```bash
   wget https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz
   tar -xzf premake-5.0.0-beta2-linux.tar.gz
   sudo mv premake5 /usr/local/bin/
   
   Generate Makefiles:

premake5 gmake2

Build the project:

cd build
make config=debug   # or: make config=release


### 🟦 Windows

    Use the provided premake5.exe in the tools/ folder.

    Open a terminal and run:

tools\premake5.exe vs2022

This will generate a Visual Studio 2022 project file (.sln).

Open the .sln file in Visual Studio and build the project from there.


### 📜 License

MIT License

