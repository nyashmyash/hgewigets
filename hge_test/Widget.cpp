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
	statcreat ++;
	idcreate = statcreat;
	mouse_entered = false; 
	sprBtn= new hgeSprite(NULL, 0,0,_width, _height);
	renderVect.push_back(this);
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
int Widget::GetOrder()
{
	return order;
}
int Widget::GetCreateID()
{
	return idcreate;
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
