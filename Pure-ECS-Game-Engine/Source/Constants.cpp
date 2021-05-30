#include "stdafx.h"
#include "../Include/Constants.h"

const char* Constants::Window::WINDOW_NAME = "Engine";
const unsigned Constants::Window::WINDOW_WIDTH = 800;
const unsigned Constants::Window::WINDOW_HEIGHT = 600;

const char* Constants::ConsoleColors::GREEN = "\u001b[32m";
const char* Constants::ConsoleColors::YELLOW = "\u001b[33m";
const char* Constants::ConsoleColors::RED = "\u001b[31m";
const char* Constants::ConsoleColors::RESET = "\u001b[0m";

const Color Constants::TextureColors::RED = { 255, 0, 0, 255 };
const Color Constants::TextureColors::GREEN = { 0, 255, 0, 255 };
const Color Constants::TextureColors::BLUE = { 0, 0, 255, 255 };