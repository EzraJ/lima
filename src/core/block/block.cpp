#include "core/engine/block/block.hpp"

namespace lima{
    namespace core{
        namespace engine{
            vector2 block::getPos(){
                return _pos;
            }

            block::block(vector2 pos, uint64_t id, char inChar){
                block::_id = id;
                block::_pos = pos;
                block::_myChar = inChar;
            }

            char block::getRender(){
                return block::_myChar;
            }

            uint64_t block::getID(){
                return block::_id;
            }

            void block::changeID(uint64_t id){
                block::_id = id;
            }

            void block::swapPosition(block& other){ // We don't ever want a space "without a block", so *always* swap instead of changing position
                std::swap(this->_pos, other._pos);
                std::swap(this->_id, other._id);
                std::swap(this->_myChar, other._myChar);
            }
        }
    }
}