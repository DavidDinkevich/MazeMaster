//
// Created by david on 10/2/21.
//

#ifndef MAZEMASTER_BUTTON_HPP
#define MAZEMASTER_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Drawable {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color defaultBackground;
    sf::Color mousePressedColor;
    sf::Color mouseHoverColor;
    std::function<void()> action;
public:
    Button(const sf::Vector2f& loc, const sf::Color& background, const sf::Color& foreground);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setFont(const sf::Font& font);
    void setText(const std::string& t);
    bool containsPoint(const sf::Vector2f& point) const;
    void setButtonState(int state);
    void setAction(const std::function<void()>& action);
    std::function<void()> getAction() const;
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f& size);
    void setTextPosition(const sf::Vector2f& size);

    enum {
        DEFAULT = 0b001,
        HOVERED = 0b010,
        PRESSED = 0b100
    };

};

#endif //MAZEMASTER_BUTTON_HPP
