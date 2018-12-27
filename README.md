<p align="center">
<h1 align="center"> 0x2048 </h1>

<h3 align="center">A yet another implementation of the game 2048 in C!</h3>

<img src="https://raw.githubusercontent.com/GnikDroy/0x2048/master/screenshots/2048.png">
</p>


## Requirements
- SDL2
- SDL2_ttk

Both of these libraries are needed to compile the program.

## Meeting the Requirements

**You can use CMake to compile the project**

Make sure that the requirements are met.

Under Ubuntu:

`sudo apt-get update`

`sudo apt-get install cmake`

`sudo apt-get install libsdl2-dev`

`sudo apt-get install libsdl2ttf-dev`

This installs the necessary libraries under linux.

If you are using Windows you can download the libraries by goint to the
SDL official website.

## How to compile

After fullfilling the requirements we can move forward to compiling the program.

Clone this github repo and make a folder named 'build' inside the project.

`git clone <Address in the URL>`

`mkdir build`

Then we can us build the project inside this folder.

`cd build`

`cmake ..`

`make`

This should create a new folder named  `bin` inside the build folder.

The compiled program should be inside. 

I have not tested this under windows. If there are any platform issues, please start an issue.

## Running

After compiling we can execute our game!

`cd bin`

`./2048`

Notice that there is a font file inside the directory. It is used by the game to render the text.

The game won't run without this.


## Creating the documentation.

The project used Doxygen for managing it's documentation.

If you wish to read the documentation install doxygen.

`sudo apt-get install doxygen-gui`

Then you can create the docs by running `doxygen` inside the root folder.

All the documentation will be created under the `docs` folder.

## Tests

Since this was a simple enough project. No tests were written. I do not 
intend to write them as well.