#include "lima/TextInput.hpp"
#include "game/game_main.hpp"


int game_main(int argc[[maybe_unused]], char** argv[[maybe_unused]], lima::render* currentRender[[maybe_unused]], lima::keyboard* currentKeyboard[[maybe_unused]]){

    

	currentRender->globalScreen->setFunc([](lima::bean* b[[maybe_unused]], uint xPos[[maybe_unused]], uint yPos[[maybe_unused]], float xGL[[maybe_unused]], float yGL[[maybe_unused]], float time[[maybe_unused]]){
	    float x = ((xGL + 1)/2) * 255;
	    float y = ((yGL + 1)/2) * 255;
	    b->setBG((int)x, (int)y, (sin(time)+1.0)/2.0 * 255);
        //b->setChar(' ');
	});
	
    //std::this_thread::sleep_for(std::chrono::seconds(3));

	lima::TextInput* myInp = new lima::TextInput(currentRender, currentKeyboard, 10, 10, 5, 5);
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	//myInp->EnteredText();
	while(myInp->EnteredText() != "quit"){

	}

    return 1;
}
