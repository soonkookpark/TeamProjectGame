#pragma once
#include "Singleton.h"

enum class Axis
{
	Horizontal,
	Vertical,
};

enum class CustomKey
{
	CustomKeyHorizontal,
	CustomKeyVertical,
	CustomButton,
};

struct AxisInfo
{
	Axis axis;
	std::list<int> positivies;
	std::list<int> negatives;
	
	float sensi = 3.f;
	float value = 0.f;
};

struct CustomInfo
{


};


class InputMgr : public Singleton<InputMgr>
{
	friend Singleton<InputMgr>;

protected:
	InputMgr();
	virtual ~InputMgr() override = default;

	std::list<int> downList;
	std::list<int> upList;
	std::list<int> ingList;

	sf::Vector2f mousePos;

	std::map<Axis, AxisInfo> axisInfoMap;
	std::map<CustomKey, CustomInfo> customInfoMap;
public:
	void Update(float dt);
	void Update(const sf::Event& ev);

	// Keyboard
	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);

	// Mouse
	const sf::Vector2f& GetMousePos();
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetMouseButtonUp(sf::Mouse::Button button);

	// Axis
	float GetAxis(Axis axis);
	float GetAxisRaw(Axis axis);
};

#define INPUT_MGR (InputMgr::Instance())
