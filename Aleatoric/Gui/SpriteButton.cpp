#include "SpriteButton.hpp"
#include "Theme.hpp"

namespace gui
{

SpriteButton::SpriteButton(const sf::Texture& defaultTexture, const sf::Texture& activeTexture, const sf::String& string):
    Widget(),
    m_pressed(false)
{
    size_t width = defaultTexture.getSize().x;
    size_t height = defaultTexture.getSize().y / 3; // default, hover, focus

    m_background.setTexture(defaultTexture);
    m_background.setTextureRect(sf::IntRect(0, 0, width, height));

    setSize(width, height);

    m_text.setFont(Theme::getFont());
    m_text.setCharacterSize(Theme::textSize);

    textures.first = defaultTexture;
    textures.second = activeTexture;

    setString(string);
}

bool SpriteButton::isActive() const
{
    return m_active;
}


void SpriteButton::setString(const sf::String& string)
{
    m_text.setString(string);
    centerText(m_text);
}


const sf::String& SpriteButton::getString() const
{
    return m_text.getString();
}


void SpriteButton::setFont(const sf::Font& font)
{
    m_text.setFont(font);
    centerText(m_text);
}


const sf::Font& SpriteButton::getFont() const
{
    return *m_text.getFont();
}


void SpriteButton::setTextSize(size_t size)
{
    m_text.setCharacterSize(size);
    centerText(m_text);
}

void SpriteButton::setTexture(const sf::Texture& texture)
{
    size_t width = texture.getSize().x;
    size_t height = texture.getSize().y / 3; // default, hover, focus

    m_background.setTexture(texture);
    m_background.setTextureRect(sf::IntRect(0, 0, width, height));
}

void SpriteButton::toggle() {
    sf::Vector2f size = getSize();
    static bool enabled = false;
    if (m_active)
        m_background.setTexture(textures.first);
    else
        m_background.setTexture(textures.second);
    m_active = !m_active;
}

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_background, states);
    target.draw(m_text, states);
}


// Callbacks -------------------------------------------------------------------

void SpriteButton::onStateChanged(State state)
{
    sf::Vector2f size = getSize();
    switch (state)
    {
    case StateDefault:
        m_background.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
        break;
    case StateHovered:
        m_background.setTextureRect(sf::IntRect(0, size.y, size.x, size.y));
        break;
    case StatePressed:
        m_background.setTextureRect(sf::IntRect(0, size.y, size.x, size.y));
    case StateFocused:
        m_background.setTextureRect(sf::IntRect(0, size.y * 2, size.x, size.y));
        break;
    }
}


void SpriteButton::onMouseMoved(float x, float y)
{
    if (isFocused())
    {
        if (containsPoint({x, y}) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            press();
        else
            release();
    }
}


void SpriteButton::onMousePressed(float, float)
{
    press();
}


void SpriteButton::onMouseReleased(float x, float y)
{

    release();
    if (containsPoint({x, y}))
    {
        triggerCallback();
    }
}


void SpriteButton::onKeyPressed(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Return)
    {
        triggerCallback();
        press();
    }
}


void SpriteButton::onKeyReleased(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Return)
        release();
}


void SpriteButton::press()
{
    if (!m_pressed)
    {
        m_pressed = true;
        m_text.move(0, 1);
    }
}


void SpriteButton::release()
{
    if (m_pressed)
    {
        m_pressed = false;
        m_text.move(0, -1);
    }
}

}
