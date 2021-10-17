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
#include "core/engine/block.hpp"
#include <algorithm>
#include <utility>



namespace lima{
    namespace core{
        namespace engine{
            class scene{
                public:

                /*
                    Note to self: file streams aren't copy-able. This is a PITA. Big time. If I somehow haven't made all of the fstreams moved already via all copy/move constructs/operators, do so
                */


                    scene(){
                        _sceneID = 0;
                    }
                    
                    scene(const scene& _scene){
                        _sceneID = _scene._sceneID;
                        _blockData = _scene._blockData;

                        //std::swap(_blockFile, _scene._blockFile);
                        //std::swap(_idData, _scene._idData);
                        
                        _blockFile = std::move(  const_cast<scene&>(_scene)._blockFile  ); // No.
                        _idData = std::move(  const_cast<scene&>(_scene)._idData  );       // Also No.
                        //_blockFile = std::move(_scene._blockFile);
                        //_idData = std::move(_scene._idData);

                        _dimensions = _scene._dimensions;
                        _levelName = _scene._levelName;
                        _IDLOAD = _scene._IDLOAD;
                        _cleared = _scene._cleared;
                    }
                    
                    scene(uint64_t id);
                    scene(vector2 dims, uint64_t id = 0); // A constructor to automatically make a scene with dimenions (dim.x, dim.y), with blocks given id 0(don't render/physics), and characters "<"
                    

                    scene& operator=(scene other){
                        _sceneID = other._sceneID;
                        _blockData = other._blockData;

                        std::swap(_blockFile, other._blockFile);
                        std::swap(_idData, other._idData);
                        
                        _dimensions = other._dimensions;
                        _levelName = other._levelName;
                        _IDLOAD = other._IDLOAD;
                        _cleared = other._cleared;
                        return *this;
                    }

                    /*scene& operator=(const scene& other){
                        _sceneID = other._sceneID;
                        _blockData = other._blockData;
                        //std::swap(_blockFile, other._blockFile);
                        _blockFile = std::move(  const_cast<scene&>(other)._blockFile  ); // No.
                        //_blockFile = std::move((const_cast<scene&>((&other)._blockFile)));
                        //_idData = std::move(other._idData);
                        _idData = std::move(  const_cast<scene&>(other)._idData  );
                        //std::swap(_idData, other._idData);
                        _dimensions = other._dimensions;
                        _levelName = other._levelName;
                        _IDLOAD = other._IDLOAD;
                        _cleared = other._cleared;
                        return *this;
                    }*/

                    scene& operator=(scene&& other){
                        _sceneID = other._sceneID;
                        _blockData = other._blockData;
                        //std::swap(_blockFile, other._blockFile);
                        _blockFile = std::move(other._blockFile);
                        _idData = std::move(other._idData);
                        //std::swap(_idData, other._idData);
                        _dimensions = other._dimensions;
                        _levelName = other._levelName;
                        _IDLOAD = other._IDLOAD;
                        _cleared = other._cleared;
                        return *this;
                    }

                    /*void operator=(scene& rhs){
                        _fileName = rhs._fileName;
                        _sceneID = rhs._sceneID;
                        _blockData = rhs._blockData;
                        rhs._blockFile.swap(_blockFile);
                        //_blockFile = rhs._blockFile;
                        rhs._idData.swap(_idData);
                        //_idData = rhs._idData;
                        _dimensions = rhs._dimensions;
                        _levelName = rhs._levelName;
                        _IDLOAD = rhs._IDLOAD;
                        _cleared = rhs._cleared;

                    }*/

                    //scene(const scene&) = default; // Non-copyable
                    //scene& operator=(const scene&) = default; // non-copyable

                    //scene(scene&& in) = default;

                    //scene& operator=(scene&&) = default;
                    
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
                                block.changeID(0);
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