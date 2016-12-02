#include "canvas.h"

void Canvas::OnInit()
{
    // Load the image
    myImage.loadFromFile("/home/justin/Documents/CS3505/Sprites/SFMLSprite/icon.png");
    myImage.setSmooth(true);

    // Setup the sprite
    mySprite.setTexture(myImage);
    mySprite.setOrigin(10, 10);
    mySprite.setPosition(20, 20);
}

void Canvas::OnUpdate()
{
    // Clear screen
    this->clear(sf::Color(100, 0, 0));

    // Rotate the sprite
    mySprite.rotate(1.0f);

    // Draw it
    //sf::RenderWindow::draw(mySprite);
    draw(mySprite);
}
