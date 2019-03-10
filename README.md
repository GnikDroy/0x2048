<p align="center">
<h1 align="center"> 0x2048 </h1>

<h3 align="center">A yet another implementation of the game 2048 in C!</h3>
</p>
<p align="center">
<img align="center" src="https://raw.githubusercontent.com/GnikDroy/0x2048/master/screenshots/2048.png">
</p>



## Requirements
- SDL2
- SDL2_ttk
- SDL2_mixer



## Meeting the Requirements

**The project uses CMake to compile the project**

Make sure that the requirements are met.

### Linux

`sudo apt-get update`

`sudo apt-get install cmake libsdl2-dev libsdl2ttf-dev libsdl2-mixer-dev`


This installs the necessary libraries under linux.

### Windows
Under Windows, you can download the libraries <a href="https://www.libsdl.org/download-2.0.php">here</a>.


## How to compile

Clone this github repository, and make a folder named 'build' inside the project root folder.

`git clone https://github.com/GnikDroy/0x2048`

`mkdir build`

Then we can us build the project inside this folder.

`cd build`

`cmake ..`

`make`

This will create a new folder named  `bin` inside the build folder.

The compiled program should be inside. 

The game has not been tested under windows but should work perfectly fine. If there are any platform issues, please start an issue.


## Running

After compiling, we can execute the game!

`cd bin`

`./2048`

Notice that there is a font file and a few audio resources inside the `bin` directory. They are used by the game to render the text and play audio.

The game won't run without these.



## Creating the documentation.

The project uses Doxygen for managing its documentation.

If you wish to read the documentation, install doxygen.

`sudo apt-get install doxygen-gui`

You might also need to install `graphviz` for visualizing the relations.

`sudo apt-get install graphviz`


You can create the docs by running `doxygen` inside the root folder.

All the documentation will be created under the `docs` folder.


## Tests

Since this was a simple enough project, no tests were written. I do not 
intend to write them in the future as well.

# Game Resources
This project uses audio from <a href="https://opengameart.org/">opengameart.com</a>

- <a href="https://opengameart.org/content/hero-immortal">Background Music</a> <a href="http://cr1eativecommons.org/licenses/by-sa/3.0/">(license)</a>
- <a href="https://opengameart.org/content/platformer-jumping-sounds"> Tile Mix Music </a> : <a href="https://creativecommons.org/licenses/by/3.0/">(license)</a>
