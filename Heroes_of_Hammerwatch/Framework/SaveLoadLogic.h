#pragma once
#include "Singleton.h"
class SaveLoadLogic : public Singleton<SaveLoadLogic>
{
	friend Singleton<SaveLoadLogic>;

protected:
public:
	SaveLoadLogic() = default;
	~SaveLoadLogic() = default;
};

