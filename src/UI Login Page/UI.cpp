#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UI.h"
//--------------------------------------------------------------
// Login Button
LoginButton::LoginButton(float x, float y, const std::string& imagePath)
{
	if (!texture.loadFromFile(imagePath))		
		std::cout << "Can't load image login\n";
	sprite.setTexture(texture);
	sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}

void LoginButton::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void LoginButton::isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, std::string& user, std::string& pass, int& page)
{		
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			
		if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            user = username.getString().toAnsiString();
            pass = password.getString().toAnsiString();
            page = 1;
		}
	}
	return;
}

//--------------------------------------------------------------
//UsernameBox
UsernameBox::UsernameBox(float x, float y) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile("image/input.png")) {
        // handle error
    }
    float height = texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
    
    label.setFont(font);
    label.setCharacterSize(height * 0.4f);
    label.setPosition(sprite.getPosition().x, sprite.getPosition().y - height / 2);
    label.setFillColor(sf::Color::Black);
    label.setString("Username");
    
    text.setFont(font);
    text.setCharacterSize(height * 0.8f);
    text.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
    text.setFillColor(sf::Color::Black);
}

void UsernameBox::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            active = true;
        else
            active = false;
    }
    if (active) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace) {
                sf::String str = text.getString();
                if (!str.isEmpty()) {
                    str.erase(str.getSize() - 1);
                    text.setString(str);
                }
            }
        }
    }
}

void UsernameBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
    window.draw(label);
}

//--------------------------------------------------------------
// PasswordBox
PasswordBox::PasswordBox(float x, float y) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile("image/input.png")) {
        // handle error
    }
    float height = texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    label.setFont(font);
    label.setCharacterSize(height * 0.4f);
    label.setPosition(sprite.getPosition().x, sprite.getPosition().y - height / 2);
    label.setFillColor(sf::Color::Black);
    label.setString("Password");

    text.setFont(font);
    text.setCharacterSize(height * 0.8f);
    text.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
    text.setFillColor(sf::Color::Black);

    star.setFont(font);
    star.setCharacterSize(height * 0.8f);
    star.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
    star.setFillColor(sf::Color::Black);
}
void PasswordBox::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            active = true;
        else
            active = false;
    }
    if (active) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
                star.setString(star.getString() + "*");
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace) {
                sf::String str = text.getString();
                if (!str.isEmpty()) {
                    str.erase(str.getSize() - 1);
                    text.setString(str);
                }
            }
        }
    }
}
void PasswordBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(star);
    window.draw(label);
}



//--------------------------------------------------------------
// DeleteButton
DeleteButton::DeleteButton(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    sprite.setTexture(texture);
    sprite.setPosition(1000,300);
}

void DeleteButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void DeleteButton::isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, sf::Text& star) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            username.setString("");
            password.setString("");
            star.setString("");
        }
    }
    return;
}

