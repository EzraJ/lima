#include "game/game_main.hpp"


int game_main(int argc[[maybe_unused]], char** argv[[maybe_unused]], lima::render* currentRender){

    

	currentRender->globalScreen->setFunc([](lima::bean* b[[maybe_unused]], uint xPos[[maybe_unused]], uint yPos[[maybe_unused]], float xGL[[maybe_unused]], float yGL[[maybe_unused]], float time[[maybe_unused]]){
	    float x = ((xGL + 1)/2) * 255;
	    float y = ((yGL + 1)/2) * 255;
	    b->setBG((int)x, (int)y, (sin(time)+1.0)/2.0 * 255);
        b->setChar(' ');
	});
	
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 1;
}
