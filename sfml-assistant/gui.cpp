#include "gui.hpp"

#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBox.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include "callbacks.hpp"

#include <iostream>


GUI::GUI() 
	: aiPtr(nullptr)
	, buttonsCounter(0)
{}

GUI::~GUI() {
	aiPtr = nullptr;
}

void GUI::init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font) {
	tgUI.setTarget(*window);

	chatbox.init(window, font);
}

void GUI::build(AI& ai) {
	auto messageEditBoxGroup = tgui::Group::create();
	messageEditBoxGroup->setSize("99%", "5%");
	messageEditBoxGroup->setPosition("50%", "99%");
	messageEditBoxGroup->setOrigin(0.5f, 1.f);

	auto messageBox = tgui::EditBox::create();
	messageBox->setSize("77%", "100%");
	messageBox->setOrigin(0.0f, 0.5f);
	messageBox->setPosition("3%", "50%");
	messageBox->setTextSize(17);
	messageEditBoxGroup->add(messageBox, "message_edit_box");

	auto sendButton = tgui::Button::create("Send");
	sendButton->setSize("14%", "100%");
	sendButton->setOrigin(1.0f, 0.5f);
	sendButton->setPosition("97%", "50%");
	sendButton->onClick(&sendButtonOnClick, std::ref(tgUI), std::ref(chatbox), std::ref(ai));
	messageEditBoxGroup->add(sendButton, "send_message_button");

	auto scrollablePanel = tgui::ScrollablePanel::create();
	scrollablePanel->setSize("100%", 0);
	scrollablePanel->setOrigin(0.f, 1.f);
	scrollablePanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	scrollablePanel->setPosition(0, "message_edit_box_group.top - 10");


	tgUI.add(messageEditBoxGroup, "message_edit_box_group");
	tgUI.add(scrollablePanel, "options_panel");

	tgUI.get("message_edit_box")->setFocused(true);

	chatbox.setOffsetWidgetPtr(std::dynamic_pointer_cast<tgui::ScrollablePanel>(tgUI.get("options_panel")));

	onEnterPressed = sendButtonOnClick;
	aiPtr = &ai;
}

void GUI::draw() {
	chatbox.draw();
	tgUI.draw();
}

void GUI::handleEvent(const sf::Event& event) {
	tgUI.handleEvent(event);

	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Enter)
			onEnterPressed(tgUI, chatbox, *aiPtr);
}

void GUI::newMessage(Chatbox::Sender sender, const std::string& text) {
	chatbox.pushBack(sender, text);
}

tgui::GuiSFML& GUI::getTgUI() {
	return tgUI;
}

void GUI::addButtonToPanel(const std::string& text) {
	auto panel = std::dynamic_pointer_cast<tgui::ScrollablePanel>(tgUI.get("options_panel"));
	auto button = tgui::Button::create(text);
	button->setSize("100%", "30%");
	button->setOrigin(0.f, 0.f);
	button->onClick(&panelButtonOnClick, button, std::ref(chatbox), std::ref(*aiPtr));

	if (!buttonsCounter) {
		button->setPosition("0%", "0%");

		panel->add(button, "panel_button_1");
		panel->setSize("100%", "20%");

		buttonsCounter = 1;
	} else {
		std::string previousButtonName = "panel_button_" + std::to_string(buttonsCounter);
		std::string thisButtonName = "panel_button_" + std::to_string(buttonsCounter + 1);

		button->setPosition("0%", std::string(previousButtonName + ".bottom - 1").c_str());

		panel->add(button, thisButtonName.c_str());

		buttonsCounter++;
	}
}

void GUI::clearPanel() {
	auto panel = std::dynamic_pointer_cast<tgui::ScrollablePanel>(tgUI.get("options_panel"));

	panel->setSize("100%", "0%");
	panel->removeAllWidgets();

	buttonsCounter = 0;
}