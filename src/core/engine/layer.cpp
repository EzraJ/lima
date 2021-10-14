#include "core/engine/layer.hpp"

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

                lime::core::engine::scene getSceneRender(){
                    lima::core::engine::scene retScene(0);
                    for(auto& e : _myScenes){
                        e->secon
                    }
                }

        }
    }
}