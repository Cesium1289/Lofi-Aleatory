#ifndef GUI_SPRITEBUTTON_HPP
#define GUI_SPRITEBUTTON_HPP

#include "Widget.hpp"
#include <utility>
using namespace std;

namespace gui
{

/**
 * Push button linked to a sprite sheet
 */
class SpriteButton: public Widget
{
public:
    SpriteButton(const sf::Texture& defaultTexture, const sf::Texture& activeTexture, const sf::String& label = "");

    bool isActive() const;

    void setString(const sf::String& string);
    const sf::String& getString() const;

    void setFont(const sf::Font& font);
    const sf::Font& getFont() const;

    void setTextSize(size_t size);

    void setTexture(const sf::Texture& texture);

    void toggle();

    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onKeyReleased(const sf::Event::KeyEvent& key) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void press();
    void release();

    sf::Text m_text;
    sf::Sprite m_background;
    pair<sf::Texture, sf::Texture> textures;
    bool m_pressed;
    bool m_active;
};

}

#endif // GUI_SPRITEBUTTON_HPP
