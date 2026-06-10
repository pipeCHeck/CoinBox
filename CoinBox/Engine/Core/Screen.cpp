#include "Screen.h"

float Screen::m_width = 1.0f;
float Screen::m_height = 1.0f;

void Screen::SetSize(unsigned int width, unsigned int height)
{
    m_width = width > 0 ? static_cast<float>(width) : 1.0f;
    m_height = height > 0 ? static_cast<float>(height) : 1.0f;
}
