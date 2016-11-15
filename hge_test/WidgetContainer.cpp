#include "stdafx.h"
#include "WidgetContainer.h"

WidgetContainer::WidgetContainer(void)
{
}
void WidgetContainer::Show(bool visible)
{
	this->visible = visible;
}
bool WidgetContainer::IsVisible()
{
	return visible;
}
void WidgetContainer::Update(float df)
{
	for (auto i = widgetsMap.begin(); i!=widgetsMap.end();i++)
		i->second->Update(0);
	for (auto i = widgetsContMap.begin(); i!=widgetsContMap.end();i++)
		i->second->Update(0);

}
void WidgetContainer::Render()
{
	for(int i =0;i< renderVect.size();i++)
		renderVect[i]->Render();

}

void WidgetContainer::AddWidget(std::shared_ptr<Widget> widg, std::shared_ptr<WidgetContainer> wcont)
{
	widg->SetWidgetContainer(std::weak_ptr<WidgetContainer>(wcont));
	renderVect.push_back(widg);
	widgetsMap[widg->GetId()] = widg;
}
void WidgetContainer::AddWidgetCont(std::string id, std::shared_ptr<WidgetContainer> pWc)
{
	widgetsContMap[id] = pWc;
}
std::shared_ptr<Widget>  WidgetContainer::GetWidget(std::string id)
{
	auto i = widgetsMap.find(id);
	if(i!=widgetsMap.end())
		return i->second;
	else
		return nullptr;
}
std::shared_ptr<WidgetContainer> WidgetContainer::GetWidgetContainer(std::string id) 
{
	auto i = widgetsContMap.find(id);
	if(i!=widgetsContMap.end())
		return i->second;
	else
		return nullptr;
}

