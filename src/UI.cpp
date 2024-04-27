#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UI.h"
#include "run.h"
#include "HandleData.h"

//--------------------------------------------------------------
// Button
Button::Button(float x, float y, const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);

    outline.setSize(sprite.getGlobalBounds().getSize());
    outline.setPosition(sprite.getPosition());
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2.0f);
    outline.setOutlineColor(sf::Color::Transparent);
}
bool Button::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            return true;
    }
    return false;
}
void Button::isHovering(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
        isHover = true; // Change color to red when mouse hovers over
    }
    else {
        isHover = false; // Change color back to white when mouse is not hovering
    }
    window.draw(sprite);
}
void Button::draw(sf::RenderWindow& window) {
    if (isHover) {
        outline.setOutlineColor(sf::Color(58, 155, 220));
    }
    else {
        outline.setOutlineColor(sf::Color::Transparent);
    }
    window.draw(sprite);
    window.draw(outline);
}

//--------------------------------------------------------------
// Login Button
LoginButton::LoginButton(float x, float y, const std::string& imagePath) : Button(x, y, imagePath) {}
bool LoginButton::isClicked(sf::RenderWindow& window, sf::Event event, sf::Text& username, sf::Text& password, std::string& user, std::string& pass) {		
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
    sprite.setPosition(x, y);
 
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(x + 10, y + 10);
    text.setFillColor(sf::Color::Black);

    textDisplay = text;
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
    if (active) {
        textDisplay.setString(text.getString() + "|");
        window.draw(textDisplay);
    }
    else 
        window.draw(text);
}

//--------------------------------------------------------------
// PasswordBox
PasswordBox::PasswordBox(float x, float y, const std::string& imagePath, const std::string &sHeadname) : InputBox(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    if (!texture.loadFromFile(imagePath)) {
        cout << "Can't load image\n";
    }
    outline.setSize(sprite.getGlobalBounds().getSize());
    outline.setPosition(sprite.getPosition());
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2.0f);
    outline.setOutlineColor(sf::Color::Transparent);

    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);

    star.setFont(font);
    star.setCharacterSize(20);
    star.setPosition(x + 10, y + 10);
    star.setFillColor(sf::Color::Black);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(x + 10, y + 10);
    text.setFillColor(sf::Color::Black);

    tHeadname.setFont(font);
    tHeadname.setCharacterSize(15);
    tHeadname.setPosition(x, y - 20);
    tHeadname.setFillColor(sf::Color::Black);
    tHeadname.setString(sHeadname);
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
void PasswordBox::isHovering(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
		isHover = true; // Change color to red when mouse hovers over
	}
    else {
		isHover = false; // Change color back to white when mouse is not hovering
	}
}
void PasswordBox::drawStar(sf::RenderWindow& window) {
    window.draw(tHeadname);
    if (isHover) {
        outline.setOutlineColor(sf::Color(58, 155, 220));
    }
    else {
        outline.setOutlineColor(sf::Color::Transparent);
    }
    window.draw(sprite);
    window.draw(outline);
    if (active) {
        textDisplay.setString(star.getString() + "|");
        window.draw(textDisplay);
    }
    else window.draw(star);
}
void PasswordBox::drawText(sf::RenderWindow& window) {
    window.draw(tHeadname);
    if (isHover) {
        outline.setOutlineColor(sf::Color(58, 155, 220));
    }
    else {
        outline.setOutlineColor(sf::Color::Transparent);
    }
    window.draw(sprite);
    window.draw(outline);
    if (active) {
		textDisplay.setString(text.getString() + "|");
		window.draw(textDisplay);
	}
	else window.draw(text);
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
	sprite.setPosition(x, y);

	text.setFont(font);
	text.setCharacterSize(18);
	text.setPosition(x + 15, y + 11);
	text.setFillColor(sf::Color::White);
	text.setString(sText);
}
TextBox::TextBox(float x, float y, const std::string& imagePath, std::string sText, std::string sColor) : Button(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    if (!texture.loadFromFile(imagePath)) {
        cout << "Can't load image\n";
    }
    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    text.setFont(font);
    text.setCharacterSize(height * 0.5f);
    text.setPosition(sprite.getPosition().x + 15, sprite.getPosition().y + height * 0.5f * 0.35);
    text.setFillColor(sf::Color::Black);
    text.setString(sText);
}
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
	window.draw(text);
}

//--------------------------------------------------------------
// LinkedButton
LinkedButton::LinkedButton(float x, float y, const std::string& imagePath, std::string sText) : Button(x,y,imagePath) {
    if (!texture.loadFromFile(imagePath))
        std::cout << "Can't load image login\n";
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    float height = texture.getSize().y;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setString(sText);
    // Position
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    sf::FloatRect spriteRect = sprite.getGlobalBounds();
    text.setPosition(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f);
    
}
void LinkedButton::draw(sf::RenderWindow& window) {
    if (isHover) {
        sprite.setColor(sf::Color(240, 251, 255));
    }
    else if (isFinding) {
        sprite.setColor(sf::Color(174, 176, 227)); // Purple lean
    }
    else sprite.setColor(sf::Color(255, 255, 255));
    window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// InputWithHead
InputWithHead::InputWithHead(float x, float y, const std::string& imagePath, std::string sHeadname) : InputBox(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        // handle error
    }
    if (!texture.loadFromFile(imagePath)) {
        // handle error
    }
    float height = texture.getSize().y;
    texture.setSmooth(1);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(x + 10, y + 10);
    text.setFillColor(sf::Color::Black);

    tHeadname.setFont(font);
    tHeadname.setCharacterSize(15);
    tHeadname.setPosition(x, y - 20.0f);
    tHeadname.setFillColor(sf::Color::Black);
    tHeadname.setString(sHeadname);

    outline.setSize(sprite.getGlobalBounds().getSize());
    outline.setPosition(sprite.getPosition());
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2.0f);
    outline.setOutlineColor(sf::Color::Transparent);
}
void InputWithHead::draw(sf::RenderWindow& window) {
    if (isHover) {
		outline.setOutlineColor(sf::Color(58, 155, 220));
	}
    else {
		outline.setOutlineColor(sf::Color::Transparent);
	}
    
    window.draw(sprite);
    window.draw(tHeadname);
    window.draw(outline);
    if (active) {
        textDisplay.setString(text.getString() + "|");
    	window.draw(textDisplay);
    }
	else
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

//--------------------------------------------------------------
// GenderSelect
GenderSelect::GenderSelect(float x, float y, const std::string& imagePath1, const std::string& imagePath2, std::string sHead) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    if (!texture1.loadFromFile(imagePath1)) {
		cout << "Can't load image\n";
	}
    if (!texture2.loadFromFile(imagePath2)) {
        cout << "Can't load image\n";
    }
    texture1.setSmooth(1);
    sprite1.setTexture(texture1);
    sprite1.setPosition(x+1, y+20);

    texture2.setSmooth(1);
    sprite2.setTexture(texture2);
    sprite2.setPosition(x+1, y + 20);

    tHead.setFont(font);
    tHead.setCharacterSize(15);
    tHead.setFillColor(sf::Color::Black);
    tHead.setString(sHead);
    tHead.setPosition(x, y);

    outline.setSize(sprite1.getGlobalBounds().getSize());
    outline.setPosition(sprite1.getPosition());
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2.0f);
    outline.setOutlineColor(sf::Color::Transparent);
}
bool GenderSelect::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite1.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            if (female) female = false;
            else female = true;
            return true;
        }
    }
    return false;
}
bool GenderSelect::isHovering(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (sprite1.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
		isHover = true; 
	}
    else {
		isHover = false; 
	}
	return isHover;
}
void GenderSelect::draw(sf::RenderWindow& window) {
    if (isHover) {
        outline.setOutlineColor(sf::Color(58, 155, 220));
    }
    else {
        outline.setOutlineColor(sf::Color::Transparent);
    }
    if (female) window.draw(sprite1);
    else window.draw(sprite2);
    window.draw(outline);
    window.draw(tHead);
}


//--------------------------------------------------------------
// ChooseBoxWithHead
ChooseBoxWithHead::ChooseBoxWithHead(float x, float y, const std::string& imagePath, std::string sHead, std::string sText) : TextBox(x, y, imagePath, sText) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
		cout << "Can't load font\n";
	}
    if (!texture.loadFromFile(imagePath)) {
		cout << "Can't load image\n";
	}
	float height = texture.getSize().y;
	texture.setSmooth(1);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	text.setFont(font);
	text.setCharacterSize(18);
	text.setPosition(x + 10.0f, y + 13.0f);
	text.setFillColor(sf::Color::Black);
	text.setString(sText);

	tHead.setFont(font);
	tHead.setCharacterSize(15);
	tHead.setPosition(x, y - 20);
	tHead.setFillColor(sf::Color::Black);
	tHead.setString(sHead);
}
bool ChooseBoxWithHead::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            if (isSelect) isSelect = false;
			else isSelect = true;
            return true;
        }
    }
    return false;
}
void ChooseBoxWithHead::draw(sf::RenderWindow& window) {
    if (isSelect) {
        sprite.setColor(sf::Color(77, 113, 173)); // Medium dark blue
    }
    else if (isHover) {
    	sprite.setColor(sf::Color(173, 216, 230)); // Fade Blue
	}
	else {
		sprite.setColor(sf::Color::White);
    }
    window.draw(sprite);
    window.draw(tHead);
    window.draw(text);
}

//--------------------------------------------------------------
// CourseButton
CourseButton::CourseButton(float x, float y, const std::string& imagePath, std::string sText) : Button(x, y, imagePath) {
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
    text.setCharacterSize(20.0f);
    text.setPosition(x - sprite.getGlobalBounds().width / 2 + 5.0f, sprite.getPosition().y + 10.0f);
    text.setFillColor(sf::Color::White);
    text.setString(sText);

}
void CourseButton::draw(sf::RenderWindow& window) {
    if (isHover) {
		sprite.setColor(sf::Color(173, 216, 230));
	}
	else {
		sprite.setColor(sf::Color::White);
	}
	window.draw(sprite);
    window.draw(text);
}

//--------------------------------------------------------------
// ShowPasswordButton
ShowPasswordButton::ShowPasswordButton(float x, float y) {
	BigCircle.setRadius(15);
    BigCircle.setFillColor(sf::Color(240,240,240));
    BigCircle.setPosition(x, y);

    SmallCircle.setRadius(7.5f);
    SmallCircle.setFillColor(sf::Color(39,54,116));
    SmallCircle.setPosition(x + 7.5f, y + 7.5f);
}
ShowPasswordButton::ShowPasswordButton(float x, float y, std::string sText) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
        cout << "Can't load font\n";
    }
    BigCircle.setRadius(15);
    BigCircle.setFillColor(sf::Color(240, 240, 240));
    BigCircle.setPosition(x, y);

    SmallCircle.setRadius(7.5f);
    SmallCircle.setFillColor(sf::Color(39, 54, 116));
    SmallCircle.setPosition(x + 7.5f, y + 7.5f);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setString(sText);
    text.setPosition(x + 35, y + 5);
}
bool ShowPasswordButton::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (BigCircle.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
			if (active) active = false;
			else active = true;
			return true;
		}
	}
	return false;
}
void ShowPasswordButton::draw(sf::RenderWindow& window) {
    if (active) {
		SmallCircle.setFillColor(sf::Color(39,54,116));
	}
    else {
		SmallCircle.setFillColor(sf::Color(240,240,240));
	}
	window.draw(BigCircle);
	window.draw(SmallCircle);
    window.draw(text);
}

//--------------------------------------------------------------
// HrztBar
HrztBar::HrztBar(float x, float y, float width, float height) {
    bar.setSize(sf::Vector2f(width, height));
	bar.setFillColor(sf::Color::White);
	bar.setPosition(x, y);
}
void HrztBar::draw(sf::RenderWindow& window) {
    window.draw(bar);
}

//--------------------------------------------------------------
// Buttonv2
Buttonv2::Buttonv2(float x, float y, const std::string& imagePath) : Button(x, y, imagePath) {}
bool Buttonv2::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
			if (isSelect) isSelect = false;
            else isSelect = true;
            return true;
	}
    return false;
}

//--------------------------------------------------------------
// navigateButton
NavigateButton::NavigateButton(float x, float y, const std::string& imagePath) : Button (x,y,imagePath) {}
void NavigateButton::draw(sf::RenderWindow& window) {
    if (isHover) sprite.setColor(sf::Color(240, 240, 240));
	else sprite.setColor(sf::Color::White);
    window.draw(sprite);
}

//--------------------------------------------------------------
// ColorText
ColorText::ColorText(float x, float y, unsigned int size, std::string sText) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
		cout << "Can't load font\n";
	}
    text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(x, y);
	text.setFillColor(sf::Color::Black);
	text.setString(sText);
}
void ColorText::setColor(const sf::Color& color) {
    text.setFillColor(color);
}
void ColorText::draw(sf::RenderWindow& window) {
    window.draw(text);
}

//--------------------------------------------------------------
// Avatar Profile
AvatarProfile::AvatarProfile(float x, float y, const std::string& imagePath, std::string sText) : Button(x, y, imagePath) {
    if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
		cout << "Can't load font\n";
	}
    if (!texture.loadFromFile(imagePath)) {
		cout << "Can't load image\n";
	}
	texture.setSmooth(1);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	text.setFont(font);
	text.setCharacterSize(20);
	text.setPosition(x + 60, y + 15);
	text.setFillColor(sf::Color::Black);
	text.setString(sText);
}
void AvatarProfile::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(text);
}