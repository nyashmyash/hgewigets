
#include "Widget.h"
#pragma once
#include "hge_test.h"

class WidgetContainer
{
private:
	bool visible;
	std::map<std::string,std::shared_ptr<Widget> > widgetsMap; //widgets in container
	std::map<std::string,std::shared_ptr<WidgetContainer> > widgetsContMap; //other containers
public:
	void AddWidget(std::shared_ptr<Widget> v);
	void AddWidgetCont(std::string id, std::shared_ptr<WidgetContainer> pWc);
	std::shared_ptr<Widget>  GetWidget(std::string id);
	std::shared_ptr<WidgetContainer>  GetWidgetContainer(std::string id);
	void Show(bool visible);
	bool IsVisible();
	void Update(float fd); //update widgets in container
	void Render(); //redraw widgets in container
	WidgetContainer(void);
	~WidgetContainer(void) {};
};

