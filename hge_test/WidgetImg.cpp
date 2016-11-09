#include "stdafx.h"
#include "WidgetImg.h"

WidgetImg::WidgetImg(Position pos,
					 Size size,
				     std::string id, 
				     int order, 
				     bool visible,
				     HTEXTURE imgTex): Widget(pos,size,id,order,visible), imgTex(imgTex)
{
	GetSprite()->SetTexture(imgTex);
}

WidgetImg::WidgetImg(void)
{
}


