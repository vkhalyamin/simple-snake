# SIMPLE SNAKE

Simple snake game, written in C programming language and ncurses. GNU ncurses is a programming library that allows the users to create text-based user interfaces.

## Getting Started

This program is designed to run only on machines with Unix-like operating systems.

### Prerequisites

To compile the program, you need to install ncurses library. Ncurses is available in the default repositories of most Linux distributions. For instance, you can install it on Arch-based systems using the following command:

```
$ sudo pacman -S ncurses
```

On Ubuntu, Debian, Linux Mint:

```
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```

### Installing

Clone this repository:
```
$ git clone https://github.com/vkhalyamin/simple-snake.git
```

Build this program with Make:
```
$ cd ./simple-snake
$ make snake
```

## Usage

The program supports some options:
```
-s      set snake speed-level
-i      enable inverse control
-v      enable VIM control (h,j,k,l)
```
More info about options:
```
$ ./snake --help
```

## Author

[Khalyamin Vladimir](https://github.com/vkhalyamin) - vkhalyamin(at)protonmail.com

## License

This project is licensed under the MIT License &ndash; see the LICENSE file for details.
