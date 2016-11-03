#pragma once
#include "Widget.h"
#include "hge_test.h"
class WidgetContainer
{
private:
	bool visibl;
	//std::string id;
	std::map<std::string,Widget*> widgetsMap;
	std::map<std::string,WidgetContainer*> widgetsContMap;
public:
	void addWidget(Widget *v);
	void addWidgetCont(std::string id, WidgetContainer* pWc);
	Widget* GetWidget(std::string id);
	WidgetContainer* GetWidgetContainer(std::string id);
	void Show(bool visibl);
	bool isVisible();
	void Update(float fd);
	void Render();
	WidgetContainer(void);
	~WidgetContainer(void);
};

