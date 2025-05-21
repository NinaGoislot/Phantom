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

void textDraw(std::string text, float x, float y, SimpleText::Alignment alignment, SimpleText::FontSize size)
{
    TextRenderer().SetTextSize(size);
    TextRenderer().Label(text.c_str(), x, y, alignment);
    TextRenderer().Render();
}