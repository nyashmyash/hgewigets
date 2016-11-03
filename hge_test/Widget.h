#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <hgegui.h>
#include <memory>
#include <string>

#define MSG_BTNCLICK 1
#define MSG_MOUSEENTER 2
#define MSG_MOUSELEAVE 3

static int statcreat = 0;

class WidgetContainer;

class Widget
{

protected:
	float posX, posY, width, height;
	std::string id_s;
	int order;
	int idcreate;
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

	void SetId(const std::string & id_); // ���������� ��������� ������������� 
	std::string GetId();
	void SetOrder(int order_); // ��� ��������� ������� ��������� �������� �� ������ (���������� z-order �� ������������)
	int GetOrder();
	int GetCreateID();
	void SetPos(float x, float y); // ��������� �������
	void SetSize(float w, float h); // ������ �������. �������������� ��� ��� ������� � ��������������
	bool MouseInBox();
	virtual bool	MouseLButton(bool bDown);
	virtual void	MouseOver(bool bOver);
	virtual void Update(float dt); // ���������� �������� �������
	virtual void Render(void); // ��������� �������
	WidgetContainer* GetWidgetContainer();
	void SetWidgetContainer(WidgetContainer* w);
	void Show(); // �������� ������
	void Hide(); // ������ ������
	void AddEventHandler(int hdr,std::function<void(Widget *)> func); // ����������� ������ ��������� ������ ��� ��������� �������� �������. 
	

};
