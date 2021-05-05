#include <string>
#include <iostream>

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <TGUI/Widgets/EditBox.hpp>

#include "callbacks.hpp"
#include "chatbox.hpp"
#include "ai.hpp"


void sendButtonOnClick(tgui::GuiSFML& tgUI, Chatbox& chatbox, AI& ai) {
	tgui::EditBox::Ptr messageEditBox = std::dynamic_pointer_cast<tgui::EditBox>(tgUI.get("message_edit_box"));

	std::string messageText = sf::String(messageEditBox->getText());
	messageEditBox->setText("");
	messageEditBox->setFocused(true);

	if (messageText.size() > 0) {
		chatbox.pushBack(Chatbox::Sender::User, messageText);
		ai.processMessage(messageText);
	}
}

void panelButtonOnClick(tgui::Button::Ptr button, Chatbox& chatbox, AI& ai) {
	std::string buttonText = sf::String(button->getText());

	chatbox.pushBack(Chatbox::Sender::User, buttonText);
	ai.processMessage(buttonText);
}