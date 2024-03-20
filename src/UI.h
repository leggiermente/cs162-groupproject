#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct LoginBox {
    sf::Texture texture;
    sf::Sprite sprite;
    LoginBox(float x, float y, const std::string& imagePath);
    void draw(sf::RenderWindow& window);
};
struct LoginButton {
	sf::Texture texture;
	sf::Sprite sprite;
    LoginButton(float x, float y, const std::string& imagePath);
	void draw(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, std::string& user, std::string& pass);
};
struct UsernameBox {
    sf::Text text;
    sf::Font font;
    bool active = false;
    sf::Texture texture;
    sf::Sprite sprite;
    UsernameBox(float x, float y);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct PasswordBox {
    sf::Text text;
    sf::Text star;
    sf::Font font;
    bool active = false;
    sf::Texture texture;
    sf::Sprite sprite;
    PasswordBox(float x, float y);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct HomePage {
    sf::Texture texture1,texture2;
    sf::Sprite sprite1,sprite2;
    HomePage(float x, float y, const std::string& imagePath1, const std::string& imagePath2);
    void draw(sf::RenderWindow& window, bool isStaff);
};
struct CheckStaffButton {
    sf::Texture texture1;
    sf::Sprite sprite1;
    sf::Texture texture2;
    sf::Sprite sprite2;
    CheckStaffButton(float x, float y, const std::string& imagePath1, const std::string& imagePath2);
    void draw(sf::RenderWindow& window,bool& checked);
    bool isClick(sf::RenderWindow& window, bool& check);
};
struct Background {
    sf::Texture texture;
    sf::Sprite sprite;
    Background(float x, float y, const std::string& imagePath);
    void draw(sf::RenderWindow& window);
};

// Staff Menu
struct ClassesButton {
    sf::Texture texture;
    sf::Sprite sprite;
    ClassesButton(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct SchoolyearsButton {
    sf::Texture texture;
    sf::Sprite sprite;
    SchoolyearsButton(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct ViewingPage {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    ViewingPage(float x, float y, const std::string& imagePath, std::string sText);
    void draw(sf::RenderWindow& window);
};
struct Button400x45 {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    Button400x45(float x, float y, const std::string& imagePath, std::string sText);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct Button200x45 {
    Button400x45** semesterButtons = nullptr;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    Button200x45(float x, float y, const std::string& imagePath, std::string sText);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
struct LogOutButton {
    sf::Texture texture;
    sf::Sprite sprite;
    LogOutButton(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};