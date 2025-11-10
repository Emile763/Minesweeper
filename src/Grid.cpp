#include "Grid.h"



Grid::Grid(const sf::Vector2u& windSize)
{
	m_gridSize.x = int(windSize.x / m_size);
	m_gridSize.y = int(windSize.y / m_size);

	m_rectangle.setSize(sf::Vector2f(float(m_size - 1), float(m_size -1)));
	m_rectangle.setFillColor(sf::Color(100, 100, 100));

	
	if (!m_font.loadFromFile("arial.ttf"))
	{

	}
	m_nbr.setFont(m_font);
	m_nbr.setCharacterSize(m_size - 1);
	m_nbr.setFillColor(sf::Color::White);

	m_flag.setFillColor(sf::Color::Red);
	m_flag.setRadius(float(m_size/ 2 -1));

	Reset();

}


Grid::~Grid()
{
}


void Grid::Reset()
{
	m_grid.clear();
	for ( int y = 0; y < m_gridSize.y; y++)
	{
		m_grid.push_back(std::vector<square>());
		for ( int x = 0; x < m_gridSize.x; x++)
		{
			m_grid[y].push_back(square());
		}
	}
	srand((unsigned int)time(NULL));

	for (int i = 0; i < m_bombNbr; i++)
	{
		int x = rand() % m_gridSize.x;
		int y = rand() % m_gridSize.y;
		m_grid[y][x].type = 9;
	}
	int nbr = 0;
	for (int y = 0; y < m_gridSize.y; y++)
	{
		for (int x = 0; x < m_gridSize.x; x++)
		{
			nbr = 0;
			if (m_grid[y][x].type != 9)
			{
				if (x != 0)
				{
					if (m_grid[y][x - 1].type == 9)
						nbr++;

					if (y != 0)
					{
						if (m_grid[y - 1][x - 1].type == 9)
							nbr++;
					}
					if (y != m_gridSize.y - 1)
					{
						if (m_grid[y + 1][x - 1].type == 9)
							nbr++;
					}
				}

				if (x != m_gridSize.x - 1)
				{
					if (m_grid[y][x + 1].type == 9)
						nbr++;

					if (y != 0)
					{
						if (m_grid[y - 1][x + 1].type == 9)
							nbr++;
					}
					if (y != m_gridSize.y - 1)
					{
						if (m_grid[y + 1][x + 1].type == 9)
							nbr++;
					}
				}
				if (y != 0)
				{
					if (m_grid[y - 1][x].type == 9)
						nbr++;
				}
				if (y != m_gridSize.y - 1)
				{
					if (m_grid[y + 1][x].type == 9)
						nbr++;
				}
				
				m_grid[y][x].type = nbr;
				
			}
			
			
		}
	}

	m_Lose = false;

	
}


void Grid::Render(Window& window)
{
	for ( int y = 0; y < m_gridSize.y; y++)
	{
		for ( int x = 0; x < m_gridSize.x; x++)
		{
			if (m_grid[y][x].hide == true)
			{
				
				m_rectangle.setPosition({float(x * m_size) + 1, float(y * m_size) + 1});
				window.Draw(m_rectangle);
				if (m_grid[y][x].flag)
				{
					m_flag.setPosition({ float(x * m_size) + 1.5f, float(y * m_size) + 1.5f });
					window.Draw(m_flag);
				}
			}
			else if(m_grid[y][x].type != 0)
			{
				if (m_grid[y][x].type != 9)
				{
					m_nbr.setString(char(m_grid[y][x].type + 48));
					
					
				}
				else
				{
					m_nbr.setString("*");
					
				}
				m_nbr.setPosition({ float(x * m_size) + 1, float(y * m_size) + 1 });
				window.Draw(m_nbr);
			}
		
		}
	}
}


void Grid::Update(sf::Vector2i pos)
{
	
	
			if (pos.x > 0)
			{
				if (m_grid[pos.y][pos.x - 1].hide == true) 
				{
					m_grid[pos.y][pos.x - 1].hide = false;
					if (m_grid[pos.y][pos.x - 1].type == 0)
						Update(sf::Vector2i(pos.x - 1,pos.y));
				}
				

				if (pos.y > 0)
				{		
					if (m_grid[pos.y - 1][pos.x - 1].hide == true)
					{
						m_grid[pos.y - 1][pos.x - 1].hide = false;
						if (m_grid[pos.y - 1][pos.x - 1].type == 0)
							Update({ pos.x - 1,pos.y - 1 });
					}
				}
				if (pos.y < m_gridSize.y - 1)
				{
					if (m_grid[pos.y + 1][pos.x - 1].hide == true)
					{
						m_grid[pos.y + 1][pos.x - 1].hide = false;
						if (m_grid[pos.y + 1][pos.x - 1].type == 0)
							Update({ pos.x - 1, pos.y + 1 });
					}
				}
			}

			if (pos.x < m_gridSize.x - 1)
			{
				if (m_grid[pos.y][pos.x + 1].hide == true)
				{
					m_grid[pos.y][pos.x + 1].hide = false;
					if (m_grid[pos.y][pos.x + 1].type == 0)
						Update({ pos.x + 1,pos.y });
				}

				if (pos.y > 0)
				{
					if (m_grid[pos.y - 1][pos.x + 1].hide == true)
					{
						m_grid[pos.y - 1][pos.x + 1].hide = false;
						if (m_grid[pos.y - 1][pos.x + 1].type == 0)
							Update({ pos.x + 1,pos.y - 1 });
					}
				}
				if (pos.y < m_gridSize.y - 1)
				{
					if (m_grid[pos.y + 1][pos.x + 1].hide == true)
					{
						m_grid[pos.y + 1][pos.x + 1].hide = false;
						if (m_grid[pos.y + 1][pos.x + 1].type == 0)
							Update({ pos.x + 1,pos.y + 1 });
					}
				}
			}
			if (pos.y > 0)
			{
				if (m_grid[pos.y - 1][pos.x].hide == true)
				{
					m_grid[pos.y - 1][pos.x].hide = false;
					if (m_grid[pos.y - 1][pos.x].type == 0)
						Update({ pos.x, pos.y - 1 });
				}
			}
			if (pos.y < m_gridSize.y - 1)
			{
				if (m_grid[pos.y + 1][pos.x ].hide == true)
				{
					m_grid[pos.y + 1][pos.x].hide = false;
					if (m_grid[pos.y + 1][pos.x].type == 0)
						Update({ pos.x, pos.y + 1 });
				}
			}

				
	
	


}


void Grid::Discover(Window& window)
{
	
	m_mouseRPos = m_mouse.getPosition(*window.getWindow());
	m_mouseRPos.x /= m_size;
	m_mouseRPos.y /= m_size;
	
	if (m_mouse.isButtonPressed(sf::Mouse::Button::Left))
	{
		if (m_mouseRPos.x >= 0 && m_mouseRPos.x < m_gridSize.x && m_mouseRPos.y >= 0 && m_mouseRPos.y < m_gridSize.y && m_grid[m_mouseRPos.y][m_mouseRPos.x].hide && !m_grid[m_mouseRPos.y][m_mouseRPos.x].flag)
		{
			m_grid[m_mouseRPos.y][m_mouseRPos.x].hide = false;
			
			if (m_grid[m_mouseRPos.y][m_mouseRPos.x].type == 0)
			{
				
				Update(m_mouseRPos);
			}
			else if (m_grid[m_mouseRPos.y][m_mouseRPos.x].type == 9)
			{
				
				m_Lose = true;

			}
		}
	}
	
}

sf::Vector2i Grid::setFlag(Window& Flag, const sf::Vector2i& pos)
{
	if (m_mouse.isButtonPressed(sf::Mouse::Button::Right) && pos != m_mouseRPos)
	{
		m_grid[m_mouseRPos.y][m_mouseRPos.x].flag = !m_grid[m_mouseRPos.y][m_mouseRPos.x].flag;
		return m_mouseRPos;
	}
	else if (pos == m_mouseRPos)
	{
		return pos;
	}
	else
	{
		return {-1, -1};
	}
		
}

bool Grid::hasLost()
{
	return m_Lose;
}


void Grid::Reveal()
{
	for (int y = 0; y < m_gridSize.y; y++)
	{
		for (int x = 0; x < m_gridSize.x; x++)
		{
			m_grid[y][x].hide = false;
		}
	}
}
