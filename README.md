# Bong

A recreation of the game Pong in C

## Run

* Linux or Windows 11 : `./bong`
* Windows 10 : `.\bong.exe`

### special params

--dbg : print ball speed and position and actual game state in console

## Compile

* Windows : make windows
* Linux   : make linux

### Dependencies

* For Linux users :
  * build-essential
  * libx11-dev
  * libxcursor-dev
  * libxinerama-dev
  * libxi-dev
  * libgl1-mesa-dev
  * libgles2-mesa-dev

* For Windows users : Probably all of this is already installed/comes with Windows
  * OpenGL(opengl32.dll)
  * Winmm(winmm.dll)
  * GDI(gdi32.dll)

## How to Play

Two players controls two bars, each player
need to hit the ball to the opponent side to
make a point, who makes 12 points first, wins.

### Controls

* Blue bar : W and S keys
* Green bar : Up and Down arrows

## Known *unintentional features*

Ball stick on bars [STATUS : Unsolved]

### Contributors

* [JnnDrc : Creator/Owner](https://github.com/JnnDrc)
* [rdWei : Contributor](https://github.com/rdWei)

#### Note

    This is the first programming project i made in my life,
    I've learnt C a in the last month.  
    this game's code probably is bigger than it should be.
