#include "stdafx.h"
#include "WidgetBtn.h"
#include "hge_test.h"

WidgetBtn::WidgetBtn(float _x, 
		   float _y, 
		   float _width, 
		   float _height, 
		   std::string _id, 
		   int _order, 
		   BOOL visibl,
		   HTEXTURE _pushTex,
		   HTEXTURE _popTex): Widget(_x,_y,_width,_height,_id,_order,visibl), pushTex(_pushTex), popTex(_popTex)
{ 
	click = 0;
	sprBtn->SetTexture(popTex);
}
WidgetBtn::WidgetBtn(void)
{
}
//msg to button with event mouse click
bool WidgetBtn::MouseLButton(bool bDown)
{
	if(visible && GetWidgetContainer()->isVisible())
	{
		if (bDown)
		{
			if(MouseInBox())
			{
				click = 1;
				sprBtn->SetTexture(pushTex);
			}
			else
				sprBtn->SetTexture(popTex);	
		}
		else
		{
			if(MouseInBox())
			{
				sprBtn->SetTexture(popTex);	
				if (click &&events.find(MSG_BTNCLICK)!=events.end())
					events[MSG_BTNCLICK](this);
				click = 0;
			}
		}

		
	}
	return true;
}

//delete textures
WidgetBtn::~WidgetBtn(void)
{
	hge->Texture_Free(pushTex);
	hge->Texture_Free(popTex);
	delete sprBtn;
}
