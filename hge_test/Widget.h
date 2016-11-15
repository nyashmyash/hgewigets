#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <hgegui.h>
#include <memory>
#include <string>
//messages for callback
#define MSG_BTNCLICK 1
#define MSG_MOUSEENTER 2
#define MSG_MOUSELEAVE 3

static int statcreat = 0;


struct Position
{
	float x;
	float y;
	Position()
	{
		x = 0;
		y = 0;
	}
	Position(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Position(const Position & pos)
	{
		x = pos.x;
		y = pos.y;
	}
};
struct Size
{
	float width;
	float height;
	Size()
	{
		width = 0;
		height = 0;
	}

	Size (float width,float height)
	{
		this->width = width;
		this->height = height;
	}
	Size(const Size &size)
	{
		width = size.width;
		height = size.height;
	}
};


class WidgetContainer;

class Widget
{
private:
	Position pos;
	Size size;
	std::string id_s;
	int order;
	int idcreate;
	std::shared_ptr<hgeSprite>	pSprBtn;
	int type;
	bool visible;
	bool mouse_entered;
	std::map<int,std::function<void(Widget* )>> events;
	std::weak_ptr<WidgetContainer> pWidgetCont;
private:
	//Widget(const Widget &) = delete;
	//void operator =(const Widget &) = delete;
	
public:
	Widget(Position pos,
		   Size size, 
		   std::string id, 
		   int order, 
		   bool visible);
	Widget(void){};
	virtual ~Widget(void);

	void SetId(const std::string & id); // add string id 
	std::string GetId();
	void SetOrder(int order); // change sort order
	int GetOrder();
	int GetCreateID();
	bool IsVisible();
	std::map<int,std::function<void(Widget* )>> &GetEvents();
	void SetPos(float x, float y); // position widget
	void SetSize(float w, float h); // widget size
	bool MouseInBox();
	virtual bool	MouseLButton(bool bDown);
	virtual void	MouseOver(bool bOver);
	virtual void Update(float dt); // update widget
	virtual void Render(void); // draw widget
	std::shared_ptr<WidgetContainer> GetWidgetContainer();
	std::shared_ptr<hgeSprite> GetSprite();
	void SetWidgetContainer(std::weak_ptr<WidgetContainer> w);
	void Show(); // show widget
	void Hide(); // hide widget
	void AddEventHandler(int hdr,std::function<void(Widget* )> func); // register callback functions
	

};
