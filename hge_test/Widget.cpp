#include "stdafx.h"
#include "Widget.h"
#include "hge_test.h"

Widget::Widget(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   bool visibl): posX(_x), posY(_y), width(_width), height(_height), id_s(_id), order(_order), visible(visibl)

{
	statcreat ++;
	idcreate = statcreat;
	mouse_entered = false; 
	pSprBtn	= std::shared_ptr<hgeSprite>( new hgeSprite(NULL, 0,0,_width, _height));
}
bool Widget::MouseInBox()
{
	if (mx>posX && my>posY && mx<posX+pSprBtn->GetWidth() && my<posY+pSprBtn->GetHeight())
	{return true;}
	else
	{return false;}		
}
std::map<int,std::function<void(Widget *)>> * Widget::GetEvents()
{
	return &events;
}
Widget::~Widget(void)
{
	
}
void Widget::SetWidgetContainer(WidgetContainer* pwCont)
{
   pWidgetCont = pwCont;
}
void Widget::SetId(const std::string & sId)
{
	id_s = sId;
}
std::string  Widget::GetId()
{
	return id_s;
}
void Widget::SetOrder(int iOrder)
{
	order = iOrder;
}
std::shared_ptr<hgeSprite>Widget::GetSprite()
{
	return pSprBtn;
}
int Widget::GetOrder()
{
	return order;
}
bool Widget::IsVisible()
{
	return (bool) visible;
}
int Widget::GetCreateID()
{
	return idcreate;
}
WidgetContainer* Widget::GetWidgetContainer()
{
   return pWidgetCont;
}
void Widget::SetPos(float fX, float fY)
{
	posX = fX;
	posY = fY;
}

void Widget::SetSize(float fWidth, float fHeight)
{
	width = fWidth;
	height = fHeight;
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
	if (visible && pWidgetCont->IsVisible())
		GetSprite()->Render(posX,posY);
}
void Widget::Show()
{
	visible = true;
}
void Widget::Hide()
{
	visible = false;
}
