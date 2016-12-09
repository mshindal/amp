# amp
amp - another music player

A music player for Windows, macOS, and Linux.

<img src="https://i.imgur.com/sWu9CkD.png">

## Building

### Linux

#### Ubuntu
* Install the development packages we need with `sudo apt install g++ cmake make pkg-config qt5-default qtmultimedia5-dev libtag1-dev`.
* Build with `cmake && make`.

#### Fedora
* Install the development packages we need with `sudo dnf install gcc-c++ cmake make pkgconfig qt5-qtbase-devel qt5-qtmultimedia-devel taglib-devel`.
* Build with `cmake && make`.

### Windows
* Install [MSYS2](http://msys2.github.io/). 
* Install the development packages we need by running the following command inside a **MSYS2 MinGW 64-bit** shell: `mkdir -p /mingw64 && pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make mingw-w64-x86_64-pkg-config mingw-w64-x86_64-qt5 mingw-w64-x86_64-taglib`.
* Build with `cmake -G "Unix Makefiles" && make`. 

### macOS
TODO, but probably use Homebrew.
