//
// Created by david on 10/2/21.
//

#include "gui/button.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Button::Button(const Vector2f& loc, const Color& background, const Color& foreground)
: defaultBackground(background), mousePressedColor(180,180,180),
mouseHoverColor(220, 220, 220) {
    setButtonState(DEFAULT);
    setAction([](){}); // Default action does nothing

    shape.setPosition(loc);
    shape.setFillColor(defaultBackground);
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(1.0f);

    text.setPosition(loc);
    text.setFillColor(foreground);
    text.setCharacterSize(22);
}

//Button::Button() : Button({}, {}, {}) {} // Calls other constructor

void Button::draw(RenderTarget &target, RenderStates states) const {
    target.draw(shape, states);
    target.draw(text, states);

}

void Button::setFont(const sf::Font &font) {
    text.setFont(font);
}

void Button::setText(const string& t) {
    text.setString(t);
    shape.setSize({
        (float)t.length() * text.getCharacterSize() * 0.8f,
        text.getCharacterSize() * 1.5f});
    float avgCharWidth = 12;
    text.setPosition(
            shape.getPosition().x +
            (shape.getSize().x - avgCharWidth * text.getString().getSize()) / 2.0f,
            shape.getPosition().y + shape.getSize().y / 10);
}

void Button::setPosition(const sf::Vector2f &pos) {
    shape.setPosition(pos);
    float avgCharWidth = 12;
    text.setPosition(
            shape.getPosition().x +
                        (shape.getSize().x - avgCharWidth * text.getString().getSize()) / 2.0f,
            shape.getPosition().y + shape.getSize().y / 10);
}

Vector2f Button::getPosition() const {
    return shape.getPosition();
}

bool Button::containsPoint(const sf::Vector2f &point) const {
    return
       point.x >= shape.getPosition().x && point.x < shape.getPosition().x + shape.getSize().x
    && point.y >= shape.getPosition().y && point.y < shape.getPosition().y + shape.getSize().y;
}

void Button::setButtonState(int state) {
    switch (state) {
        case PRESSED: shape.setFillColor(mousePressedColor); break;
        case HOVERED: shape.setFillColor(mouseHoverColor); break;
        default: shape.setFillColor(defaultBackground);
    }
}

void Button::setAction(const std::function<void()> &act) {
    action = act;
}

std::function<void()> Button::getAction() const {
    return action;
}

sf::Vector2f Button::getSize() const {
    return shape.getSize();
}

void Button::setSize(const Vector2f& size) {
    shape.setSize(size);
}

void Button::setTextPosition(const sf::Vector2f &size) {
    text.setPosition(size);
}