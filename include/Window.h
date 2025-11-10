#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Window
{
public:
	Window(const sf::Vector2u& size = {500, 500}, std::string title = "Default title");
	~Window();

	
	void BeginDraw(const sf::Color& color);
	void Draw(const sf::Drawable& drawable);
	void EndDraw();
	
	void Update();
	void ToggleFullscreen();
	bool isDone();
	
	sf::RenderWindow* getWindow();

private:
	void Setup(const sf::Vector2u& size, std::string title);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_size;
	std::string m_title;
	bool m_isDone;
	bool m_fullscreen;
	
};

