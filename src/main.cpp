#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // create the window for the game
    VideoMode vm(1280, 720);
    RenderWindow window(vm, "Chaos Game", Style::Default);

    Clock dtClock;
    int nFrames = 0;
    double totalTime = 0;

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    Text text(String(std::string("chaos game")), font);
    
    // center the text
    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(Vector2f(bounds.width, bounds.height) / 2.f);
    text.setPosition({1280 / 2, 100});

    std::vector<Vector2f> vertices;

    // MAIN GAME LOOP
    while (window.isOpen())
    {
        // poll input events
        Event ev;
        while (window.pollEvent(ev))
        {
            // if ESC or the close window btn is pressed, close the window
            if ((ev.type == Event::KeyPressed && ev.key.code == Keyboard::Key::Escape) || ev.type == Event::Closed)
                window.close();

            // check for left mouse pressed
            if (ev.type == Event::MouseButtonPressed && ev.mouseButton.button == Mouse::Left)
            {
                vertices.push_back(Vector2f(ev.mouseButton.x, ev.mouseButton.y));
            }
        }

        // found the avg fps and frame times for the last 100 frames
        Time dt = dtClock.restart();
        totalTime += static_cast<double>(dt.asMicroseconds()) / 1000;
        if (++nFrames % 100 == 0)
        {
            double tMs = totalTime / 100; // avg frame time
            totalTime = 0;                // reset the total time counter
            std::cout << tMs << "ms" << std::endl;
            std::cout << 1000 / tMs << "fps" << std::endl;
        }

        // BEGIN DRAW
        window.clear();

        window.draw(text);
        // draw a small rect for each vert provided
        RectangleShape shape{{5, 5}};
        for (auto const &v : vertices)
        {
            shape.setPosition(v);
            window.draw(shape);
        }

        // END DRAW
        window.display();
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
