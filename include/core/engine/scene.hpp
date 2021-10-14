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

                    std::string getFileName(){
                        return _fileName;
                    }
                    std::vector<std::vector<lima::core::engine::block>>& sceneData(){
                        return _blockData;
                    }

                    void clear(){
                        for(auto& e : _blockData){
                            for(auto& block : e){
                                e.changeID(0); 
                            }
                        }
                        _cleared = true;
                    }

                    bool isClear(){
                        return _cleared;
                    }

                    void setID(uint64_t id){
                        _sceneID = id;
                    }

                    uint64_t getID(){
                        return _sceneID;
                    }


                    friend void swap(scene& lhs, scene& rhs){
                        std::swap(lhs._fileName, rhs._fileName);
                        std::swap(lhs._sceneID, rhs._sceneID);
                        std::swap(lhs._blockData, rhs._blockData);
                        std::swap(lhs._blockFile, rhs._blockFile);
                        std::swap(lhs._idData, rhs._idData);
                        std::swap(lhs._dimensions, rhs._dimensions);
                        std::swap(lhs._levelName, rhs._levelName);
                        std::swap(lhs._IDLOAD, rhs._IDLOAD);
                        std::swap(lhs._cleared, rhs._cleared);
                        
                    }

                private:
                    std::string _fileName;
                    uint64_t _sceneID = 0;
                    std::vector<std::vector<lima::core::engine::block>> _blockData;
                    std::unordered_map<char, uint64_t> _sceneIDs;
                    std::ifstream _blockFile;
                    std::ifstream _idData;
                    vector2 _dimensions = vector2(0,0);
                    std::string _levelName;
                    bool _IDLOAD = false;
                    bool _cleared = false;
            };
        }
    }
}