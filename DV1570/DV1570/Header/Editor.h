#pragma once
#include "Object.h"
#include <vector>

class Editor
{
private:
	std::vector<Object> m_destructibleMapElements;
	std::vector<Object> m_indestructibleMapElements;
	bool m_buildMode;
	bool m_indestructibleElements;

	void _init();

public:
	Editor();
	~Editor();


	void enterBuildMode();
	void exitBuildMode();

	bool getIndestructibleElements() const;
	void setIndestructibleElements(bool indestructible);

	void draw() const;
	void update();
};