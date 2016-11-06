#pragma once
#include "Widget.h"
#include "hge_test.h"
class WidgetContainer
{
private:
	bool visibl;
	std::map<std::string,std::shared_ptr<Widget> > widgetsMap; //элементы в контейнеры
	std::map<std::string,std::shared_ptr<WidgetContainer> > widgetsContMap; //список других контейнеров 
public:
	void AddWidget(std::shared_ptr<Widget> v);
	void AddWidgetCont(std::string id, std::shared_ptr<WidgetContainer> pWc);
	std::shared_ptr<Widget>  GetWidget(std::string id);
	std::shared_ptr<WidgetContainer>  GetWidgetContainer(std::string id);
	void Show(bool visibl);
	bool IsVisible();
	void Update(float fd);
	void Render();
	WidgetContainer(void);
	~WidgetContainer(void);
};

