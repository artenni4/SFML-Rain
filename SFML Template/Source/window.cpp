#include "window.h"
#include "drop.h"

#include <iostream>
#include <random>
#include <Windows.h>


Window::Window()
{
}

void Window::ChooseDropColor()
{
	setlocale(LC_ALL, "rus");

	window.create(sf::VideoMode(800, 650), "Choose color");

	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/Verdana.ttf"))
	{
		system("pause");
		exit(-1);
	}

	

	sf::Text chooseColor;
	chooseColor.setFont(font);
	chooseColor.setString(L"Выберите цвет");
	chooseColor.setFillColor(sf::Color::White);
	chooseColor.setCharacterSize(24);
	chooseColor.setPosition(sf::Vector2f(300, 10));

	std::vector<sf::RectangleShape> rectColors(8);

	for (unsigned int i = 0; i < rectColors.size(); i++)
	{
		rectColors[i].setSize(sf::Vector2f(800, 75));
		rectColors[i].setPosition(sf::Vector2f(0, (i * 75) + 50));
	}


	rectColors[0].setFillColor(sf::Color::Black);
	rectColors[1].setFillColor(sf::Color::White);
	rectColors[2].setFillColor(sf::Color::Blue);
	rectColors[3].setFillColor(sf::Color::Yellow);
	rectColors[4].setFillColor(sf::Color::Red);
	rectColors[5].setFillColor(sf::Color::Green);
	rectColors[6].setFillColor(sf::Color::Cyan);
	rectColors[7].setFillColor(sf::Color::Magenta);

	while (window.isOpen())
	{
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Event.type == sf::Event::MouseButtonReleased)
			{
				for (unsigned int i = 0; i < rectColors.size(); i++)
				{
					std::cout << sf::Mouse::getPosition().y << std::endl;
					if (sf::Mouse::getPosition(window).y >= i * 75 + 50 && sf::Mouse::getPosition(window).y < (i + 1)* 75 + 50)
					{
						switch (i)
						{
						case 0:
						{
							color = sf::Color::Black;
							break;
						}
						case 1:
						{
							color = sf::Color::White;
							break;
						}
						case 2:
						{
							color = sf::Color::Blue;
							break;
						}
						case 3:
						{
							color = sf::Color::Yellow;
							break;
						}
						case 4:
						{
							color = sf::Color::Red;
							break;
						}
						case 5:
						{
							color = sf::Color::Green;
							break;
						}
						case 6:
						{
							color = sf::Color::Cyan;
							break;
						}
						case 7:
						{
							color = sf::Color::Magenta;
							break;
						}
						default:
							break;
						}

						window.close();
					}
				}
			}
		}

		window.clear(sf::Color(70, 70, 70, 255));

		window.draw(chooseColor);
		for (unsigned int i = 0; i < rectColors.size(); i++)
		{
			window.draw(rectColors[i]);
		}

		window.display();
	}

	window.close();
}

void Window::Init()
{
	std::vector<Drop> Drops(300);
	window.create(sf::VideoMode::getDesktopMode(), "Rain!", sf::Style::Fullscreen);

	std::default_random_engine engine;
	std::uniform_real_distribution<float> random_x(0.0f, sf::VideoMode::getDesktopMode().width);
	std::uniform_real_distribution<float> random_y(-maxYSpawn, 0.0f);
	std::uniform_real_distribution<float> random_speed(5.0f, 15.0f);
	
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	for (unsigned int i = 0; i < Drops.size(); i++)
	{
		Drops[i].x = random_x(engine);
		Drops[i].y = random_y(engine);
 		Drops[i].width = 3.0f;
		Drops[i].height = 15.0f;
		Drops[i].fallingSpeed = random_speed(engine);
		Drops[i].rect.setFillColor(color);

		Drops[i].SetSettings();
	}
	
	/*
	//do window active
	

	HWND appWindow = window.getSystemHandle();

	SetActiveWindow(appWindow);
	SetFocus(appWindow);
	
	HWND test = GetActiveWindow();
	char buff[500];
	GetWindowText(test, buff, 500);
	std::cout << buff << std::endl;
	*/


	sf::Mouse::setPosition(sf::Vector2i(100, 100));
	defaultYMousePos = sf::Mouse::getPosition().y;

	while (window.isOpen())
	{
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				window.close();
			}
			if (Event.type == sf::Event::LostFocus)
			{
				window.close();
			}
			if (Event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::getPosition().y > defaultYMousePos)
				{
					for (unsigned int i = 0; i < Drops.size(); i++)
					{
						Drops[i].fallingSpeed += 0.1;
					}
				}
				else if(sf::Mouse::getPosition().y < defaultYMousePos)
				{
					for (unsigned int i = 0; i < Drops.size(); i++)
					{
						Drops[i].fallingSpeed -= 0.1;
					}
				}
				sf::Mouse::setPosition(sf::Vector2i(100, 100));
			}
		}

		if (!window.isOpen()) return;

		for (unsigned int i = 0; i < Drops.size(); i++)
		{
			Drops[i].y += Drops[i].fallingSpeed;
			if (Drops[i].y > sf::VideoMode::getDesktopMode().height + maxYSpawn + 1)   // +1 for safety
			{
				Drops[i].y = random_y(engine);
			}
			else if (Drops[i].y < -maxYSpawn - 1)  // -1 for safety
			{
				Drops[i].y = sf::VideoMode::getDesktopMode().height - random_y(engine);
			}

			Drops[i].SetNewPosition();
		}


		window.clear(sf::Color(50, 50, 50, 255));
		for (unsigned int i = 0; i < Drops.size(); i++)
		{
			window.draw(Drops[i].rect);
		}
		window.display();
	}

}

int Window::IntInput()
{
	std::cin.unsetf(std::ios::skipws);

	int i;

	while (true)
	{
		std::cin >> i;

		if (std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');

			return i;
		}

		std::cout << "Неверный ввод! Введите целое число" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
}
