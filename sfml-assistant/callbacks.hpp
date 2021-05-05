#pragma once
#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <memory>

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <TGUI/Widgets/Button.hpp>


class Chatbox;
class AI;

void sendButtonOnClick(tgui::GuiSFML& tgUI, Chatbox& chatbox, AI& ai);

void panelButtonOnClick(tgui::Button::Ptr button, Chatbox& chatbox, AI& ai);

#endif // !CALLBACKS_HPP