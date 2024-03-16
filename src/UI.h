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
struct DeleteButton {
    sf::Texture texture;
    sf::Sprite sprite;
    DeleteButton(float x, float y, const std::string& imagePath);
    void draw(sf::RenderWindow& window);
    void isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, sf::Text& star);
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
struct LeftHome {
    sf::Texture texture;
    sf::Sprite sprite;
    LeftHome(float x, float y, const std::string& imagePath);
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