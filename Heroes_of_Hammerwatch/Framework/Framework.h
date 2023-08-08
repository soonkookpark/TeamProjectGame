#pragma once
#include "Singleton.h"

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	Framework(int w, int h, const std::string& t);
	virtual ~Framework() override = default;

	sf::RenderWindow window;
	sf::Clock clock;

	int screenWidth = 1600;
	int screenHeight = 900;
<<<<<<< HEAD
	std::string title = "SFML Works!";
=======
	std::string title = "Heroes_of_Hammerwatch!";
>>>>>>> origin/feature/Character

public:
	virtual void Init(int width, int height, const std::string& title);
	virtual void Release();

	virtual void Update(float dt);
	virtual void Draw();

	virtual void Run();

	sf::Vector2f GetWindowSize();
	sf::RenderWindow& GetWindow();
};

#define FRAMEWORK (Framework::Instance())