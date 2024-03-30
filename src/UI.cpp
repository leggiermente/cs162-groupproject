#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UI.h"
#include "run.h"
#include "readCSV.h"

//--------------------------------------------------------------
// Button
Button::Button(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
}
bool Button::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//--------------------------------------------------------------
// Login Button
LoginButton::LoginButton(float x, float y, const std::string& imagePath) : Button(x, y, imagePath) {}
bool LoginButton::isClicked(sf::RenderWindow& window,sf::Event event, sf::Text& username, sf::Text& password, std::string& user, std::string& pass) {		
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
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
// InputBox
InputBox::InputBox(float x, float y, const std::string& imagePath) : Button(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile(imagePath)) {
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
void InputBox::isClicked(const sf::Event& event, sf::RenderWindow& window) {
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
void InputBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// PasswordBox
PasswordBox::PasswordBox(float x, float y, const std::string& imagePath) : InputBox(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    if (!texture.loadFromFile(imagePath)) {
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
void PasswordBox::isClicked(const sf::Event& event, sf::RenderWindow& window) {
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
bool CheckStaffButton::isClick(sf::RenderWindow& window,sf::Event event, bool& checked) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
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
// TextBox
TextBox::TextBox(float x, float y, const std::string& imagePath, std::string sText) : Button(x,y, imagePath){
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
		cout << "Can't load font\n";
	}
    if (!texture.loadFromFile(imagePath)) {
		cout << "Can't load image\n";
	}
	float height = texture.getSize().y;
	texture.setSmooth(1);
	sprite.setTexture(texture);
	sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

	text.setFont(font);
	text.setCharacterSize(height * 0.5f);
	text.setPosition(sprite.getPosition().x + 15, sprite.getPosition().y + height * 0.5f * 0.35);
	text.setFillColor(sf::Color::White);
	text.setString(sText);
}
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
	window.draw(text);
}

//--------------------------------------------------------------
// LinkedButton
LinkedButton::LinkedButton(float x, float y, const std::string& imagePath, std::string sText) {
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
bool LinkedButton::isClicked(sf::RenderWindow& window,sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void LinkedButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// ProfileText
ProfileText::ProfileText(std::string sFirstName, std::string sLastName,
    std::string sID, std::string sDD_MM_YY, std::string sSocialID,
    std::string sGender) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    else {
        firstName.setFont(font);
        firstName.setCharacterSize(25.0f);
        firstName.setPosition(230.0f, 255.0f);
        firstName.setFillColor(sf::Color::Black);
        firstName.setString(sFirstName);

        lastName.setFont(font);
        lastName.setCharacterSize(25.0f);
        lastName.setPosition(478.0f, 255.0f);
        lastName.setFillColor(sf::Color::Black);
        lastName.setString(sLastName);

        ID.setFont(font);
        ID.setCharacterSize(25.0f);
        ID.setPosition(200.0f, 315.0f);
        ID.setFillColor(sf::Color::Black);
        ID.setString(sID);

        DD_MM_YY.setFont(font);
        DD_MM_YY.setCharacterSize(25.0f);
        DD_MM_YY.setPosition(200.0f, 365.0f);
        DD_MM_YY.setFillColor(sf::Color::Black);
        DD_MM_YY.setString(sDD_MM_YY);

        socialID.setFont(font);
        socialID.setCharacterSize(25.0f);
        socialID.setPosition(200.0f, 415.0f);
        socialID.setFillColor(sf::Color::Black);
        socialID.setString(sSocialID);

        gender.setFont(font);
        gender.setCharacterSize(25.0f);
        gender.setPosition(200.0f, 465.0f);
        gender.setFillColor(sf::Color::Black);
        gender.setString(sGender);
    }
}
ProfileText::ProfileText(std::string sFirstName, std::string sLastName,std::string sID) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    else {
        firstName.setFont(font);
        firstName.setCharacterSize(25.0f);
        firstName.setPosition(230.0f, 255.0f);
        firstName.setFillColor(sf::Color::Black);
        firstName.setString(sFirstName);

        lastName.setFont(font);
        lastName.setCharacterSize(25.0f);
        lastName.setPosition(478.0f, 255.0f);
        lastName.setFillColor(sf::Color::Black);
        lastName.setString(sLastName);

        ID.setFont(font);
        ID.setCharacterSize(25.0f);
        ID.setPosition(200.0f, 315.0f);
        ID.setFillColor(sf::Color::Black);
        ID.setString(sID);
    }
}
void ProfileText::drawStu(sf::RenderWindow& window) {
    window.draw(firstName);
    window.draw(lastName);
    window.draw(ID);
    window.draw(DD_MM_YY);
    window.draw(socialID);
    window.draw(gender);
}
void ProfileText::drawStaff(sf::RenderWindow& window) {
    window.draw(firstName);
    window.draw(lastName);
    window.draw(ID);
}

//--------------------------------------------------------------
// InputYear
InputYear::InputYear(float x, float y, const std::string& imagePath, std::string sHeadname) : InputBox(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile(imagePath)) {
        // handle error
    }
    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);

    text.setFont(font);
    text.setCharacterSize(height * 0.6f);
    text.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y + height * 0.6f / 3.7f);
    text.setFillColor(sf::Color::Black);

    tHeadname.setFont(font);
    tHeadname.setCharacterSize(20.0f);
    tHeadname.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2 - 25.0f);
    tHeadname.setFillColor(sf::Color::Black);
    tHeadname.setString(sHeadname);
}
void InputYear::draw(sf::RenderWindow& window) {
    window.draw(tHeadname);
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// Line
Line::Line(float x, float y, float width, float height) {
    stick.setSize(sf::Vector2f(width, height));
    stick.setFillColor(sf::Color::Black);
    stick.setPosition(x, y);
}
void Line::draw(sf::RenderWindow& window) {
	window.draw(stick);
}


