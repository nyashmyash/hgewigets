#pragma once
#include "Widget.h"
class WidgetImg : public Widget
{
	HTEXTURE imgTex;
public:
	WidgetImg(Position pos, 
		   Size size, 
		   std::string id, 
		   int order, 
		   bool visible,
		   HTEXTURE imgTex);
	
	WidgetImg(void);
	virtual ~WidgetImg(void){};
};

