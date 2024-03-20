#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UI.h"
#include "run.h"
#include "readCSV.h"

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
bool LoginButton::isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, std::string& user, std::string& pass) {		
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
// UsernameBox
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
            if (event.text.unicode < 128 && event.text.unicode != 8) {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::BackSpace) {
                std::string str = text.getString().toAnsiString();
                if (!str.empty()) {
                    str.pop_back();
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
        cout << "Can't load font\n";
    }
    if (!texture.loadFromFile("image/TextBox.png")) {
        cout << "Can't load image\n";
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
            switch (event.text.unicode) {
            case 8: {
                std::string str = text.getString().toAnsiString();
                std::string sStar = star.getString().toAnsiString();
                if (!str.empty() && !sStar.empty()) {
                    str.pop_back();
                    text.setString(str);

                    sStar.pop_back();
                    star.setString(sStar);
                }
                break;
            }
            default: {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
                star.setString(star.getString() + "*");
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
// HomePage
HomePage::HomePage(float x, float y, const std::string& imagePath1, const std::string& imagePath2) {
    if (!texture1.loadFromFile(imagePath1))
        std::cout << "Can't load image login\n";
    texture1.setSmooth(1);
    sprite1.setTexture(texture1);
    sprite1.setPosition(x - sprite1.getGlobalBounds().width / 2, y - sprite1.getGlobalBounds().height / 2);

    if (!texture2.loadFromFile(imagePath2))
        std::cout << "Can't load image login\n";
    texture2.setSmooth(1);
    sprite2.setTexture(texture2);
    sprite2.setPosition(x - sprite2.getGlobalBounds().width / 2, y - sprite2.getGlobalBounds().height / 2);
}
void HomePage::draw(sf::RenderWindow& window,bool isStaff) {
    isStaff ? window.draw(sprite1) : window.draw(sprite2);
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

//--------------------------------------------------------------
// Backgound
Background::Background(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
void Background::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(sprite);
}

//--------------------------------------------------------------
// ClassesButton
ClassesButton::ClassesButton(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
bool ClassesButton::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) 
            return true;
    }
    return false;
}
void ClassesButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//--------------------------------------------------------------
// SchoolyearsButton
SchoolyearsButton::SchoolyearsButton(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
bool SchoolyearsButton::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void SchoolyearsButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//--------------------------------------------------------------
// ViewingPage
ViewingPage::ViewingPage(float x, float y, const std::string& imagePath, std::string sText) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) 
        cout << "Can't load font\n";
    
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    text.setFont(font);
    text.setCharacterSize(45.0f * 0.5f);
    text.setFillColor(sf::Color::White);
    text.setString(sText);

    // Position text
    text.setPosition(180.0f, 91.0f);
}
void ViewingPage::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// Button200x45
Button200x45::Button200x45(float x, float y, const std::string& imagePath, std::string sText) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    float height = texture.getSize().y;
    text.setFont(font);
    text.setCharacterSize(height * 0.5f);
    text.setFillColor(sf::Color::Black);
    text.setString(sText);
    // Position
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    sf::FloatRect spriteRect = sprite.getGlobalBounds();
    text.setPosition(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f);

    
}
bool Button200x45::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void Button200x45::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// Button400x45
Button400x45::Button400x45(float x, float y, const std::string& imagePath, std::string sText) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) 
        cout << "Can't load font\n";
    
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    float height = texture.getSize().y;
    text.setFont(font);
    text.setCharacterSize(height * 0.5f);
    text.setFillColor(sf::Color::Black);
    text.setString(sText);
    // Position
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    sf::FloatRect spriteRect = sprite.getGlobalBounds();
    text.setPosition(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f);
}
bool Button400x45::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void Button400x45::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// LogOutButton
LogOutButton::LogOutButton(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
bool LogOutButton::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void LogOutButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

