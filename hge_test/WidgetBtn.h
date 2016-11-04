#pragma once
#include "Widget.h"
class WidgetBtn : public Widget
{
	HTEXTURE pushTex;
	HTEXTURE popTex;
	int click;
public:
	WidgetBtn(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   bool visibl,
		   HTEXTURE _pushTex,
		   HTEXTURE _popTex);
	WidgetBtn(void);
	virtual bool MouseLButton(bool bDown);

	virtual ~WidgetBtn(void);
};

