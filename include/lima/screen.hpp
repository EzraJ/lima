#include <functional>
#include "lima/render.hpp"

// TODO: Screen manager to handle stuff like window resizes

namespace lima{
    class screen{
        public:
            screen(){

            	
            }

            void setFunc(std::function<void(uint, uint, float, float)> funcIn){
                func = funcIn;
            }

			~screen(){
				
			}

        private:

            std::function<void(uint, uint, float, float)> func;

    };
}
