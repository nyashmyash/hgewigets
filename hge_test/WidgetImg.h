#pragma once
#include "Widget.h"
class WidgetImg : public Widget
{
	HTEXTURE imgTex;
public:
	WidgetImg(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   bool visibl,
		   HTEXTURE _imgTex);
	
	//virtual void	MouseOver(bool bOver);

	WidgetImg(void);
	virtual ~WidgetImg(void);
};

