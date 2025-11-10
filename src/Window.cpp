#include "Window.h"



Window::Window(const sf::Vector2u& size, const std::string title)
{
	Setup(size, title);
}


Window::~Window()
{
	Destroy();
}


void Window::Setup(const sf::Vector2u& size, const std::string title)
{
	m_size = size;
	m_title = title;
	m_isDone = false;
	m_fullscreen = false;
	Create();
}

void Window::Create()
{


	auto style = m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create(sf::VideoMode(m_size.x, m_size.y, 32), m_title, style);

}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_isDone = true;
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
			ToggleFullscreen();
	}
}

void Window::ToggleFullscreen()
{
	m_fullscreen = !m_fullscreen;
	Destroy();
	Create();
}

bool Window::isDone()
{
	return m_isDone;
}

void Window::BeginDraw(const sf::Color& color)
{
	m_window.clear(color);
}

void Window::Draw(const sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::EndDraw()
{
	m_window.display();
}




void Window::Destroy()
{
	
	m_window.close();
}

sf::RenderWindow* Window::getWindow()
{
	return &m_window;
}