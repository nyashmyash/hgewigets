#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <hgegui.h>
#include <memory>
#include <string>
//#include "WidgetContainer.h"

#define MSG_BTNCLICK 1
#define MSG_MOUSEENTER 2
#define MSG_MOUSELEAVE 3

class WidgetContainer;

class Widget
{
protected:
	float posX, posY, width, height;
	std::string id_s;
	int order;
	hgeSprite*	sprBtn;
	int type;
	BOOL visible;
	BOOL mouse_entered;
	std::map<int,std::function<void(Widget *)>> events;
	WidgetContainer* pWidgetCont;
public:
	Widget(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   BOOL visibl);
	
	Widget(void){};
	virtual ~Widget(void);

	void SetId(const std::string & id_); // установить строковый идентификатор 
	std::string GetId();
	void SetOrder(int order_); // для изменения порядка отрисовки виджетов на экране (аппаратный z-order не используется)

	void SetPos(float x, float y); // положение виджета
	void SetSize(float w, float h); // размер виджета. Предполагается что все виджеты – прямоугольники
	bool MouseInBox();
	virtual bool	MouseLButton(bool bDown);
	virtual void	MouseOver(bool bOver);
	virtual void Update(float dt); // обновление состояни виджета
	virtual void Render(void); // отрисовка виджета
	WidgetContainer* GetWidgetContainer();
	void SetWidgetContainer(WidgetContainer* w);
	void Show(); // показать виджет
	void Hide(); // скрыть виджет
	void AddEventHandler(int hdr,std::function<void(Widget *)> func); // регистрация фунций обратного вызова для различных союбытий виджета. 
	

};

class WidgetContainer
{
private:
	bool visibl;
	//std::string id;
	std::map<std::string,Widget*> widgetsMap;
	std::map<std::string,WidgetContainer*> widgetsContMap;
public:
	void addWidget(Widget *v, WidgetContainer* pWc);
	void addWidgetCont(std::string id, WidgetContainer* pWc);
	Widget* GetWidget(std::string id);
	WidgetContainer* GetWidgetContainer(std::string id);
	void Show(bool visibl);
	bool isVisible();
	void Update(float fd);
	void Render();
	WidgetContainer(void);
	~WidgetContainer(void);
};