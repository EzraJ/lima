#include "core/engine/scene.hpp"

namespace lima{
    namespace core{
        namespace engine{
            scene::scene(uint64_t id){
                _sceneID = id;
            }
            scene::~scene(){
                _blockFile.close();
                _idData.close();
            }

            void scene::openFile(std::string fName){
                if(!_idData.is_open()){
                    return;
                }

                _blockFile.open(fName, std::ios_base::in);
                if(_blockFile.is_open()){
                    _blockFile >> _dimensions.x >> _dimensions.y;
                    std::getline(_blockFile, _levelName);
                }else{
                    _blockFile.close();
                    return;
                }

                _blockData.resize(_dimensions.y);
                int x = 1;
                int y = 1;
                std::string line;
                while(std::getline(_blockFile, line)){
                    for(const char& c : line){
                        uint64_t blockID = 0;
                        auto got = _sceneIDs.find(c);
                        if(got == _sceneIDs.end()){
                            blockID = 0;
                        }else{
                            blockID = got->second;
                        }
                        _blockData[y-1].push_back(lima::core::engine::block(vector2(x, y), blockID, c));
                        x++;
                    }
                    y++;
                    x=1;
                }
                _fileName = fName;
            }


            void scene::openManifest(std::string fName){
                _idData.open(fName, std::ios_base::in);
                if(_idData.is_open()){
                    std::string buf;
                    while(std::getline(_idData, buf)){
                        // TODO!!!!! Make the syntax better!
                        char character = buf[0];
                        std::string str = buf.substr(2);
                        uint64_t value;
                        std::istringstream iss(str);
                        iss >> value;

                        _sceneIDs.insert({character, value});
                    }
                }
            }
        }
    }
}