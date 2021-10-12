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
                    std::vector<std::vector<lima::core::engine::block>>& sceneData(){
                        return _blockData;
                    }
                private:
                    uint64_t _sceneID = 0;
                    std::vector<std::vector<lima::core::engine::block>> _blockData;
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