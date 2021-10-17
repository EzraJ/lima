#include "core/engine/layer.hpp"
#include "core/terminal/terminal.hpp"
#include <algorithm>
#include <utility>
#include <string>
#include <functional>


namespace lima{
    namespace core{
        namespace engine{
                layer::layer(std::string fName, std::string mfName, uint64_t id, vector2 camPos){
                    lima::core::engine::scene psbk(id);
                    psbk.openManifest(mfName);
                    psbk.openFile(fName);
                    _myScenes[id] = psbk; // I have no idea why this just decided to work but fuck it all.
                    //_myScenes[id].openManifest(mfName);
                    //_myScenes[id].openFile(fName);
                    _cameraPosition = camPos;
                    std::cout << _myScenes[id].getFileName() << std::endl;
                }

                layer::~layer(){

                }


                void layer::moveScene(uint64_t dst, uint64_t src){
                    lima::core::engine::scene source = std::move(_myScenes[src]);
                    lima::core::engine::scene dest = std::move(_myScenes[dst]);
                    _myScenes[src] = dest;
                    _myScenes[dst] = source;

                    _myScenes[src].setID(src);
                    _myScenes[dst].setID(dst);
                }
                void layer::addScene(std::string fName, std::string mfName, uint64_t id){
                    lima::core::engine::scene psbk(id);
                    psbk.openManifest(mfName);
                    psbk.openFile(fName);
                    _myScenes[id] = psbk;
                    //_myScenes[id].openManifest(mfName);
                    //_myScenes[id].openFile(fName);
                }

                lima::core::engine::scene layer::getVisibleScene(){
                    int _y = lima::terminal::terminal::getWindowSize().y;
                    int _x = lima::terminal::terminal::getWindowSize().x;
                    lima::core::engine::scene retScene(0);
                    auto& bd = retScene.sceneData();
                    bd.resize(_y);
                    for(auto& e : bd){
                        e.resize(_x, lima::core::engine::block(vector2(0,0), 0, '>'));
                    }

                    int _filly = 1;
                    int _fillx = 1;
                    for(auto& e : bd){ // fill bd to be empty; its the return anyhow
                        for(auto& bdx : e){
                            
                            bdx = lima::core::engine::block(vector2(_fillx, _filly), 0, ' ');
                            _fillx++;
                        }
                        _fillx = 1;
                        _filly++;
                    }


                    for(auto& e : _myScenes){
                        // e.second = scene stuffs
                        std::vector<std::vector<lima::core::engine::block>>& srcBD = e.second.sceneData();
                        int _rety = 1;
                        int _retx = 1;
                        std::cout << "\r\n";
                        for(auto& srcbde : srcBD){
                            // y axis
                            for(auto& srcbdex : srcbde){

                                std::cout << "ID:" << srcbdex.getID() << " ";

                                if(srcbdex.getID() != 0){
                                    bd[_rety][_retx] = srcbdex;
                                    _retx++;
                                }else{
                                    _retx++;
                                }
                            }
                            std::cout << "\r\n";
                            _retx = 1;
                            _rety++;
                        }

                    }                    

                    return retScene;
                }

        }
    }
}