#include "stdafx.h"
#include "WidgetBtn.h"
#include "hge_test.h"

WidgetBtn::WidgetBtn(float _fX, 
		   float _fY, 
		   float _fWidth, 
		   float _fHeight, 
		   std::string _sId, 
		   int _iOrder, 
		   bool _bVisibl,
		   HTEXTURE _hPushTex,
		   HTEXTURE _hPopTex): Widget(_fX,_fY,_fWidth,_fHeight,_sId,_iOrder,_bVisibl), pushTex(_hPushTex), popTex(_hPopTex)
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
				if (click &&GetEvents()->find(MSG_BTNCLICK)!=GetEvents()->end())
					(*GetEvents())[MSG_BTNCLICK](this);
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
	delete GetSprite();
}
