#include "text.hpp"
#include <string>

SimpleText &TextRenderer()
{
    static SimpleText textRenderer;
    return textRenderer;
}

void textInit()
{
    TextRenderer().ResetFont();
    TextRenderer().SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer().SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer().EnableBlending(true);
}

int i {0};

std::string textWritten(std::string const& text) {
    if (i < text.length()) {
        i++;
    } else {
        i = -1;
    }
    if (i == -1) {
        return text;
    }
    return text.substr(0, i);
}

void textDraw(std::string const& text, float x, float y, SimpleText::Alignment alignment, SimpleText::FontSize size)
{
    TextRenderer().SetTextSize(size);
    TextRenderer().Label(textWritten(text).c_str(), x, y, alignment);
    TextRenderer().Render();
}