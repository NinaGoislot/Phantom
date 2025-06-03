#include "text.hpp"
#include <string>

//-----------------------------------------------------------------------------------------
//--------------------------------- VARIABLE GLOBAL ---------------------------------------
//-----------------------------------------------------------------------------------------

SimpleText &TextRenderer()
{
    static SimpleText textRenderer;
    return textRenderer;
}

//-----------------------------------------------------------------------------------------
//------------------------------------- INITIALIZE ----------------------------------------
//-----------------------------------------------------------------------------------------

void textInit()
{
    TextRenderer().ResetFont();
    TextRenderer().SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer().SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer().EnableBlending(true);
}

//-----------------------------------------------------------------------------------------
//------------------------------------ FUNCTIONS ------------------------------------------
//-----------------------------------------------------------------------------------------

// function to write the text

int i{0};

std::string textWritten(std::string const &text)
{
    if (i < text.length())
    {
        i++;
    }
    else
    {
        i = -1;
    }
    if (i == -1)
    {
        return text;
    }
    return text.substr(0, i);
}

// function to draw the text (we can change a lot of parameters here)
void textDraw(std::string const &text, float x, float y, SimpleText::Color color, SimpleText::Alignment alignment, SimpleText::FontSize size, bool isWriting)
{
    // we can change the color here
    TextRenderer().SetColor(SimpleText::TEXT_COLOR, color);
    
    TextRenderer().SetTextSize(size);
    x = x / 2;
    y = y / 2;
    if (isWriting)
    {
        // If isWriting is true, we will write the text letter by letter
        TextRenderer().Label(textWritten(text).c_str(), x, y, alignment);
    }
    else
    {
        TextRenderer().Label(text.c_str(), x, y, alignment);
    }
    TextRenderer().Render();
}