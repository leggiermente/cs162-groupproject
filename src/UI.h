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

// Staff Menu
struct TextBox : Button {
    sf::Text text;
    sf::Font font;
    TextBox(float x, float y, const std::string& imagePath, std::string sText);
    TextBox(float x, float y, const std::string& imagePath, std::string sText, std::string sColor);
    virtual void draw(sf::RenderWindow& window);
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
struct GenderSelect  {
    sf::Font font;
    sf::Text tHead;
    sf::Texture texture1;
    sf::Sprite sprite1;
    sf::Texture texture2;
    sf::Sprite sprite2;
    sf::RectangleShape outline;
    bool female = false;
    bool isHover = false;
    GenderSelect(float x, float y, const std::string& imagePath1, const std::string& imagePath2, std::string sHead);
    bool isClicked(sf::RenderWindow& window, sf::Event event);
    bool isHovering(sf::RenderWindow& window);
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
    sf::Text text;
    sf::Font font;
    bool active = false;
    ShowPasswordButton(float x, float y);
    ShowPasswordButton(float x, float y, std::string sText);
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
struct ColorText {
	sf::Text text;
	sf::Font font;
    bool trigger = false;
	ColorText(float x, float y, unsigned int size, std::string sText);
    void setColor(const sf::Color& color);
    void draw(sf::RenderWindow& window);
};
struct AvatarProfile : Button {
    sf::Text text;
	sf::Font font;
	AvatarProfile(float x, float y, const std::string& imagePath, std::string sText);
	void draw(sf::RenderWindow& window);
};
struct ScoreRow {
    sf::Font font;
    sf::Text no;
    sf::Text id;
    sf::Text lastName;
    sf::Text firstName;
    InputWithHead total;
    InputWithHead final;
    InputWithHead mid;
    InputWithHead other;
    sf::Sprite deleteSprite;
    sf::Texture deleteTexture;
    ScoreRow(float x, float y, const std::string& imagePath, std::string sNo, std::string sId, std::string sLastName, std::string sFirstName,
        std::string stotal, std::string sFinal, std::string sMid, std::string sOther);
    bool clickDelete(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window);
};
struct LinkedButton : Button {
    LinkedButton** linkedButton = nullptr;
    ScoreRow** scoreList = nullptr;
    sf::Font font;
    sf::Text text;
    bool isFinding = false;
    LinkedButton(float x, float y, const std::string& imagePath, std::string sText);
    void draw(sf::RenderWindow& window);
};