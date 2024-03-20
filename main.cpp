#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void draw_shooter(sf::RenderWindow& window, float pos){
    float radius = 20.0;
    sf::CircleShape shape(radius);
    shape.setPosition(pos - radius, 600.f - radius*2);
    window.draw(shape);
}

// void draw_bullet(sf::RenderWindow& window, float x, float y){
//     float radius = 10.0;
//     sf::CircleShape shape(radius);
//     shape.setPosition(x - radius, y);
//     shape.setFillColor(sf::Color(100, 250, 50));
//     window.draw(shape);
// }

class Bullets{
    std::vector<float> x;
    std::vector<float> y;
    int n;
    float radius = 10;
    float speedPerFrame = 10;

    void initBullet(int i, float x0, float y0) {
        x[i] = x0;
        y[i] = y0;
    }

    bool bulletIn(int i) {
        return (x[i] > -radius) && (x[i] < 800 + radius) && 
            (y[i] > -radius) && (y[i] < 600 + radius);
    }

    void moveBullet(int i) {
        y[i] -= speedPerFrame;
    }

public:
    
    Bullets() : x{100, 0.0}, y {100, 0.0}, n{100} {}

    Bullets(float x0, float y0)  {
        n = 100;
        for (int i = 0; i < n; ++i) {
            x.push_back(x0);
            y.push_back(y0);
        }
    }

    void update() {
        for (int i = 0; i < n; ++i) {
            if (bulletIn(i)) moveBullet(i);
        }
    }

    void addBullet(float x0, float y0) {
        for (int i = 0; i < n; ++i) {
            if (!bulletIn(i)) {
                initBullet(i, x0, y0);
                break;
            }
        }
    }

    void draw(sf::RenderWindow& window){
        for (int i = 0; i < n; ++i){
            if (bulletIn(i)){
                // std::cout << "drawing " << i << x[i] << y[i] << std::endl;
                sf::CircleShape shape(radius);
                shape.setPosition(x[i] - radius, y[i] - radius);
                shape.setFillColor(sf::Color(100, 250, 50));
                window.draw(shape);
            } 
        }
    }

};

int main(void){

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    
    sf::Clock clock;
    
    // run the program as long as the window is open
    float ShooterPosition = 400.0;
    float ShooterStepX = 5.0;
    // float BulletX = 0.0;
    // float BulletY = 0.0;
    // bool MovingRight = false;
    // bool MovingLeft = false;
    window.setFramerateLimit(50);

    Bullets bullets(-100.0, -100.0);
    bool shootKeyHeld = false;

    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        
        while (window.pollEvent(event)){
            // "close requested" event: we close the window

            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.scancode){
                        case sf::Keyboard::Scan::Space:
                            shootKeyHeld = true;
                            break;
                        default:
                            break;
                    }
                    break;
                
                case sf::Event::KeyReleased:
                    switch (event.key.scancode){
                        case sf::Keyboard::Scan::Space:
                            shootKeyHeld = false;
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (ShooterPosition < 800.0 - 20.0) ShooterPosition += ShooterStepX;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (ShooterPosition > 20) ShooterPosition -= ShooterStepX;
        }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) bullets.addBullet(ShooterPosition, 600.0 - 50.0);
        draw_shooter(window, ShooterPosition);

        if (shootKeyHeld && clock.getElapsedTime().asSeconds() >= 0.2){
            clock.restart();
            bullets.addBullet(ShooterPosition, 600.0 - 50.0);
        }

        bullets.draw(window);
        bullets.update();
        

        window.display();
    }
    
    return 0;
}