#include "stdafx.h"
#include "Widget.h"
#include "hge_test.h"

Widget::Widget(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   BOOL visibl): posX(_x), posY(_y), width(_width), height(_height), id_s(_id), order(_order), visible(visibl)

{
	mouse_entered = false; 
	sprBtn= new hgeSprite(NULL, 0,0,_width, _height);
}
bool Widget::MouseInBox()
{
	if (mx>posX && my>posY && mx<posX+sprBtn->GetWidth() && my<posY+sprBtn->GetHeight())
	{return true;}
	else
	{return false;}		
}

Widget::~Widget(void)
{
	
}
void Widget::SetWidgetContainer(WidgetContainer* w)
{
   pWidgetCont = w;
}
void Widget::SetId(const std::string & id_)
{
	id_s = id_;
}
std::string  Widget::GetId()
{
	return id_s;
}
void Widget::SetOrder(int order_)
{
	order = order_;
}
WidgetContainer* Widget::GetWidgetContainer()
{
   return pWidgetCont;
}
void Widget::SetPos(float x, float y)
{
	posX = x;
	posY = y;
}

void Widget::SetSize(float w, float h)
{
	width = w;
	height = h;
}

bool Widget::MouseLButton(bool bDown)
{
	return true;
}
void Widget::AddEventHandler(int id_hdr,std::function<void(Widget *)> func)
{
	events[id_hdr]=func;
}
void Widget::MouseOver(bool bOver)
{
	
}

void Widget::Update(float dt)
{
	if (events.find(MSG_MOUSEENTER)!=events.end())
	{
		if(MouseInBox()&& mouse_entered == false)
			events[MSG_MOUSEENTER](this);
		mouse_entered = true; 
	}
	if (events.find(MSG_MOUSELEAVE)!=events.end())
	{
		if(!MouseInBox()&& mouse_entered == true)
			events[MSG_MOUSELEAVE](this);
		mouse_entered = false; 
	}
	MouseLButton(mouse_down);
}

void Widget::Render(void)
{
	if (visible && pWidgetCont->isVisible())
		sprBtn->Render(posX,posY);
}
void Widget::Show()
{
	visible = true;
}
void Widget::Hide()
{
	visible = false;
}



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

}
void WidgetContainer::Render()
{
	//std::map<int,Widget*> new_map_order;
	for (auto i = widgetsMap.begin(); i!=widgetsMap.end();i++)
		i->second->Render();
	for (auto i = widgetsContMap.begin(); i!=widgetsContMap.end();i++)
		i->second->Render();

}
void WidgetContainer::addWidget(Widget *v, WidgetContainer* pWc)
{
	v->SetWidgetContainer( pWc);
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
