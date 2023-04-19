#include "CenteredText.h"

using namespace sf;

CenteredText::CenteredText(const sf::Font &font, const sf::String &string, sf::Vector2f position, bool centeredVertical)
{
    centerVertical = centeredVertical;
    setFont(font);
    setString(string);
    setPosition(position);
}

CenteredText::CenteredText(const String &string, const Font &font)
{
    setFont(font);
    setString(string);
}

void CenteredText::setString(const String &string)
{
    Text::setString(string);
    // center the text
    auto bounds = getLocalBounds();
    auto middle = Vector2f(bounds.width, bounds.height) / 2.f;
    setOrigin(centerVertical ? middle : Vector2f(middle.x, 0));
}
