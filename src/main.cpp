// CHAOS GAME PROJECT
// Made by: Jacob Parker
// Partner: None

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "CenteredText.h"

using namespace sf;

int main()
{
    // create the window for the game
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game", Style::Default);

    Clock dtClock;
    int nFrames = 0;
    double totalTime = 0;

    // load the font used for all text
    Font fontLato;
    fontLato.loadFromFile("fonts/Lato-Regular.ttf");

    // create the fps text
    Text textFps;
    textFps.setFont(fontLato);
    textFps.setCharacterSize(12);

    constexpr const char *INSTRUCTIONS = "Welcome to Chaos Game!\nClick anywhere three times to define the triangle\nThen click one more to start!";
    CenteredText textInstruct(fontLato, INSTRUCTIONS, {window.getView().getCenter().x, 50.f}, false);

    std::vector<Vector2f> points;

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
                points.push_back({static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y)});
            }
        }

        // found the avg fps and frame times for the last 100 frames
        Time dt = dtClock.restart();
        totalTime += static_cast<double>(dt.asMicroseconds()) / 1000;
        if (++nFrames % 200 == 0)
        {
            double tMs = totalTime / 200; // avg frame time
            totalTime = 0;                // reset the total time counter
            double fps = 1000 / tMs;      // overall fps

            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << fps << "fps " << tMs << "ms";
            textFps.setString(oss.str());
        }

        // BEGIN DRAW
        window.clear();
        window.draw(textFps);

        // point.size() < 4 when awaiting user input
        if (points.size() < 4) {
            window.draw(textInstruct);

            // draw a small rect for each vert provided
            RectangleShape shape{{5, 5}};
            for (auto const &vertex : points)
            {
                shape.setPosition(vertex);
                window.draw(shape);
            }
        }

        // END DRAW
        window.display();
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
