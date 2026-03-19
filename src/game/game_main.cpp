#include <cmath>

#include "game/game_main.hpp"

#include "lima/screen_info.hpp"
#include "lima/TextInput.hpp"

lima::style beanStyle;

int game_main(int argc, char** argv, lima::render* CurrentRender, lima::keyboard* CurrentKeyboard){

	lima::screen* myScr = CurrentRender->CreateScreen(1, 1, 10, 10);
	

	myScr->setFunc([](lima::screen_info info){
		//float x = ((info.normX + 1)/2) * 255;
		//float y = ((info.normY + 1)/2) * 255;
		//info.beanPtr->setBG((unsigned char) x, (unsigned char) y, (sin(info.time)+1.0)/2.0 * 255);
		info.beanPtr->setStyle(beanStyle);
		info.beanPtr->setChar('d');
	});

	//sleep(10);
	

	lima::screen* myScr2 = CurrentRender->CreateScreen(10, 1, 20, 20);
	
	myScr2->setFunc([](lima::screen_info info){
		float x = ((info.normX + 1)/2) * 255;
		float y = ((info.normY + 1)/2) * 255;
		info.beanPtr->setBG((unsigned char) x, (unsigned char) y, (sin(info.time*2.0)+1.0)/2.0 * 255);
	});
	
	lima::TextInput myInp(CurrentRender, CurrentKeyboard, 20, 10, 5, 5);
	myInp.SetActive(true);
	
	while(myInp.EnteredText() != "quit"){
		if(myInp.EnteredText() == "I"){
			beanStyle.italic = true;
		}else if (myInp.EnteredText() == "NI"){
			beanStyle.italic = false;
		}

		if(myInp.EnteredText() == "U"){
			beanStyle.underline = true;
		}else if (myInp.EnteredText() == "NU"){
			beanStyle.underline = false;
		}

		if(myInp.EnteredText() == "B"){
			beanStyle.blinking = true;
		}else if(myInp.EnteredText() == "NB"){
			beanStyle.blinking = false;
		}

		if(myInp.EnteredText() == "INV"){
			beanStyle.inverse = true;
		}else if(myInp.EnteredText() == "NINV"){
			beanStyle.inverse = false;
		}

		if(myInp.EnteredText() == "S"){
			beanStyle.strikethrough = true;
		}else if (myInp.EnteredText() == "NS"){
			beanStyle.strikethrough = false;
		}

		if(myInp.EnteredText() == "INVIS"){
			beanStyle.invisible = true;
		}else if (myInp.EnteredText() == "NINVIS"){
			beanStyle.invisible = false;
		}

		if(myInp.EnteredText() == "BOLD"){
			beanStyle.bold = true;
		}else if (myInp.EnteredText() == "NBOLD"){
			beanStyle.bold = false;
		}

		if(myInp.EnteredText() == "DIM"){
			beanStyle.dim = true;
		}else if (myInp.EnteredText() == "NDIM"){
			beanStyle.dim = false;
		}
		

	}

    return 0;
}
