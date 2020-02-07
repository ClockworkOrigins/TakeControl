# TakeControl
TakeControl is a tool to manage game contents from characters over items to dialogs. Due to its plugin it can be used for every game. The first game making use of it will be Red Skies: Ascension.

## Building from source

To build TakeControl yourself to add bugfixes or new features, you need to set up the following:

* Download & install **Git**
* Download & install **Microsoft Visual Studio 2015** (other versions are currently not officially supported)
* Download & install **Qt 5.6** (newer version might work as well, but aren't tested yet)
* Download & install **CMake**
* Set the environment variable **Qt5_BaseDir** to the Qt 5.6 folder, e.g. **C:\Qt\5.6**
* Run cmake (best would be using the GUI) and configure your build

That's it. Now you have a Visual Studio project to build TakeControl.

### Building on Linux

Building on Linux using either g++ or clang++ is no problem (our build server builds the Linux configuration only). But we don't know whether the client will run.
