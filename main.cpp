#define resolutionWidth 1280
#define resolutionHeight 720
#define framerateLimit 90

#include <SFML/Graphics.hpp>
#include <iostream>

class DVD {

public:
    sf::Sprite sprite;

    DVD(sf::Vector2f startPosition = {100.f,100.f},
        sf::Vector2f startDirectionOfMoving = {0.5, 0.5},
        float iconSizeX = 240,
        float iconSizeY = 260,
        float moveSpeed = 10 ) {

            if(!texture.loadFromFile("src/dvd.png")) {
                std::cout << "Could not load DVD picture" << std::endl;
            }
            directionOfMoving = startDirectionOfMoving;
            size = {iconSizeX, iconSizeY};
            speed = moveSpeed;
            sprite.setTexture(texture);
            sprite.scale(iconSizeX/spriteSize().x, iconSizeY/spriteSize().y);
            sprite.setPosition(startPosition);
            sprite.setColor(sf::Color::Blue);

    }

    sf::Vector2f spriteSize() {
        return {static_cast<float>(sprite.getTexture()->getSize().x * sprite.getScale().x),
                static_cast<float>(sprite.getTexture()->getSize().x * sprite.getScale().x)};
    }

    void moveDVD() {
        sprite.move(speed*directionOfMoving.x, speed*directionOfMoving.y);
    }

    void checkPosition() {
        position = sprite.getPosition();
        if (resolutionWidth - position.x - size.x <= 0 || resolutionWidth - position.x >= resolutionWidth) {
            directionOfMoving.x = -directionOfMoving.x;
        } else if (resolutionHeight - position.y - size.y + 0.5*size.y <= 0 || resolutionHeight - position.y >= resolutionHeight) {
            directionOfMoving.y = -directionOfMoving.y;
        }
    }

private:
    sf::Texture texture;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f directionOfMoving;
    float speed;
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(resolutionWidth, resolutionHeight), "My window");
    window.setFramerateLimit(framerateLimit);
    DVD dvd;

    float moveX = 10;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        dvd.checkPosition();
        dvd.moveDVD();
        window.draw(dvd.sprite);
        window.display();
    }

    return 0;
}
