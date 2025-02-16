#pragma once
#include "lima/render.hpp"
#include "lima/keyboard.hpp"
#include <chrono>
#include <thread>

int game_main(int argc, char** argv, lima::render* currentRender, lima::keyboard* currentKeyboard);