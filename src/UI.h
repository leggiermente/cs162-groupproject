#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Struct.h"

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
struct InputScore : InputBox {
    InputScore(float x, float y, const std::string& imagePath);
    void draw(sf::RenderWindow& window);
};
struct ButtonSakura : Button {
	ButtonSakura(float x, float y, const std::string& imagePath);
	void draw(sf::RenderWindow& window);
};
struct ScoreRow {
    sf::Font font;
    sf::Text no;
    sf::Text id;
    sf::Text lastName;
    sf::Text firstName;
    InputScore totalS;
    InputScore finalS;
    InputScore midS;
    InputScore otherS;
    ButtonSakura deleteButton;
    ScoreRow(float x, float y, const std::string& imagePath);
    void isHovering(sf::RenderWindow& window);
    void loadIfm(string sNo, string sId, string sLName, string sFName, ScoreStu* sScoreStu);
    bool clickInput(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window);
};
struct ScoreRowInStu {
    sf::Font font;
    sf::Text year[4];
    sf::Text semester[4][4];
    sf::Text orGPA;
    ScoreRowInStu(float x, float y);
    void loadScore(GPA* gpaStu);
    void draw(sf::RenderWindow& window);
};
struct LinkedButton : Button {
    sf::Font font;
    sf::Text text;
    bool isFinding = false;
    LinkedButton(float x, float y, const std::string& imagePath, std::string sText);
    void setPositionForText();
    void draw(sf::RenderWindow& window);
};
struct Prompt {
    sf::Font* font;
    sf::Text text;
    sf::Texture* texture1;
    sf::Sprite sprite1;
    sf::Texture* texture2;
    sf::Sprite sprite2;
    bool loadImage(float x, float y, sf::Texture &inTexture1, sf::Texture& inTexture2) {
        texture1 = &inTexture1;
        sprite1.setTexture(*texture1);
        sprite1.setPosition(x, y);

        texture2 = &inTexture2;
        sprite2.setTexture(*texture2);
        sprite2.setPosition(x, y);
        return true;
    }

    bool loadFont(sf::Font &inFont) {
        font = &inFont;
        text.setFont(*font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(39,54,116));
        return true;
    }

    void setText(const std::string& str) {
        text.setString(str);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        sf::Vector2f spriteCenter = sprite1.getPosition() + sf::Vector2f(sprite1.getGlobalBounds().width / 2.0f, sprite1.getGlobalBounds().height / 2.0f);
        text.setPosition(spriteCenter);
    }

    void displayPrompt1(sf::RenderWindow& window, const std::string& sText) {
        text.setString(sText);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        sf::Vector2f spriteCenter = sprite1.getPosition() + sf::Vector2f(sprite1.getGlobalBounds().width / 2.0f, sprite1.getGlobalBounds().height / 2.0f);
        text.setPosition(spriteCenter);

        window.draw(text);
        sf::sleep(sf::seconds(2));
    }


};
struct CourseScore {
    sf::Text courseId;
    sf::Text year;
    sf::Text semester;
    sf::Text tTotal;
    sf::Text tFinal;
    sf::Text tMid;
    sf::Text tOther;
    bool active = false;
};
struct CourseBoard {
    sf::Font font;
	sf::Text text;
    sf::Texture texture;
    sf::Sprite sprite;
    CourseScore scoreRow[10];
	CourseBoard(float x, float y, const std::string& imagePath);
    void loadCourseScoreRow(ScoreStu* sScoreStu, int idx);
    void resetRow(int idx);
    void draw(sf::RenderWindow& window);
};