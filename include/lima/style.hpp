#pragma once

namespace lima{
    struct style{
        //bool reset = false; // Goes at the end of the sequence [0m
        bool bold = false; // 1m ~ 22m
        bool dim = false; // 2m ~ 22m
        bool italic = false; // 3m ~ 23m
        bool underline = false; // 4m ~ 24m
        bool blinking = false; // 5m ~ 25m
        bool inverse = false; // 7m ~ 27m
        bool invisible = false; // 8m ~ 28m -- What's the point of this? You have to print text to change it...
        bool strikethrough = false; // 9m ~ 29m
        style(bool boldIn = false, bool dimIn = false, bool italicIn = false, bool underlineIn = false, bool blinkingIn = false, bool inverseIn = false, bool invisibleIn = false,bool strikethroughIn = false){
            bold = boldIn;
            dim = dimIn;
            italic = italicIn;
            underline = underlineIn;
            blinking = blinkingIn;
            inverse = inverseIn;
            invisible = invisibleIn;
            strikethrough = strikethroughIn;
        }
    };
}