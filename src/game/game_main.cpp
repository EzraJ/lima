#include "game/game_main.hpp"

int game_main(int argc, char** argv, lima::render* currentRender, lima::keyboard* currentKeyboard){

	lima::screen* myScr = currentRender->CreateScreen(1, 1, 20, 20);
	
	myScr->setFunc([](lima::screen_info info){
		float x = ((info.normX + 1)/2) * 255;
		float y = ((info.normY + 1)/2) * 255;
		info.beanPtr->setBG((unsigned char) x, (unsigned char) y, (sin(info.time)+1.0)/2.0 * 255)
	});

	lima::TextInput* myInp = new lima::TextInput(currentRender, currentKeyboard, 10, 10, 5, 5);
	myInp->SetActive(true);
	while(myInp->EnteredText() != "quit"){

	}

	delete myInp;

    return 1;
}
