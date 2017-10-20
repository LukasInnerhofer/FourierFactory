#include "main.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 900), "Fourier Factory [BETA]");

	const std::map<std::string, Button *> buttons = initButtons();
	bool running = false;
	std::vector<sf::Vector2i> vectors;

	while (window.isOpen())
	{
		sf::Event e;
		if (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseLeft:
				if (sf::Mouse::getPosition(window).x < window.getSize().x / 2 && sf::Mouse::getPosition(window).y > 40)
				{
					sf::Vector2i vectorOrigin = { static_cast<int>(window.getSize().x / 4), static_cast<int>((window.getSize().y - 60) / 2) };
					for (sf::Vector2i vector : vectors)
					{
						vectorOrigin += vector;
					}
					vectors.push_back({sf::Mouse::getPosition(window).x - vectorOrigin.x, vectorOrigin.y - sf::Mouse::getPosition(window).y});
				}
				else
				{
					for (std::pair<std::string, Button *> button : buttons)
					{
						if (button.second->getMouseOver())
						{
							if (button.first == "start")
							{
								running = true;
							}
							else if(button.first == "stop")
							{
								running = false;
							}
							else if (button.first == "openFile")
							{
								running = false;
							}
						}
					}
				}

				break;

			default:
				break;
			}
		}

		window.clear();

		drawBackground(window);

		for (std::pair<std::string, Button *> button : buttons)
		{
			button.second->update(window);
			button.second->draw(window);
		}

		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	return 0;
}

std::map<std::string, Button *> initButtons()
{
	return 
	{
		{
			"start", new Button({ 10, 10 }, { 50, 20 }, "Start", 15, { 8, 0 })
		},
		{
			"stop", new Button({ 70, 10 }, { 50, 20 }, "Stop", 15, { 8, 0 })
		},
		{
			"openFile", new Button({ 130, 10 }, { 84, 20 }, "Open File", 15, { 8, 0 })
		}
	};
}

void drawBackground(sf::RenderWindow &window)
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color(200, 200, 200, 255));

	line.setSize({ static_cast<float>(window.getSize().x), 1.0f });
	line.setPosition({ 0, 40 });
	window.draw(line);

	line.setSize({ 1.0f, window.getSize().y - 40.0f });
	line.setPosition({ window.getSize().x / 2.0f, 40.0f });
	window.draw(line);

	// Coordinate Systems
	line.setFillColor(sf::Color::White);

	// Vector diagram
	line.setSize({ (window.getSize().x / 2.0f) - 20, 1.0f });
	line.setPosition({ 10.0f, (window.getSize().y - 50) / 2.0f});
	window.draw(line);

	line.setSize({ 1.0f, window.getSize().y - 60.0f });
	line.setPosition({ window.getSize().x / 4.0f, 50.0f });
	window.draw(line);

	//Line diagram
	line.setSize({ (window.getSize().x / 2.0f) - 20, 1 });
	line.setPosition({ (window.getSize().x / 2.0f) + 10, (window.getSize().y - 50) / 2.0f });
	window.draw(line);

	line.setSize({ 1, window.getSize().y - 60.0f });
	line.setPosition({ (window.getSize().x / 2.0f) + 20, 50.0f });
	window.draw(line);
}