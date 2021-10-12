# lima
A text-based game engine

lima's primary purpose(as of right now) is to be a text-based game engine used in the [Kajam gamejam](https://replit.com/site/kajam)
Because of the simplicity, it shouldn't take too much time(famous last words), but will definitely be close.

The goal(as of 10/12/21) is to get lima into atleast a prototype state so that additions can be made to the gameengine while my team develops for Kajam. The silver-lining to this is that due to the simplicity of the project, after the script engine is made functional and basic bootstrap for angelscript is implemented, the API can be programmed in angelscript very easily and in theory the minimum needed for a functional prototype.

I'll be updating and patching lima before Kajam starts, during Kajam, and if our team finds the engine to work well then most likely after the Kajam. 

## Details

The project uses angelscript as the scripted language.

The project is ASCII-only for atleast now


## Planned features

* Camera system(s)
* Good enough API
* Instead of different drawing modes, for now have scenes display as layers and be togglable with "transparent" characters. Game programming will handle logic for something like a pause menu
* No serliaization *for now*
* Physics/Game logic/Game updates will most likely be implemented by game programmers to allow flexibility(in terms of the engine and the game programmer is making)
    * However, let's implement tools to make all of these easier to use. i.e "registerGameLogicFunction(fName, timeInterval, ...)" etc
* Entity system
    * Most likely will use the above systems and have game programmers implement themselves to an extent(i.e we provide entity IDs similar to block IDs)
* Global ID systems utilizing uint64_t for various systems(block behaviors, entities, scripts, scenes, etc)

### Rendering
#### Cameras
Cameras will logically exist and be affixed to a point(or entity) and will render(print to console) a radius around the camera(with a rectangular viewpoint) appropriately.
#### Windows
Each camera will require the existence of a window, in this case a viewport is a better way of putting it. There's always going to be a master window that is positioned from (0,0) to the maximum resolution of the terminal. Whenever a camera is connected to a window, it will render to that window. Most likely the window will actually do the rendering, with the camera merely being a top-down point. This may change when implementing views that aren't top down.
#### Updates
Instead of clearing the screen and reprinting everything, it will be better to move the cursor to (1,1) and print to the appropriate windows(with respect to layers) 
# Dependencies

[Taywee/args](https://github.com/Taywee/args) (Header)

[gabime/spdlog](https://github.com/gabime/spdlog) (Header)

[angelscript](https://www.angelcode.com/angelscript/) (Statically Linked)



# "Internal docs/rules"

Everything internal to lima will be marked as lima_Name
(i.e the lima terminal singleton is lima_Terminal in the game engine singleton)

The "smallest" cursor position/point of origin is (1,1), if anything returns 0 for x,y coordinates it means an error occured. 


# Notes
This project  is going to be VERY MESSY for awhile, I'll attempt to keep things organized but famous last words. 
To give an idea for the project outline; it will most likely just be a scrappy collection of libraries barely working together with "a lot of overhead" and poor programming. 
However, if the Kajam gamejam goes well and my team likes lima(or if I want to continue development), I'll keep on adding features and such to lima. It should get interesting because I've never seen a text game engine that wasn't adventure-styled or specific to a game. Per repl's requirements, lima will only run on Linux. In theory windows supports should be very easy, but we never know. (I might straight up be too lazy)