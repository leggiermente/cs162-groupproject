#include <iostream>

#include "display.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;

const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;
int page = 0;

UsernameBox inputUserBox(xMid, yMid - 200.0f);
PasswordBox inputPassBox(xMid, yMid - 100.0f);
LoginButton loginButton(xMid, yMid - 20.0f, "image/button.png");
DeleteButton deleteButton(xMid, yMid, "image/delete.png");

std::string user;
std::string pass;

void RunApp() 
{
    while (window.isOpen()) 
    {
        switch (page)
        {
        case 0: // Login Page
        {
            // Read input from mouse and keyboard
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                inputUserBox.handleEvent(event, window);
                inputPassBox.handleEvent(event, window);
                deleteButton.isClicked(window, inputUserBox.text, inputPassBox.text, inputPassBox.star);
                loginButton.isClicked(window, inputUserBox.text, inputPassBox.text, user, pass, page);

                // Draw Element 
                window.clear(sf::Color::White);
                loginButton.draw(window);
                inputUserBox.draw(window);
                inputPassBox.draw(window);                  
                deleteButton.draw(window);                   
                window.display();
            }
            
            break;
        }
        case 1: // Account menu page
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            sf::Text notice;
            sf::Font font;
            if (!font.loadFromFile("font/Roboto-Regular.ttf")) {
                // handle error
            }
            notice.setString("Login Successfully!!!");
            notice.setFont(font);
            notice.setCharacterSize(70.0f);
            notice.setPosition(xMid - 200, yMid);
            notice.setFillColor(sf::Color::Green);
            notice.setString("Login Successfully!!!");
            window.draw(notice);
            window.display();
            break;
        }
        default:
            break;
        }
    }
    std::cout << "Username: " << user << std::endl;
    std::cout << "Password: " << pass << std::endl;
    return;
}