#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Button {
    sf::Texture texture;
    sf::Sprite sprite;
    Button(float x, float y, const std::string& imagePath);
    bool isClicked(sf::RenderWindow& window);
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
struct CheckStaffButton {
    sf::Texture texture1;
    sf::Sprite sprite1;
    sf::Texture texture2;
    sf::Sprite sprite2;
    CheckStaffButton(float x, float y, const std::string& imagePath1, const std::string& imagePath2);
    void draw(sf::RenderWindow& window,bool& checked);
    bool isClick(sf::RenderWindow& window, bool& check);
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
struct LinkedButton {
    sf::Texture texture;
    LinkedButton** linkedButton = nullptr;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    LinkedButton(float x, float y, const std::string& imagePath, std::string sText);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};