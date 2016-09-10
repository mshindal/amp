# qTunes
A music player for Windows, MacOS, and Linux.

## Screenshots
<img src="https://i.imgur.com/vyuaTPw.png" width="600" height="470" alt="qTunes on KDE.">

qTunes on KDE.

## Builds
TODO

## Building

### Ubuntu
* Install the development packages we need with `sudo apt install g++ make pkg-config qt5-default qtmultimedia5-dev libtag1-dev`.
* Run `qmake` in the project's directory to generate a Makefile, and `make` to build the project.
* An IDE like Qt Creator can make development much easier. If you want, install it with `sudo apt install qtcreator`.

### Windows
* Install [MSYS2](http://msys2.github.io/). Make sure you follow all instructions on the page, including the update process at the end.
  * During the update process, the location of the MSYS2 script will change, preventing you from starting it from the Start Menu. Once that happens, you will need to launch MSYS2 by opening a Command Prompt and running `C:\msys64\msys2_shell.cmd` (or something slightly different if you changed the default folder that MSYS2 installs to).
* Once everything is up to date, install the development packages we need by running the following command inside a MSYS2 shell: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-pkg-config mingw-w64-x86_64-qt5 mingw-w64-x86_64-taglib`.
* Now that the packages we need are installed, we're ready to start building. Building happens inside a MINGW64 shell, not a MSYS2 shell. Open up a MINGW64 shell by opening a Command Prompt and running `C:\msys64\msys2_shell.cmd -mingw64`. In the MINGW64 shell you just opened, run `qmake` in the project's directory to generate a Makefile, and `mingw32-make` to build the project.
  * In MINGW64 and MSYS2, Windows drives are mounted off the root directory, so if you cloned the qTunes repository to `C:\qTunes`, you can access that directory inside of MINGW64 by navigating to `/c/qTunes`.
* An IDE like Qt Creator can make development much easier. If you want, install it by running the following command inside a MSYS2 shell: `pacman -S mingw-w64-x86_64-qt-creator`. Launch it by running `qtcreator&` in a MINGW64 shell.

### MacOS
TODO
