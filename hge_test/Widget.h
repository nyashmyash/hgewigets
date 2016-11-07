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

class WidgetContainer;

class Widget
{

private:
	float posX, posY, width, height;
	std::string id_s;
	int order;
	int idcreate;
	std::shared_ptr<hgeSprite>	pSprBtn;
	int type;
	bool visible;
	bool mouse_entered;
	std::map<int,std::function<void(Widget* )>> events;
	WidgetContainer* pWidgetCont;
	
public:
	Widget(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   bool visibl);
	
	Widget(void){};
	virtual ~Widget(void);

	void SetId(const std::string & id_); // add string id 
	std::string GetId();
	void SetOrder(int order_); // change sort order
	int GetOrder();
	int GetCreateID();
	bool IsVisible();
	std::map<int,std::function<void(Widget* )>> *GetEvents();
	void SetPos(float x, float y); // position widget
	void SetSize(float w, float h); // widget size
	bool MouseInBox();
	virtual bool	MouseLButton(bool bDown);
	virtual void	MouseOver(bool bOver);
	virtual void Update(float dt); // update widget
	virtual void Render(void); // draw widget
	WidgetContainer* GetWidgetContainer();
	std::shared_ptr<hgeSprite> GetSprite();
	void SetWidgetContainer(WidgetContainer* w);
	void Show(); // show widget
	void Hide(); // hide widget
	void AddEventHandler(int hdr,std::function<void(Widget* )> func); // register callback functions
	

};
