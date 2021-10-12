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
My current idea for text rendering is to have scenes that act as layers(i.e layer 0,1,2,3 correlate to scene 0,1,2,3), with "transparent" blocks and toggles for each layer. On render updates, the renderer will ask the game engine for scenes that are visible and follow these steps:
1. Read each block in scene
2. For each block, read it's ID and send a "request" to the script engine
3. The script engine will "reply" with information pertaining to rendering(i.e character, color, bolded, etc)
4. Because everything is essentially text, we can construct a string that has each blocks character alongeside appropriate rendering properties
    1. i.e: "[color_blue]#[color_blue]#[color_blue]#[color_blue]#" with [color_blue] corresponding with the ANSI codes to change colors.
5. With the level loaded as a "renderable" string, we go to our logical camera(for now a single vector2 point) for where to render.     
    1. i.e: a vector2 of (1,1) on the camera will render everything in the scene to the edges of the terminal window.
    2. i.e: a vector of (5,5) will have the topleft most character correspond with (5,5) in the scene, and render to the edges of the terminal window.
    3. note: most likely will be a non-issue, but anything outside of the camera view might potentially be a problem; easily solvable with carriage returns and newlines
6. Finally, with the appropriate text selected to fit the terminal window, we simply send our text to the terminal module, which should require raw mode.

#### Cameras
With "layers" being a feature for the moment, cameras will simply be a camera in the render window. Make sure to give references to the game programmer and engine features, i.e if we wanted a camera block that would be the cameras position, or if the game programmer wants to continually update the camera positions on entities(such as a player)

#### Windows/Layers
The previous concept of a window was esentially a layer on top with different positions; Instead the current layer system could simply specify a point on the **terminal** window to render its (1,1) point of origin. This solution would allow game/engine programmers to make "views" into mulitple windows, when in reality the renderer simply renders the bottom-most layer to the top-most layer.

#### Functionality
1. In the gameEngine object: `std::vector<std::vector<lima::core::engine::scene>>`
    1. This will be the layers that the application can/has loaded. Most likely a `layer` class will be made that will do a lot of work for the renderer; and ensure that gamelogic will be updated on each individual scene. To keep the theme of properties, layers will keep track of visible scenes and track its own visibility, which the renderer will request.
        1. The renderer will poll the gameEngine class or use a reference of the layers, and then the renderer will go through and do its work.
        > note to self: It's most likely not true at all, but to keep multi-thread safety, we could have layers automatically insert themselves as outside of gamelogic(boolean) and not visible(boolean). Likewise, each scene will do the same. This may be an annoyance to the game programmers, but lets force them to be safe and track their scenes properly.
    2. When appropriate, implement game logic. There are many paths that canbe taken, we could have the game programmers handle it and have threads for engine features(i.e a render thread that runs at a rate defined by game programmers), force a game loop on the users, to name a few. The most likely solution will be to make engine features on threads(appropriately managed on the engine side), and have the angelscript API interface with these **in a thread-safe manner**
        1. For example, we could have `init.as` register the gameloop/logic function that will be called at set intervals defined by the game programmer.
            1. This approach will allow us to do the above, but if the game programmer wants to, the engine should be flexible enough to allow them to manage game logic on their own by "bootstrapping" angelscript. The engine will still be in control; but the engine cores will be on threads accessible via the angel script API made by us. It'll be as if the angelscript is the program itself and simply has access to game-making tools(crazy, I know/s)
        1. TODO: Flesh out this idea further

    3. Physics relies on game logic, so I'm entirely unsure who should do physics(if at all), most likely will keep flexibility in the favor of the game programmer.
        > note: layer by layer physics interactions? Unsure, probably best to have the engine do basic physics by default and allow game programmers to specify properties such as this.

Due to the beautiful simplicity of text, we can map everything to an ID instead of having to deal with ECS problems(a bad example, but still)
Because of this, a *lot* of processing can be simply done with the scene object alone. Additional processing(i.e layers, and potentially traits) will definitly be looked at in the future, but most likely lima will be ripe with features only because theres so much you can do with text graphics.

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