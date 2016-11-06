#include "stdafx.h"
#include "hge_test.h"
#include "WidgetImg.h"

WidgetImg::WidgetImg(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   bool visibl,
		   HTEXTURE _imgTex): Widget(_x,_y,_width,_height,_id,_order,visibl), imgTex(_imgTex)
{
	GetSprite()->SetTexture(_imgTex);
}

WidgetImg::WidgetImg(void)
{
}


WidgetImg::~WidgetImg(void)
{
	
}
