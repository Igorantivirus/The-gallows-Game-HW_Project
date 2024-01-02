#pragma once

#include<iostream>
#include<random>
#include<time.h>

#include<SFML\Graphics.hpp>

template<typename type>
std::ostream& operator<<(std::ostream& out, const sf::Vector2<type>& pos)
{
	out << "x = " << pos.x << " y = " << pos.y;
	return out;
}
template<typename type>
std::ostream& operator<<(std::ostream& out, const sf::Rect<type>& pos)
{
	out << "left = " << pos.left << " top = " << pos.top << " width = " << pos.width << " height = " << pos.height;
	return out;
}

int randomVal(int begin, int end)
{
	return rand() % (end + begin + 1) - begin;
}