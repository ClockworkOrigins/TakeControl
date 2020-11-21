# TakeControl
TakeControl is a tool to manage game contents from characters over items to dialogs. Due to its plugin architecture it can be used for every game. The first game making use of it will be Red Skies: Ascension.

## Building from source

To build TakeControl yourself to add bugfixes or new features, you need to set up the following:

* Download & install **Git**
* Download & install **Microsoft Visual Studio 2015** or **Microsoft Visual Studio 2017** (other versions are currently not officially supported but might work as well)
* Download & install **Qt 5.12** (newer version might work as well, but aren't tested yet)
* Download & install **CMake**
* Run cmake (best would be using the GUI) and configure your build
* Ensure either 7zip or WinRar are in PATH
* When using VS 2015: Set the environment variable **VS15** to the path of the **vcvarsall.bat** (e.g. C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat)
* When using VS 2017: Set the environment variable **VS17** to the path of the **vcvars64.bat** (e.g. C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat)
* Set the CMake variable **Qt5_BaseDir** to the Qt 5.12 folder, e.g. **C:\Qt\5.12**

That's it. Now you have a Visual Studio project to build TakeControl.

### Building on Linux

Building on Linux using either g++ or clang++ should be no problem, but isn't officially supported yet.
