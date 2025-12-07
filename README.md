# sfSandbox
sfSandbox is a toy sandbox CA made to teach myself SFML, modern c++ features like std::function and other things

---

# Compiling
## dependencies:
* A c++ compiler, if you would rather use clang++ than g++ just change the CXX line in the Makefile (advised c++20)
* As the only build system make is required to build the programm
* SFML is required to be installed in the path or you will need to add -L[path_to_sfml_local_copy] in the CXXFLAGS variable of the Makefile
### installing everything on linux is done as follows:
Ubuntu / Debian:
> sudo apt install g++-20 libc++-20 libsfml-dev make

The package names should be the same using other package managers, if you use pacman or yay feel free to make a PR to add the requirements download and install command here
### installing everything on windows is done as follows:
I do not know the commands, as before feel free to add them by PR
### installing everything on macOS is done as follows:
I guess it's the same as debian except the package manager is brew, if you know better, you know the drill, the PRs are open
## commands:
For fast compilation you can:
> make -j

Otherwise:
> make

---

# Debug profile
A debug profile might come in the future, it's not done yet

---

# Gameplay and screenshots
No gameplay is currently aviable, the sand is already placed in the world when you launch the programm and you cannt interact with it, however this will change soon


