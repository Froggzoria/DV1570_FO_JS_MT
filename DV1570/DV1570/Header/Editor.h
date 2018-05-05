#pragma once
#include "Object.h"
#include <vector>

class Editor
{
private:
	std::vector<Object> m_mapElements;
	bool m_buildMode;

	void _init();

public:
	Editor();
	~Editor();


	void enterBuildMode();
	void exitBuildMode();

	void draw() const;
	void update();
};