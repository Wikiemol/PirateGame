#include "vec2.h"
#include <iostream>

Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vec2::operator=(const Vec2 &other)
{
    this->x = other.x;
    this->y = other.y;
}

