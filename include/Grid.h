#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

struct square
{
	square(const int& t = 0) : type(t){}

	
	int type;
	bool hide = true;
	bool flag = false;
};

using grid = std::vector<std::vector<square>>;

class Grid
{
public:
	Grid(const sf::Vector2u& windSize);
	
	~Grid();
	void Reset();
	void Render(Window& window);
	void Update(sf::Vector2i pos);
	void Discover(Window& window);
	sf::Vector2i setFlag(Window& window, const sf::Vector2i& pos);
	bool hasLost();
	void Reveal();

private:
	grid m_grid;
	int m_size = 16;
	sf::Vector2i m_gridSize;
	int m_bombNbr = 300;
	sf::RectangleShape m_rectangle;
	sf::Text m_nbr;
	sf::Font m_font;
	sf::CircleShape m_flag;

	sf::Vector2i m_mouseRPos;

	bool m_Lose;

	bool m_removeF;
};

