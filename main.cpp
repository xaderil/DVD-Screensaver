#define resolutionWidth 1280
#define resolutionHeight 720
#define framerateLimit 150

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class DVD {

public:
    sf::Sprite sprite;

    DVD(sf::Vector2f startPosition = {100.f,100.f},
        sf::Vector2f startDirectionOfMoving = {0.5, 0.5},
        float iconSizeX = 240,
        float iconSizeY = 260,
        float moveSpeed = 5 ) {

            if(!texture.loadFromFile("src/dvd.png")) {
                std::cout << "Could not load DVD picture" << std::endl;
            }
            directionOfMoving = startDirectionOfMoving;
            size = {iconSizeX, iconSizeY};
            speed = moveSpeed;
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sprite.scale(iconSizeX/spriteSize().x, iconSizeY/spriteSize().y);
            sprite.setPosition(startPosition);
            resetColor();
    }

    sf::Vector2f spriteSize() {
        return {static_cast<float>(sprite.getTexture()->getSize().x * sprite.getScale().x),
                static_cast<float>(sprite.getTexture()->getSize().x * sprite.getScale().x)};
    }
    void resetColor() {
        color = Colors[0 + rand() % 14];
        sprite.setColor(color);
    }
    void moveDVD() {
        sprite.move(speed*directionOfMoving.x, speed*directionOfMoving.y);
    }

    void checkPosition() {
        position = sprite.getPosition();
        if (resolutionWidth - position.x - size.x <= 0 || resolutionWidth - position.x >= resolutionWidth) {
            directionOfMoving.x = -directionOfMoving.x;
            resetColor();
        } else if (resolutionHeight - position.y - size.y + 0.5*size.y <= 0 || resolutionHeight - position.y >= resolutionHeight) {
            directionOfMoving.y = -directionOfMoving.y;
            resetColor();
        }
    }

private:
    float speed;
    sf::Color color;
    sf::Texture texture;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f directionOfMoving;
    std::vector<sf::Color> Colors = {sf::Color(255,255,255), sf::Color(255,0,0), sf::Color(0,255,0),
                                     sf::Color(0,0,255), sf::Color(255,255,0), sf::Color(0,255,255),
                                     sf::Color(255,0,255), sf::Color(191,191,191), sf::Color(128,128,128),
                                     sf::Color(128,0,0), sf::Color(128,128,0), sf::Color(0,128,0),
                                     sf::Color(0,0,128), sf::Color(0,128,128), sf::Color(128,0,128)};

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(resolutionWidth, resolutionHeight), "My window");
    window.setFramerateLimit(framerateLimit);
    DVD dvd;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        dvd.checkPosition();
        dvd.moveDVD();
        window.draw(dvd.sprite);
        window.display();
    }

    return 0;
}
