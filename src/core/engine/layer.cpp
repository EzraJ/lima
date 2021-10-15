#include "core/engine/layer.hpp"
#include "core/terminal/termina.hpp"

namespace lima{
    namespace core{
        namespace engine{
                layer::layer(std::string fName, std::string mfName,uint64_t id = 0){
                    _myScenes.insert({lima::core::engine::scene(id), id});
                    _myScenes[id].openManifest(mfName);
                    _myScenes[id].openFile(fName);
                }

                layer::~layer(){

                }


                void moveScene(uint64_t dst, uint64_t src){
                    lima::core::engine::scene tmp = _myScenes[dst];
                    _myScenes[dst] = _myScenes[src];
                    _myScenes[src] = tmp;
                    
                    _myScenes[dst].setID(dst);
                    _myScenes[src].setID(dst);
                }

                void addScene(std::string fName, std::string mfName,uint64_t id){
                    _myScenes.insert({lima::core::engine::scene(id), id});
                    _myScenes[id].openManifest(mfName);
                    _myScenes[id].openFile(fName);
                }

                lima::core::engine::scene getVisibleScene(){
                    int _y = lima::terminal::terminal::getWindowSize().y;
                    int _x = lima::terminal::terminal::getWindowSize().x;
                    lima::core::engine::scene retScene(0);
                    auto& bd = retScene.sceneData();
                    bd.resize(_y);
                    for(auto& e : bd){
                        e.resize();
                    }

                    if(!_visible){
                        // Nothing on the layer is visible, so lets return retScene with all of the blocks set to id 0
                        int x = 1;
                        for(int i = 0; i < _y; i++){
                            for(int v = 0; i < _x; i++){
                                bd.push_back(lima::core::engine::block(vector2(x, i+1), 0, '<'));
                                x++;
                            }
                        }
                        return retScene;
                    }
                    std::vector<lima::core::engine::scene> _scenebuf; // Because we care about order, are using std::map, and scenes are ordered by number, we can simply insert into a vector for easier processing
                    for(auto& e : _scenebuf){
                        _scenebuf.push_back(e->second);
                    }

                    for(auto& e : _scenebuf){
                        if(!e.isClear()){

                        }
                    }

                    return retScene;
                }

        }
    }
}