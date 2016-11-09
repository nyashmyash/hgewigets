#include "stdafx.h"
#include "WidgetBtn.h"
#include "WidgetContainer.h"

WidgetBtn::WidgetBtn(Position pos,
		   Size size, 
		   std::string id, 
		   int order, 
		   bool visible,
		   HTEXTURE pushTex,
		   HTEXTURE popTex): Widget(pos,size,id,order,visible), pushTex(pushTex), popTex(popTex)
{ 
	click = 0;
	GetSprite()->SetTexture(popTex);
}
WidgetBtn::WidgetBtn(void)
{
}
//msg to button with event mouse click
bool WidgetBtn::MouseLButton(bool bDown)
{
	if(IsVisible() && GetWidgetContainer()->IsVisible())
	{
		if (bDown)
		{
			if(MouseInBox())
			{
				click = 1;
				GetSprite()->SetTexture(pushTex);
			}
			else
				GetSprite()->SetTexture(popTex);	
		}
		else
		{
			if(MouseInBox())
			{
				GetSprite()->SetTexture(popTex);	
				if (click &&GetEvents().find(MSG_BTNCLICK)!=GetEvents().end())
					(GetEvents())[MSG_BTNCLICK](this);
				click = 0;
			}
		}

		
	}
	return true;
}
