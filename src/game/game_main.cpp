#include <cmath>

#include "game/game_main.hpp"

#include "lima/screen_info.hpp"

int game_main(int argc, char** argv, lima::render* CurrentRender, lima::keyboard* CurrentKeyboard){

	lima::screen* myScr = CurrentRender->CreateScreen(1, 1, 20, 20);
	
	myScr->setFunc([](lima::screen_info info){
		float x = ((info.normX + 1)/2) * 255;
		float y = ((info.normY + 1)/2) * 255;
		info.beanPtr->setBG((unsigned char) x, (unsigned char) y, (sin(info.time)+1.0)/2.0 * 255)
	});

	lima::TextInput myInp(CurrentRender, CurrentKeyboard, 10, 10, 5, 5);
	myInp.SetActive(true);
	while(myInp.EnteredText() != "quit"){

	}

    return 1;
}
