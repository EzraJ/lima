// Layer class for the gamengine to use, it will:
// Track and load scenes for visiblity and gamelogic(booleans)
// present the renderer with a renderable string OR blocks

#pragma once

#include "core/engine/block.hpp"
#include "core/engine/scene.hpp"
#include <map>

namespace lima{
    namespace core{
        namespace engine{
            class layer{
                public:
                    layer(std::string fName, uint64_t id = 0);
                    ~layer();

                    void moveScene(uint64_t dst, uint64_t src); // Swaps senes dst and src, doesn't really matter which is which
                    void addScene(std::string fName, uint64_t id);


                    std::unordered_map<uint64_t, lima::core::engine::scene>& getScene(){
                        return _myScenes;
                    }

                    void setVisbility(bool visible){
                        _visible = visible;
                    }

                    void setGameLogic(bool loaded){
                        _gameLogic = loaded;
                    }

                    lima::core::engine::scene getVisibleScene(); // Does not render; instead returns the blocks of all of the scenes after processing.
                    // i.e scene 0 is the scene, and scene 1 is full of transparent blocks, getSceneRender() will return a scene with all of the blocks in 

                private:
                    //std::vector<lime::core::engine::scene> _myScenes;
                    std::map<uint64_t, lima::core::engine::scene> _myScenes;
                    bool _visible = false;
                    bool _gameLogic = false;
            };



        }
    }
}