#include "stdafx.h"
#include "WidgetContainer.h"
WidgetContainer::WidgetContainer(void)
{
}
void WidgetContainer::Show(bool _visibl)
{
	visibl = _visibl;
}
bool WidgetContainer::isVisible()
{
	return visibl;
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
	/*for (auto i = widgetsMap.begin(); i!=widgetsMap.end();i++)
		i->second->Render();
	for (auto i = widgetsContMap.begin(); i!=widgetsContMap.end();i++)
		i->second->Render();
		*/
}
void WidgetContainer::addWidget(Widget *v)
{
	v->SetWidgetContainer( this);
	widgetsMap[v->GetId()] = v;
}
void WidgetContainer::addWidgetCont(std::string id, WidgetContainer* pWc)
{
	widgetsContMap[id] = pWc;
}

Widget* WidgetContainer::GetWidget(std::string id)
{
	auto i = widgetsMap.find(id);
	if(i!=widgetsMap.end())
		return widgetsMap[id];
	else
		return NULL;
}
WidgetContainer* WidgetContainer::GetWidgetContainer(std::string id) 
{
	auto i = widgetsContMap.find(id);
	if(i!=widgetsContMap.end())
		return widgetsContMap[id];
	else
		return NULL;
}
WidgetContainer::~WidgetContainer(void)
{
	for(auto i = widgetsContMap.begin();i!= widgetsContMap.end(); i++)
		delete i->second;
}
