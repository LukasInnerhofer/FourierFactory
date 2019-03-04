#include "main.h"

#define ANGULAR_FREQUENCY	1
#define FPS_GOAL			60

/// <ui>
#define TOOLBAR_HEIGHT		40

inline sf::Vector2f vectorDiagramOrigin(const sf::Vector2u &windowSize) { return { windowSize.x / 4.0f, (windowSize.y - 40) / 2.0f + 40 }; }
inline sf::Vector2f vectorDiagramSize(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f - 20, windowSize.y - 60.0f }; }
inline sf::Vector2f lineDiagramOrigin(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f + 20, (windowSize.y - 40) / 2.0f + 40 }; }
inline sf::Vector2f lineDiagramSize(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f - 20, windowSize.y - 60.0f }; }
/// </ui>

void handleEvents(sf::Window &window, std::vector<sf::Vector2f> &vectors, std::vector<sf::Vector2f> &lineDiagramPoints, const std::map<std::string, sf::Button *> &buttons, bool &running, std::chrono::steady_clock::time_point &startTime);
std::map<std::string, sf::Button *> initButtons();
void drawBackground(sf::RenderWindow &window);
float stof_ext(const std::string &str);

int main()
{
	float fps = 1;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 900), "Fourier Factory");

	const std::map<std::string, sf::Button *> buttons = initButtons();
	bool running = false;
	std::vector<sf::Vector2f> vectors;
	std::vector<sf::Vector2f> lineDiagramPoints;
	float lineDiagramScale = 1;

	std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
	std::thread timerThread;

	sf::RectangleShape pixel = sf::RectangleShape({ 1, 1 });
	pixel.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		timerThread = std::thread([] { std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS_GOAL)); });
		const std::chrono::time_point<std::chrono::steady_clock> loopStartTime = std::chrono::steady_clock::now();

		handleEvents(window, vectors, lineDiagramPoints, buttons, running, startTime);

		window.clear();
		drawBackground(window);

		for (std::pair<std::string, sf::Button *> button : buttons)
		{
			button.second->update(window);
			window.draw(*button.second);
		}

		{
			sf::Vector2f vectorOrigin = vectorDiagramOrigin(window.getSize());
			for (const sf::Vector2f &vector : vectors)
			{
				window.draw(sf::LineShape(vectorOrigin, vectorOrigin + vector));
				vectorOrigin.x += vector.x;
				vectorOrigin.y -= vector.y;
			}
		}

		if (running)
		{
			for (unsigned int itVectors = 0; itVectors < vectors.size(); ++itVectors)
			{
				sf::Transform transform;
				vectors[itVectors] = transform.rotate(180 * (itVectors + 1) * ANGULAR_FREQUENCY / (PI * fps)).transformPoint(vectors[itVectors]);
			}

			float ySum = 0;
			for (const sf::Vector2f &vector : vectors) { ySum += vector.y; }

			lineDiagramPoints.push_back(
				lineDiagramOrigin(window.getSize()) + 
				sf::Vector2f(
					(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime).count() / 1000000.0) * 
					window.getSize().x * ANGULAR_FREQUENCY / (8 * PI), 
					-ySum * lineDiagramScale));
			
			if (lineDiagramPoints[lineDiagramPoints.size() - 1].x > lineDiagramOrigin(window.getSize()).x + lineDiagramSize(window.getSize()).x - 10)
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

void handleEvents(sf::Window &window, std::vector<sf::Vector2f> &vectors, std::vector<sf::Vector2f> &lineDiagramPoints, const std::map<std::string, sf::Button *> &buttons, bool &running, std::chrono::steady_clock::time_point &startTime)
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
			if (sf::Mouse::getPosition(window).x < window.getSize().x / 2 && sf::Mouse::getPosition(window).y > TOOLBAR_HEIGHT)
			{
				sf::Vector2f vectorOrigin = vectorDiagramOrigin(window.getSize());
				for (const sf::Vector2f vector : vectors)
				{
					vectorOrigin.x += vector.x;
					vectorOrigin.y -= vector.y;
				}
				const int diffX = sf::Mouse::getPosition(window).x - vectorOrigin.x;
				const int diffY = vectorOrigin.y - sf::Mouse::getPosition(window).y;
				vectors.push_back({ static_cast<float>(diffX == 0 ? 1 : diffX), static_cast<float>(diffY == 0 ? 1 : diffY) });
			}
			else
			{
				for (const std::pair<std::string, sf::Button *> &button : buttons)
				{
					if (button.second->getMouseOver())
					{
						if (button.first == "start")
						{
							startTime = std::chrono::steady_clock::now();
							running = true;
						}
						else if (button.first == "stop")
						{
							running = false;
							lineDiagramPoints.clear();
						}
						else if (button.first == "openFile")
						{
							running = false;
							std::string path = "";
#ifdef _WIN32
							std::array<char, 1024> fileName;
							OPENFILENAME ofn = {};
							ofn.lStructSize = sizeof(ofn);
							ofn.hwndOwner = NULL;
							ofn.lpstrFile = fileName.data();
							ofn.lpstrFile[0] = '\0';
							ofn.nMaxFile = fileName.size();
							ofn.lpstrFilter = NULL;

							try
							{
								if (!GetOpenFileName(&ofn))
								{
									const DWORD errcode = CommDlgExtendedError();
									if (errcode) throw std::system_error(std::error_code(errcode, std::system_category()), "GetOpenFileName resulted in an error.");
									else return;
								}
								path = std::string(fileName.data());
							}
							catch (const std::system_error &exception)
							{
								std::cout << "System error occured during file dialog. " << exception.what() << " Code: " << exception.code() << std::endl;
								return;
							}
							catch (const std::length_error &exception)
							{
								std::cout << "The supplied pathname was too long. " << exception.what() << std::endl;
								return;
							}
							catch (const std::bad_alloc &exception)
							{
								std::cout << "Failed to allocate memory during file dialog. " << exception.what() << std::endl;
								return;
							}
							catch (const std::exception &exception)
							{
								std::cout << "Unknown exception occured during file handling. " << exception.what() << std::endl;
								return;
							}
#endif // _WIN32
							lineDiagramPoints.clear();
							vectors.clear();
							
							auto fstream = std::ifstream(path);
							std::string line;
							try
							{
								while (std::getline(fstream, line))
								{
									const unsigned int index = line.find(',');
									if (index != std::string::npos)
									{
										vectors.push_back({ stof_ext(line.substr(index + 1)), stof_ext(line.substr(0, index)) });
									}
									else
									{
										throw InvalidFormat("Fourier files must follow this format: \ncoeffA1,coeffB1\ncoeffA2,coeffB2\n...");
									}
								}
							}
							catch (const std::invalid_argument &exception)
							{
								std::cout << "Invalid argument exception occured during file read. " << exception.what() << std::endl;
								std::cout << "Hint: fourier files must follow this format: \ncoeffA1,coeffB1\ncoeffA2,coeffB2\n...\n";
								return;
							}
							catch (const std::out_of_range &exception)
							{
								std::cout << "Out of range exception occured during file read. " << exception.what() << std::endl;
								return;  
							}
							catch (const std::logic_error &exception)
							{
								std::cout << "Logic error occured during file read. " << exception.what() << std::endl;
								return;
							}
							catch (const InvalidFormat &exception)
							{
								std::cout << "Invalid format exception occured during file read. " << exception.what() << std::endl;
								return;
							}
							catch (const std::exception &exception)
							{
								std::cout << "Unknown exception occured during file read. " << exception.what() << std::endl;
								return;
							}
							
							float totalMag = 0;
							for (const sf::Vector2f &vector : vectors) { totalMag += vectorMath::magnitude(vector); }
							const sf::Vector2f diagramSize = vectorDiagramSize(window.getSize());
							const float scale = (((diagramSize.x > diagramSize.y) ? diagramSize.y : diagramSize.x) / 2 - 10) / totalMag;
							for (unsigned int itVectors = 0; itVectors < vectors.size(); ++itVectors)
							{
								vectors[itVectors].x *= scale;
								vectors[itVectors].y *= scale;
							}
						}
						else if (button.first == "clear")
						{
							running = false;
							vectors.clear();
							lineDiagramPoints.clear();
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
		},
		{
			"clear", new sf::Button({ 224, 10 }, { 50, 20 }, "Clear", 15, { 8, 0 })
		}
	};
}

void drawBackground(sf::RenderWindow &window)
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color(200, 200, 200, 255));

	// Toolbar
	line.setSize({ static_cast<float>(window.getSize().x), 1.0f });
	line.setPosition({ 0, TOOLBAR_HEIGHT });
	window.draw(line);

	// Seperator
	line.setSize({ 1.0f, static_cast<float>(window.getSize().y - TOOLBAR_HEIGHT) });
	line.setPosition({ window.getSize().x / 2.0f, static_cast<float>(TOOLBAR_HEIGHT) });
	window.draw(line);

	// Coordinate Systems
	line.setFillColor(sf::Color::White);

	// Vector diagram
	// x
	line.setSize({ vectorDiagramSize(window.getSize()).x, 1.0f });
	line.setPosition({ 10.0f, vectorDiagramOrigin(window.getSize()).y});
	window.draw(line);

	// y
	line.setSize({ 1.0f, vectorDiagramSize(window.getSize()).y });
	line.setPosition({ vectorDiagramOrigin(window.getSize()).x, TOOLBAR_HEIGHT + 10.0f });
	window.draw(line);

	// Line diagram
	// x
	line.setSize({ lineDiagramSize(window.getSize()).x, 1.0f });
	line.setPosition({ lineDiagramOrigin(window.getSize()).x - 10, lineDiagramOrigin(window.getSize()).y });
	window.draw(line);

	// y
	line.setSize({ 1, lineDiagramSize(window.getSize()).y });
	line.setPosition({ (window.getSize().x / 2.0f) + 20, TOOLBAR_HEIGHT + 10.0f });
	window.draw(line);
}

float stof_ext(const std::string &str)
{
	float ret = 0;

	try
	{
		ret = std::stof(str); // throws invalid_argument and out_of_range
	}
	catch (const std::logic_error &exception)
	{
		const unsigned int index = str.find('e');
		if (index != std::string::npos)
		{
			ret = std::stof(str.substr(0, index)) * std::pow(10, std::stof(str.substr(index + 1)));
		}
		else throw exception;
	}

	return ret;
}