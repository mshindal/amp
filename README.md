# amp
amp - another music player

A music player for Windows, macOS, and Linux.

<img src="https://i.imgur.com/sWu9CkD.png">

## Building

### Linux

#### Ubuntu
* Install the development packages we need with `sudo apt install g++ make pkg-config qt5-default qtmultimedia5-dev libtag1-dev`.
* Run `qmake` in the project's directory to generate a Makefile, and `make` to build the project.

#### Fedora
* Install the development packages we need with `sudo dnf install gcc-c++ make pkgconfig qt5-qtbase-devel qt5-qtmultimedia-devel taglib-devel`.
* Run `qmake-qt5` in the project's directory to generate a Makefile, and `make` to build the project.

### Windows
* Install [MSYS2](http://msys2.github.io/). Make sure you follow all instructions on the page, including the update process at the end.
* MSYS2 includes three shells, all of which you can launch from the Start Menu: MSYS2 MSYS, MSYS2 MinGW 64-bit, and MSYS2 MinGW 32-bit. Make sure you're using the correct shell for each step, or else you'll get `command not found` errors.
* Install the development packages we need by running the following command inside a **MSYS2 MSYS** shell: `mkdir -p /mingw64 && pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-pkg-config mingw-w64-x86_64-qt5 mingw-w64-x86_64-taglib`. This might take a while!
* Now that the packages we need are installed, we're ready to start building. Building happens inside a **MSYS2 MinGW 64-bit shell**. Open up a MSYS2 MinGW 64-bit shell and `cd` to the project's directory. *Note: In MSYS2, Windows drives are mounted off the root directory, so if you cloned the amp repository to C:\amp, you can access that directory inside of MSYS2 by navigating to /c/amp.* Once you're in the project's directory, run `qmake` to generate a Makefile, and `mingw32-make` to build the project.
* The amp binary will be in a folder called `debug`. Launch it by running `./debug/amp`. If you want to build the release version, run `mingw32-make -f Makefile.Release` and then launch it by running `./release/amp`.

### macOS
TODO, because I don't have a Mac, and Apple purposely makes it hard to run macOS in a virtual machine.
