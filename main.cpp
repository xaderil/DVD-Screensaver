#define resolutionWidth 1280
#define resolutionHeight 720
#define framerateLimit 90
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(resolutionWidth, resolutionHeight), "My window");
    window.setFramerateLimit(framerateLimit);

    sf::Texture textureDvd;
    if(!textureDvd.loadFromFile("src/dvd.png")) {
        std::cout << "Could not load DVD picture" << std::endl;
    }
    sf::Sprite dvdPict;
    dvdPict.setTexture(textureDvd);
    dvdPict.scale(0.17, 0.17);
    dvdPict.setPosition(100, 100);
    dvdPict.setColor(sf::Color::Yellow);

    int32_t moveX = 10;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Blue);

        sf::Vector2f shapePosition = dvdPict.getPosition();
        std::cout << shapePosition.x << " " << shapePosition.y << std::endl;
        std::cout << resolutionWidth - shapePosition.x << " " << resolutionWidth - shapePosition.x + 270.5 << std::endl << std::endl;
        if (resolutionWidth - shapePosition.x - 270.2 <= 0 || resolutionWidth - shapePosition.x >= resolutionWidth) {
            moveX = -moveX;
        }
        dvdPict.move(moveX, 0);
        window.draw(dvdPict);
        window.display();
    }

    return 0;
}
