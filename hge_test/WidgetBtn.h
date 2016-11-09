#pragma once
#include "Widget.h"
class WidgetBtn : public Widget
{
	HTEXTURE pushTex;
	HTEXTURE popTex;
	int click;
public:
	WidgetBtn(Position pos,
		   Size size, 
		   std::string id, 
		   int order, 
		   bool visible,
		   HTEXTURE pushTex,
		   HTEXTURE popTex);
	WidgetBtn(void);
	virtual bool MouseLButton(bool bDown);

	virtual ~WidgetBtn(void) {};
};

