#include "stdafx.h"
#include "Widget.h"
#include "hge_test.h"

Widget::Widget(Position pos,
		   Size size, 
		   std::string id, 
		   int order, 
		   bool visible): pos(pos), size(size), id_s(id), order(order), visible(visible)

{
	statcreat ++;
	idcreate = statcreat;
	mouse_entered = false; 
	pSprBtn	= std::shared_ptr<hgeSprite>( new hgeSprite(NULL, 0,0,size.width, size.height));
}
bool Widget::MouseInBox()
{
	if (mousePos.x>pos.x && mousePos.y>pos.y && mousePos.x<pos.x+pSprBtn->GetWidth() && mousePos.y<pos.y+pSprBtn->GetHeight())
		return true;
	else
		return false;		
}
std::map<int,std::function<void(Widget *)>> &Widget::GetEvents()
{
	return events;
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
void Widget::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Widget::SetSize(float width, float height)
{
	size.width = width;
	size.height = height;
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
		GetSprite()->Render(pos.x,pos.y);
}
void Widget::Show()
{
	visible = true;
}
void Widget::Hide()
{
	visible = false;
}
