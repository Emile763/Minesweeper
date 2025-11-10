#include "Game.h"

Game::Game() : m_window({801, 593}, "Minesweeper"), m_grid({800, 600}), m_MPos(-1, -1), m_pressed(false)
{
}


Game::~Game()
{
}

void Game::HandleInput()
{
	if (!m_grid.hasLost())
	{
		m_grid.Discover(m_window);
		m_MPos = m_grid.setFlag(m_window, m_MPos);
	}
	
}

void Game::Render()
{
	m_window.BeginDraw(sf::Color::Black);

	m_grid.Render(m_window);
	m_window.EndDraw();
}

void Game::Update()
{
	if (m_grid.hasLost())
	{
		m_grid.Reveal();
		
		if (!m_mouse.isButtonPressed(sf::Mouse::Button::Left))
			m_pressed = false;

		if (m_mouse.isButtonPressed(sf::Mouse::Button::Left) && !m_pressed)
		{	
			
			m_grid.Reset();
			
		}
			
		if (m_mouse.isButtonPressed(sf::Mouse::Button::Left))
			m_pressed = true;

	}
	m_window.Update();
	
}

Window* Game::getWindow()
{
	return &m_window;
}