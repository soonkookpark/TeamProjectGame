#pragma once
#include "Scene.h"
#include "StringTable.h"
#include "DataTableMgr.h"
#include "Framework.h"

class SpriteGo;
class SceneTitle : public Scene
{
protected:
	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	SpriteGo* endIcon;
	SpriteGo* mapTool;
	SpriteGo* playGame;
public:

	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void TestCode(float dt);
	void UIButtonMaker();
};

