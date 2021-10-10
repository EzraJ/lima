# lima
A text-based game engine

lima's primary purpose(as of now) is a text-based game engine used in the Kajam gamejam(from repl)

The premise is very simple, we need to make a text-based game, and because(October 2nd) the gamejame starts later we'd like a game engine to work with. 

Right now this is very barebones and such, but most likely I won't touch this project after the gamejam unless it shows actual potential, or I use it for future gamejams/games.
I'll most likely just occasionally check on the project for bugs and fix them after the game jam. While working on it for the gamejam will be given a lot of attention. 

## Details

The project uses angelscript as the scripted language.

The project is ASCII-only for atleast now


## Planned features

* Camera systems
* Good enough API
* Different "drawing modes" for UI/world/etc (will most likely ab/use the camera system)
* No serialization,  project files will simply be cfg files. Everything being text-based makes it easier to make an engine
* Physics(?)
* Entity system (AI by engine or user?)
    * Entity IDs to describe looks, which layer they are on, etc
* Global ID system to map characters to behaviors(including representation)
### Rendering
#### Cameras
Cameras will logically exist and be affixed to a point(or entity) and will render(print to console) a radius around the camera(with a rectangular viewpoint) appropriately.
#### Windows
Each camera will require the existence of a window, in this case a viewport is a better way of putting it. There's always going to be a master window that is positioned from (0,0) to the maximum resolution of the terminal. Whenever a camera is connected to a window, it will render to that window. Most likely the window will actually do the rendering, with the camera merely being a top-down point. This may change when implementing views that aren't top down.
#### Updates
Instead of clearing the screen and reprinting everything, it will be better to move the cursor to (0,0) and print to the appropriate windows(with respect to layers) 
# Dependencies

[Taywee/args](https://github.com/Taywee/args) (Header)

[gabime/spdlog](https://github.com/gabime/spdlog) (Header)

[angelscript](https://www.angelcode.com/angelscript/) (Statically Linked)



# "Internal docs/rules"

Everything internal to lima will be marked as lima_Name
(i.e the lima terminal singleton is lima_Terminal)


# Notes
This project (as of right now) is going to be VERY MESSY, as of right now, I need to get this project working in a prototype state in 8 days(ideally less for my gamejammers to work on the project)