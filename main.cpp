#define resolutionWidth 1280
#define resolutionHeight 720
#define framerateLimit 150
#define numberOfIcons 10

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class DVD {

public:
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
        position = startPosition;
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

    sf::Sprite sprite;
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
    sf::RenderWindow window(sf::VideoMode(resolutionWidth, resolutionHeight), "DVD Screensaver");
    window.setFramerateLimit(framerateLimit);

//    sf::Texture texture;
//    if(!texture.loadFromFile("src/dvd.png")) {
//        std::cout << "Could not load DVD picture" << std::endl;
//    }
//    texture.setSmooth(true);

    std::vector<DVD> Icons(numberOfIcons);
    float xDirection = 0.5, yDirection = 0.5;
    for (int i = 0; i < numberOfIcons; i++) {
        if(i % 2 != 0) {
            xDirection = -xDirection;
        } else if (i + 1 % 2 != 0) {
            yDirection = -yDirection;
        }
        float x = static_cast<float>(10 + rand() % (resolutionWidth - 300));
        float y = static_cast<float>(10 + rand() % (resolutionHeight - 300));
        Icons[i] = DVD({x, y}, {xDirection, yDirection});
    }
    DVD dvd({200, 200}, {-0.5, 0.5});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < numberOfIcons; i++) {
            Icons[i].checkPosition();
            Icons[i].moveDVD();
            window.draw(Icons[i].sprite);
        }
        dvd.checkPosition();
        dvd.moveDVD();
        window.draw(dvd.sprite);
        window.display();
    }

    return 0;
}
