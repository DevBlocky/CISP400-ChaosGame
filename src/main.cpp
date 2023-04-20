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
    srand(time(nullptr));

    // create the window for the game
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game", Style::Default);

    // used for measuring deltaTime and fps
    Clock dtClock;
    int totalFrames = 0;
    double totalTime = 0;

    // load the font used for all text
    Font fontLato;
    fontLato.loadFromFile("fonts/Lato-Regular.ttf");

    // create the fps text
    Text textInfo;
    textInfo.setFont(fontLato);
    textInfo.setCharacterSize(12);

    // create the insturctions text
    constexpr const char *INSTRUCTIONS = "Welcome to Chaos Game!\nClick anywhere three times to define the triangle\nThen click one more to start!";
    CenteredText textInstruct(fontLato, INSTRUCTIONS, {window.getView().getCenter().x, 50.f}, false);

    // vectors for points displayed on screen
    std::vector<Vector2f> inputPoints;
    std::vector<Vector2f> generated;
    Vector2f lastGenerated;

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
                inputPoints.push_back({static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y)});
            }
        }

        // found the avg fps and frame times for the last 100ms
        Time dt = dtClock.restart();
        totalTime += static_cast<double>(dt.asMicroseconds()) / 1000;
        totalFrames++;
        if (totalTime > 100.f) // update every 100ms
        {
            double tMs = totalTime / totalFrames; // avg frame time
            totalTime = 0;                        // reset counters
            totalFrames = 0;
            double fps = 1000 / tMs; // overall fps

            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << fps << "fps " << tMs << "ms" << std::endl;
            oss << generated.size() << " points";
            textInfo.setString(oss.str());
        }

        // BEGIN DRAW
        window.clear();
        window.draw(textInfo);

        // point.size() < 4 when awaiting user input
        if (inputPoints.size() < 4)
        {
            window.draw(textInstruct);

            // draw a small rect for each vert provided
            RectangleShape shape{{5, 5}};
            for (auto const &vertex : inputPoints)
            {
                shape.setPosition(vertex);
                window.draw(shape);
            }
        }
        // we're no longer awaiting user input, generate points and dispaly!
        else
        {
            constexpr int TARGET_PPS = 1000; // points per second
            // calculate number of points to create to meet TARGET_PPS
            int nPoints = TARGET_PPS * static_cast<double>(dt.asMicroseconds()) / 1000000;
            if (generated.size() + nPoints >= 30000)
                nPoints = 30000 - generated.size(); // cap at 30k generated points

            for (int n = 0; n < nPoints; n++)
            {
                // set lastGenerated to the initial point if we don't have any points yet
                if (generated.size() == 0)
                    lastGenerated = inputPoints[inputPoints.size() - 1];

                // randomly select the next point from the input points
                Vector2f selectedPoint = inputPoints[rand() % (inputPoints.size() - 1)];
                // create the new lastGenerated point
                lastGenerated = (lastGenerated + selectedPoint) / 2.f;
                generated.push_back(lastGenerated);
            }

            // draw all points
            RectangleShape shape({1, 1});
            for (size_t i = 0; i < generated.size(); i++)
            {
                shape.setPosition(generated[i]);
                window.draw(shape);
            }
        }

        // END DRAW
        window.display();
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
