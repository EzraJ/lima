#include "lima/TextInput.hpp"
#include "game/game_main.hpp"


int game_main(int argc, char** argv, lima::render* currentRender, lima::keyboard* currentKeyboard){

	currentRender->globalScreen->setFunc([](lima::bean* b, uint xPos, uint yPos, float xGL, float yGL, float time){
	    float x = ((xGL + 1)/2) * 255;
	    float y = ((yGL + 1)/2) * 255;
	    b->setBG((int)x, (int)y, (sin(time)+1.0)/2.0 * 255);
        //b->setChar(' ');
	});
	
	lima::TextInput* myInp = new lima::TextInput(currentRender, currentKeyboard, 10, 10, 5, 5);
	myInp->SetActive(true);
	while(myInp->EnteredText() != "quit"){

	}

	delete myInp;

    return 1;
}
