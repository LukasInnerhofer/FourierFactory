#include "main.h"

void handleEvents(sf::Window &window, List<sf::Vector2f> &vectors, const std::map<std::string, sf::Button *> &buttons, bool &running);

int main()
{
	float fps = 1;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 900), "Fourier Factory [BETA]");

	const std::map<std::string, sf::Button *> buttons = initButtons();
	bool running = false;
	List<sf::Vector2f> vectors;
	List<sf::Vector2f> lineDiagramPoints;
	float lineDiagramScale = 1;

	const std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
	std::thread timerThread;

	sf::RectangleShape pixel = sf::RectangleShape({ 1, 1 });
	pixel.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		timerThread = std::thread([] { std::this_thread::sleep_for(std::chrono::milliseconds(16)); });
		const std::chrono::time_point<std::chrono::steady_clock> loopStartTime = std::chrono::steady_clock::now();

		handleEvents(window, vectors, buttons, running);

		window.clear();
		drawBackground(window);

		for (std::pair<std::string, sf::Button *> button : buttons)
		{
			button.second->update(window);
			window.draw(*button.second);
		}

		{
			sf::Vector2f vectorOrigin = vectorDiagramOrigin(window.getSize());
			for (unsigned int itVectors = 0; itVectors < vectors.size(); ++itVectors)
			{
				window.draw(sf::LineShape(vectorOrigin, vectorOrigin + sf::Vector2f(vectors[itVectors].x, vectors[itVectors].y)));
				vectorOrigin.x += vectors[itVectors].x;
				vectorOrigin.y -= vectors[itVectors].y;
			}
		}

		if (running)
		{
			for (unsigned int itVectors = 0; itVectors < vectors.size(); ++itVectors)
			{
				vectors[itVectors] = vectorMath::rotate(vectors[itVectors], (itVectors + 1) * ANGULAR_FREQUENCY / fps);
			}

			float ySum = 0;
			for (const sf::Vector2f &vector : vectors) { ySum += vector.y; }

			lineDiagramPoints.push_back(
				lineDiagramOrigin(window.getSize()) + 
				sf::Vector2f(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime).count() * window.getSize().x * ANGULAR_FREQUENCY / (8000000 * PI), 
					ySum * lineDiagramScale));
			
			if (lineDiagramPoints[lineDiagramPoints.size() - 1].x > lineDiagramOrigin(window.getSize()).x + (window.getSize().x / 2.0f) - 20)
			{
				auto oldPoints = lineDiagramPoints;
				for (unsigned int itPoints = 1; itPoints < lineDiagramPoints.size(); ++itPoints)
				{
					lineDiagramPoints[itPoints].x = oldPoints[itPoints - 1].x;
				}
				lineDiagramPoints.erase(lineDiagramPoints.begin());
			}

			for (unsigned int itValues = 0; itValues < lineDiagramPoints.size(); ++itValues)
			{
				pixel.setPosition(lineDiagramPoints[itValues].x, lineDiagramPoints[itValues].y);
				window.draw(pixel);
			}
		}

		window.display();
		timerThread.join();
		fps = 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - loopStartTime).count();
	}

	return 0;
}

void handleEvents(sf::Window &window, List<sf::Vector2f> &vectors, const std::map<std::string, sf::Button *> &buttons, bool &running)
{
	sf::Event e;
	if (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::getPosition(window).x < window.getSize().x / 2 && sf::Mouse::getPosition(window).y > 40)
			{
				sf::Vector2f vectorOrigin = vectorDiagramOrigin(window.getSize());
				for (const sf::Vector2f vector : vectors)
				{
					vectorOrigin.x += vector.x;
					vectorOrigin.y -= vector.y;
				}
				vectors.push_back({ sf::Mouse::getPosition(window).x - vectorOrigin.x, vectorOrigin.y - sf::Mouse::getPosition(window).y });
			}
			else
			{
				for (const std::pair<std::string, sf::Button *> &button : buttons)
				{
					if (button.second->getMouseOver())
					{
						if (button.first == "start")
						{
							running = true;
						}
						else if (button.first == "stop")
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
}

std::map<std::string, sf::Button *> initButtons()
{
	return 
	{
		{
			"start", new sf::Button({ 10, 10 }, { 50, 20 }, "Start", 15, { 8, 0 })
		},
		{
			"stop", new sf::Button({ 70, 10 }, { 50, 20 }, "Stop", 15, { 8, 0 })
		},
		{
			"openFile", new sf::Button({ 130, 10 }, { 84, 20 }, "Open File", 15, { 8, 0 })
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
	line.setPosition({ 10.0f, vectorDiagramOrigin(window.getSize()).y});
	window.draw(line);

	line.setSize({ 1.0f, window.getSize().y - 60.0f });
	line.setPosition({ vectorDiagramOrigin(window.getSize()).x, 50.0f });
	window.draw(line);

	//Line diagram
	line.setSize({ (window.getSize().x / 2.0f) - 20, 1 });
	line.setPosition({ (window.getSize().x / 2.0f) + 10, (window.getSize().y - 50) / 2.0f });
	window.draw(line);

	line.setSize({ 1, window.getSize().y - 60.0f });
	line.setPosition({ (window.getSize().x / 2.0f) + 20, 50.0f });
	window.draw(line);
}