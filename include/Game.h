#pragma once
#include "Window.h"
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Render();
	void Update();

	Window* getWindow();

private:
	Window m_window;
	Grid m_grid;

	sf::Vector2i m_MPos;
	bool m_pressed;

	sf::Font m_font;
};

