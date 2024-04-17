#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Button {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape outline;
    bool isHover = false;
    Button(float x, float y, const std::string& imagePath);
    virtual bool isClicked(sf::RenderWindow& window, sf::Event event);
    virtual void draw(sf::RenderWindow& window);
    virtual void isHovering(sf::RenderWindow& window);
};
struct LoginButton : Button {
    LoginButton(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window, sf::Event event, sf::Text& username, sf::Text& password, std::string& user, std::string& pass);
};
struct InputBox : Button {
    sf::Text text;
    sf::Font font;
    sf::Text textDisplay;
    sf::RectangleShape outline;
    bool active = false;
    InputBox(float x, float y, const std::string& imagePath);
    virtual void isClicked(const sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};
struct PasswordBox : InputBox {
    sf::Text star;
    sf::Text tHeadname;
    PasswordBox(float x, float y, const std::string& imagePath, const std::string& sHeadname);
    void isClicked(const sf::Event& event, sf::RenderWindow& window);
    void isHovering(sf::RenderWindow& window);
    void drawStar(sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window);
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
struct TextBox : Button {
    sf::Text text;
    sf::Font font;
    TextBox(float x, float y, const std::string& imagePath, std::string sText);
    TextBox(float x, float y, const std::string& imagePath, std::string sText, std::string sColor);
    virtual void draw(sf::RenderWindow& window);
};
struct LinkedButton : Button{
    LinkedButton** linkedButton = nullptr;
    sf::Font font;
    sf::Text text;
    LinkedButton(float x, float y, const std::string& imagePath, std::string sText);
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
struct ChooseBoxWithHead : TextBox {
	sf::Text tHead;
	bool isSelect = false;
    ChooseBoxWithHead(float x, float y, const std::string& imagePath, std::string sHead, std::string sText);
	bool isClicked(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);
};
struct CourseButton : Button {
	sf::Text text;
	sf::Font font;
	CourseButton(float x, float y, const std::string& imagePath, std::string sText);
	void draw(sf::RenderWindow& window);
};
struct ShowPasswordButton {
    sf::CircleShape BigCircle;
    sf::CircleShape SmallCircle;
    bool active = false;
    ShowPasswordButton(float x, float y);
    bool isClicked(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window);
};
struct HrztBar{
    sf::RectangleShape bar;
	HrztBar(float x, float y, float width, float height);
	void draw(sf::RenderWindow& window);
};
struct Buttonv2 : Button {
    bool isSelect = false;
	Buttonv2(float x, float y, const std::string& imagePath);
	bool isClicked(sf::RenderWindow& window, sf::Event event);
};
struct NavigateButton : Button {
    NavigateButton(float x, float y, const std::string& imagePath);
    void draw(sf::RenderWindow& window);
};
