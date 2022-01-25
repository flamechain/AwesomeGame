# AwesomeGame

Docs: [Index.md](./docs/Index.md)

Trello: [trello.com/b/2hjanStg](https://trello.com/b/2hjanStg/awesomegame)

## Building

### MinGW

Requires: make, g++

Run `$ make setup` to setup the building directories and copy necessary libraries.

To build a debug version run `$ make`, and for a release `$ make VERSION=release`.

### Windows

Requires: make, cl

Start by running `$ make -f Makefile.win setup` to copy the neccessary libraries.

To build a debug version run `$ make -f Makefile.win`, and for a release `$ make -f Makefile.win VERSION=release`.

### Installer

Requires: iscc

Run `$ make installer` to compile the installer for MinGW releases.

Run `$ make -f Makefile.win installer` to compile the installer for Windows releases.

___

## Running

For MinGW run `bin/MinGW/release/dissension.exe` or `bin/MinGW/debug/dissension.exe` for debug release.

For Windows run `bin/x86-64/release/dissension.exe` or `bin/x86-64/debug/dissension.exe` for debug release.

To install the game into AppData run `install-mingw.exe` or `install-x64.exe` depending on your environment.
