#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Button {
    sf::Texture texture;
    sf::Sprite sprite;
    Button(float x, float y, const std::string& imagePath);
    virtual bool isClicked(sf::RenderWindow& window, sf::Event event);
    virtual void draw(sf::RenderWindow& window);
};
struct LoginButton : Button {
    LoginButton(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window, sf::Event event, sf::Text& username, sf::Text& password, std::string& user, std::string& pass);
};
struct InputBox : Button {
    sf::Text text;
    sf::Font font;
    bool active = false;
    InputBox(float x, float y, const std::string& imagePath);
    virtual void isClicked(const sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};
struct PasswordBox : InputBox {
    sf::Text star;
    PasswordBox(float x, float y, const std::string& imagePath);
    void isClicked(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct CheckStaffButton {
    sf::Texture texture1;
    sf::Sprite sprite1;
    sf::Texture texture2;
    sf::Sprite sprite2;
    CheckStaffButton(float x, float y, const std::string& imagePath1, const std::string& imagePath2);
    void draw(sf::RenderWindow& window,bool& checked);
    bool isClick(sf::RenderWindow& window,sf::Event event, bool& check);
};
struct ProfileText {
    sf::Text firstName,
        lastName,
        ID,
        DD_MM_YY,
        socialID,
        gender;
    sf::Font font;
    ProfileText(std::string sFirstName, std::string sLastName, std::string sID);
    ProfileText(std::string firstName, std::string lastName,
    std::string ID, std::string DD_MM_YY, std::string socialID,
    std::string gender);
    void drawStu(sf::RenderWindow& window);
    void drawStaff(sf::RenderWindow& window);
};

// Staff Menu
struct ViewingPage {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    ViewingPage(float x, float y, const std::string& imagePath, std::string sText);
    void draw(sf::RenderWindow& window);
};
struct TextBox : Button {
    sf::Text text;
    sf::Font font;
    TextBox(float x, float y, const std::string& imagePath, std::string sText);
    TextBox(float x, float y, const std::string& imagePath, std::string sText, std::string sColor);
    virtual void draw(sf::RenderWindow& window);
};
struct LinkedButton {
    sf::Texture texture;
    LinkedButton** linkedButton = nullptr;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    LinkedButton(float x, float y, const std::string& imagePath, std::string sText);
    bool isClicked(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window);
};
struct InputWithHead : InputBox {
    sf::Text tHeadname;
    InputWithHead(float x, float y, const std::string& imagePath, std::string sHeadname);
    void draw(sf::RenderWindow& window);
};
struct Line {
    sf::RectangleShape stick;
    Line(float x, float y, float width, float height);
    void draw(sf::RenderWindow& window);
};
struct TextChangeBox : TextBox {
    sf::Text textChange;
    sf::Text tHead;
    bool active = false;
    TextChangeBox(float x, float y, const std::string& imagePath, std::string sHead, std::string sText, std::string sTextChange);
	bool isClicked(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window);
};
class BareboneText
{
public:
    int xCordinate, yCordinate;
    std::string textContent;
    sf::Font scoreboardFont;
    BareboneText() : xCordinate(0), yCordinate(0), textContent("") {
            // You may choose to load a default font here or leave it empty
            // and load the font later when needed
        }
    BareboneText(int x, int y, std::string text): xCordinate(x), yCordinate(y), textContent(text)
    {
        if (!scoreboardFont.loadFromFile("font/Roboto_Mono/RobotoMono-VariableFont_wght.ttf")) {
            std::cout << "Cannot load font!" << std::endl;
        }
        sf::Text myText;
        myText.setFont(scoreboardFont);
        myText.setPosition(xCordinate, yCordinate);
        myText.setString(textContent);
    }
    void draw(sf::RenderWindow& window);
};
