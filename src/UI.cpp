#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UI.h"
#include "run.h"
#include "funcLoginPage.h"

//--------------------------------------------------------------
// Login Box
LoginBox::LoginBox(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
void LoginBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//--------------------------------------------------------------
// Login Button
LoginButton::LoginButton(float x, float y, const std::string& imagePath)
{
	if (!texture.loadFromFile(imagePath))		
		std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
	sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
void LoginButton::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
bool LoginButton::isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, std::string& user, std::string& pass)
{		
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {		
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            user = username.getString().toAnsiString();
            pass = password.getString().toAnsiString();
            return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
//UsernameBox
UsernameBox::UsernameBox(float x, float y) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile("image/TextBox.png")) {
        // handle error
    }
    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
 
    text.setFont(font);
    text.setCharacterSize(height * 0.6f);
    text.setPosition(sprite.getPosition().x+10, sprite.getPosition().y + height * 0.6f / 3.7f);
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
}

//--------------------------------------------------------------
// PasswordBox
PasswordBox::PasswordBox(float x, float y) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile("image/TextBox.png")) {
        // handle error
    }
    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    star.setFont(font);
    star.setCharacterSize(height * 0.6f);
    star.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y + height * 0.6f / 3.7f);
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

//--------------------------------------------------------------
// LeftHome
LeftHome::LeftHome(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
void LeftHome::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//--------------------------------------------------------------
// CheckStaffButton
CheckStaffButton::CheckStaffButton(float x, float y, const std::string& imagePath1, const std::string& imagePath2) {
    if (!texture1.loadFromFile(imagePath1))
        std::cout << "Can't load image login\n";
    if (!texture2.loadFromFile(imagePath2))
        std::cout << "Can't load image login\n";
    
    texture1.setSmooth(1);
    sprite1.setTexture(texture1);
    sprite1.setPosition(x - sprite1.getGlobalBounds().width / 2, y - sprite1.getGlobalBounds().height / 2);

    texture2.setSmooth(1);
    sprite2.setTexture(texture2);
    sprite2.setPosition(x - sprite2.getGlobalBounds().width / 2, y - sprite2.getGlobalBounds().height / 2);
}
void CheckStaffButton::draw(sf::RenderWindow& window, bool& checked) {
    if (checked)
        window.draw(sprite2);
    else
        window.draw(sprite1);
}
bool CheckStaffButton::isClick(sf::RenderWindow& window, bool& checked) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite1.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            if (checked) checked = false;
            else checked = true;
            return true;
        }
    }
    return false;
}