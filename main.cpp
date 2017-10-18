#include "main.h"

int main()
{
	Button button({ 100, 100 }, { 100, 100 }, "test");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 900), "Fourier Factory [BETA]");

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
			default:
				break;
			}
		}

		button.update(window);
		button.draw(window);

		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	return 0;
}