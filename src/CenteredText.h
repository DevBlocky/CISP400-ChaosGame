#include <SFML/Graphics.hpp>

class CenteredText : public sf::Text
{
    using Text::Text;

public:
    CenteredText(const sf::Font &font, const sf::String &string, sf::Vector2f position = {0, 0}, bool centeredVertical = true);
    CenteredText(const sf::String &string, const sf::Font &font); // override for the Text constructor
    void setString(const sf::String &string);

private:
    bool centerVertical = true;
};
