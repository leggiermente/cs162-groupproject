#pragma once
#include <SFML/Graphics.hpp>
#include <string>
struct LoginButton {
	sf::Texture texture;
	sf::Sprite sprite;

    LoginButton(float x, float y, const std::string& imagePath);

	void draw(sf::RenderWindow& window);

    void isClicked(sf::RenderWindow& window, sf::Text& username, sf::Text& password, std::string& user, std::string& pass, int& page);

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
    sf::Text label;
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
    sf::Text label;
    bool active = false;
    sf::Texture texture;
    sf::Sprite sprite;

    PasswordBox(float x, float y);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};