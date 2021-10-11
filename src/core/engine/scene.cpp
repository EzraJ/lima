#include "core/engine/scene.hpp"

namespace lima{
    namespace core{
        namespace engine{
            scene::scene(uint64_t id = 0;){
                scene::_sceneID = id;
            }
            scene::~scene(){
                scene::_blockFile.close();
                scene::_idData.close();
            }

            void scene::openFile(std::string fName){
                if(!scene::_idData.is_open()){
                    return;
                }

                scene::_blockFile.open(fName, std::ios_base::in);
                if(_blockFile.is_open()){
                    scene::_blockFile >> _dimensions.x >> _dimensions.y;
                    std::getline(scene::_blockFile, _levelName);
                }else{
                    scene::_blockFile.close();
                    return;
                }

                scene::_blockData.resize(_dimensions.y);
                int x = 1;
                int y = 1;
                std::string line;
                while(std::getline(_blockFile, line)){
                    for(const char& c : line){
                        uint64_t blockID = 0;
                        auto got = scene::_sceneIDs.find(c);
                        if(got == scene::_sceneIDs.end()){
                            blockID = 0;
                        }else{
                            blockID = got->second;
                        }
                        scene::_blockData[y-1].push_back(lima::engine::block(vector2(x, y), blockID, c));
                        x++;
                    }
                    y++;
                    x=1;
                }
            }


            void scene::openManifest(std::string fName){
                scene::_idData.open(fName, std::ios_base::in);
                if(scene::_idData.is_open()){
                    std::string buf;
                    while(std::getline(scene::_idData, buf)){
                        // TODO!!!!! Make the syntax better!
                        char character = buf[0];
                        std::string str = buf.substr(2);
                        uint64_t value;
                        std::istringstream iss(str);
                        iss >> value;

                        scene::_sceneIDs.insert({character, value});
                    }
                }
            }

            std::vector<std::vector<lima::engine::block>>& sceneData(){
                return scene::_blockData;
            }

        }
    }
}