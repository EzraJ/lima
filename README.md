# Lima
## What is Lima?
Lima is a fast C++ framework that allows for the creation of TUI applications. Lima provides real time TUI elements and handles basic input/output. 

## Examples
Check for terminal input and update with program uptime.
```cpp
#include "game/game_main.hpp"
#include "lima/TextInput.hpp"
#include "lima/Vector2.hpp"
#include "lima/LabelVariable.hpp"

int game_main(int argc, char** argv, lima::render* CurrentRender, lima::keyboard* CurrentKeyboard){	
	lima::TextInput myInp(CurrentRender, CurrentKeyboard, 20, 10, 5, 5);
	myInp.SetActive(true);

	float time = -(float) ((float)std::chrono::duration_cast<std::chrono::milliseconds>(CurrentRender->timePt - std::chrono::high_resolution_clock::now()).count() / 1000.0f);

	lima::LabelVariable<float> myLabel(CurrentRender, &time, lima::Vector2(10, 30), lima::Vector2(5, 5));

	while(myInp.EnteredText() != "quit"){
		time = -(float) ((float)std::chrono::duration_cast<std::chrono::milliseconds>(CurrentRender->timePt - std::chrono::high_resolution_clock::now()).count() / 1000.0f);
		//return 1;
	}

    return 0;
}
```

Check for terminal input and render a screen.
```cpp
#include <cmath>

#include "game/game_main.hpp"
#include "lima/screen_info.hpp"
#include "lima/TextInput.hpp"
#include "lima/LabelVariable.hpp"

int game_main(int argc, char** argv, lima::render* CurrentRender, lima::keyboard* CurrentKeyboard){
	lima::screen* myScr = CurrentRender->CreateScreen(10, 1, 20, 20);
	
	myScr->setFunc([](lima::screen_info info){
		float x = ((info.normX + 1)/2) * 255;
		float y = ((info.normY + 1)/2) * 255;
		info.beanPtr->setBG((unsigned char) x, (unsigned char) y, (sin(info.time*2.0)+1.0)/2.0 * 255);
	});
	
	lima::TextInput myInp(CurrentRender, CurrentKeyboard, 20, 10, 5, 5);
	myInp.SetActive(true);

	while(myInp.EnteredText() != "quit"){

	}

    return 0;
}
```
