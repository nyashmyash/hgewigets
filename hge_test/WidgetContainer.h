#pragma once
#include "Widget.h"
#include "hge_test.h"
class WidgetContainer
{
private:
	bool visibl;
	std::map<std::string,Widget* > widgetsMap; //элементы в контейнеры
	std::map<std::string,WidgetContainer*> widgetsContMap; //список других контейнеров 
public:
	void AddWidget(Widget* v);
	void AddWidgetCont(std::string id, WidgetContainer* pWc);
	Widget*  GetWidget(std::string id);
	WidgetContainer* GetWidgetContainer(std::string id);
	void Show(bool visibl);
	bool IsVisible();
	void Update(float fd);
	void Render();
	WidgetContainer(void);
	~WidgetContainer(void);
};

