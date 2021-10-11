// Scene class contains:
// Scene blocks
// Loading/Saving[?] level files
// Handle manifest files
// Correspond with IDs


// Because we're storing everything in a vector<vector>, it goes:
// _blockData[y][x]

#pragma once
#include <cstdint>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <unordered_map>
#include <sstream>
#include "core/engine/block/block.hpp"


namespace lima{
    namespace core{
        namespace engine{
            class scene{
                public:

                    scene(uint64_t id = 0);
                    ~scene();
                    void openFile(std::string fName);
                    void openManifest(std::string fName);
                    std::vector<std::vector<lima::engine::block>>& sceneData();

                    /*scene(uint64_t id = 0){
                        _sceneID = id;
                    }
                    ~scene(){
                        _blockFile.close();
                        _idData.close();
                    }

                    

                    void openFile(std::string fName){

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
                                _blockData[y-1].push_back(lima::engine::block(vector2(x, y), blockID, c));
                                x++;
                            }
                            y++;
                            x=1;
                        }

                    }
                    void openManifest(std::string fName){
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


                    std::vector<std::vector<lima::engine::block>>& sceneData(){
                        return _blockData;
                    }*/
                    

                private:
                    uint64_t _sceneID = 0;
                    std::vector<std::vector<lima::engine::block>> _blockData;
                    std::unordered_map<char, uint64_t> _sceneIDs;
                    std::ifstream _blockFile;
                    std::ifstream _idData;
                    vector2 _dimensions = vector2(0,0);
                    std::string _levelName;
                    bool _IDLOAD = false;


            };


        }
    }
}