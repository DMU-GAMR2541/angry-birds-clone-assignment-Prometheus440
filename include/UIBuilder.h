#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class UIBuilder
{
private:
    sf::Font* p_font = nullptr;
    std::string str_text = "";
    int i_charSize = 20;
    sf::Color col_fillColour = sf::Color::White;
    sf::Vector2f v2_position = { 0.0f, 0.0f };

public:
    UIBuilder& setFont(sf::Font& font)
    {
        p_font = &font;
        return *this;
    }

    UIBuilder& setText(std::string text)
    {
        str_text = text;
        return *this;
    }

    UIBuilder& setCharSize(int size)
    {
        i_charSize = size;
        return *this;
    }

    UIBuilder& setColour(sf::Color colour)
    {
        col_fillColour = colour;
        return *this;
    }

    UIBuilder& setPosition(float x, float y)
    {
        v2_position = {x, y};
        return *this;
    }

    sf::Text build()
    {
        std::cout << "=== Building UI ===" << std::endl;
        std::cout << "Font: " << p_font << std::endl;
        std::cout << "Position: (" << v2_position.x << ", " << v2_position.y << ")" << std::endl;
        std::cout << "Text: " << str_text << std::endl;
        std::cout << "Size: " << i_charSize << std::endl;
        std::cout << "====================" << std::endl;

        sf::Text text;
        text.setFont(*p_font);
        text.setString(str_text);
        text.setCharacterSize(i_charSize);
        text.setFillColor(col_fillColour);
        text.setPosition(v2_position);


        return text;
    }
};