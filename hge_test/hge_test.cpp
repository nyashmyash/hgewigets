// hge_test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "hge_test.h"

#include "Widget.h"
#include "WidgetBtn.h"
#include "WidgetImg.h"
#include <string>

using namespace std;

#pragma comment (lib, "hge.lib")
#pragma comment (lib, "hgehelp.lib")
//#pragma comment (lib,"libcmt.lib")

#define MAX_LOADSTRING 100


// Pointers to the HGE objects we will use
HGE *hge = NULL;
float mx, my;
bool mouse_down = false;
hgeSprite*		sprcurs;
//hgeSprite*			spt;
hgeFont		*	fnt;

HTEXTURE			curs;
hgeQuad				quad;
WidgetContainer* wcont;      
// Some "gameplay" variables
//float x=100.0f, y=100.0f, s=0.01;

int push = 0;
bool FrameFunc()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	mouse_down = hge->Input_GetKeyState(HGEK_LBUTTON);
	hge->Input_GetMousePos(&mx, &my);
	wcont->Update(0);
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	t+=dt;
	tx=50*cosf(t/90);
	ty=70*sinf(t/90);
	quad.v[0].tx=tx;        quad.v[0].ty=ty;
	quad.v[1].tx=tx+800/64; quad.v[1].ty=ty;
	quad.v[2].tx=tx+800/64; quad.v[2].ty=ty+600/64;
	quad.v[3].tx=tx;        quad.v[3].ty=ty+600/64;

	return false;
}

bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	hge->Gfx_RenderQuad(&quad);
	wcont->Render();
	if(hge->Input_IsMouseOver() && sprcurs) sprcurs->Render(mx,my);
	fnt->SetColor(0x1111FFFF);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();

	return false;
}
void OnMouseEnter(Widget * widget)
{
  widget->GetWidgetContainer()->GetWidget("img2")->Show();
}
void OnMouseLeave(Widget * widget)
{
  widget->GetWidgetContainer()->GetWidget("img2")->Hide();
}
void OnMouseClick(Widget * widget)
{
WidgetContainer* container = widget->GetWidgetContainer()->GetWidgetContainer("container2");
container->Show(!container->isVisible());
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{


	hge =  hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_TITLE, "HGE");
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate()) {
		char path[100];
		std::string str;
		GetCurrentDirectoryA(100, path);
		str =path + std::string("\\bg.png");
		quad.tex=hge->Texture_Load(str.c_str());
		// Set up the quad we will use for background animation
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFFFFF;
		}

		quad.v[0].x=0; quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0; quad.v[3].y=600; 

		// Load texture
		
		str = path + std::string("\\btnpop.png");
		HTEXTURE btnpoptex=hge->Texture_Load(str.c_str());
		str = path + std::string("\\btnpush.png");
		HTEXTURE btnpushtex=hge->Texture_Load(str.c_str());
		
		wcont = new WidgetContainer();
				
		WidgetBtn* btn = new WidgetBtn(100.,100.,140.,24.,"btn1",1,TRUE,btnpushtex, btnpoptex);
		btn->AddEventHandler(MSG_BTNCLICK, OnMouseClick);
		wcont->addWidget(btn, wcont); 

		str = path + std::string("\\img1.png");
		HTEXTURE teximg1=hge->Texture_Load(str.c_str());
		WidgetImg *img = new WidgetImg(100.,200.,201.,126.,"img1",2,TRUE,teximg1);
		img->AddEventHandler(MSG_MOUSEENTER, OnMouseEnter);
		img->AddEventHandler(MSG_MOUSELEAVE, OnMouseLeave);
		wcont->addWidget(img, wcont);

		str = path + std::string("\\img2.png");
		HTEXTURE teximg2=hge->Texture_Load(str.c_str());
		wcont->addWidget(new WidgetImg(100.,200.,201.,126.,"img2",3,FALSE,teximg2), wcont);
		wcont->Show(true);
		WidgetContainer* wcont2 = new WidgetContainer();
		wcont2->addWidget(new WidgetBtn(350.,100.,140.,24.,"btnz",4,TRUE,btnpushtex, btnpoptex),wcont2);
		wcont2->addWidget(new WidgetImg(350.,200.,201.,126.,"imgz1",5,TRUE,teximg1), wcont2);
		wcont2->Show(false);
		wcont->addWidgetCont("container2", wcont2);

		str = path + std::string("\\cursor.png");
		curs=hge->Texture_Load(str.c_str());
	
		sprcurs= new hgeSprite(curs,0,0,32,32);

		str = path +std::string("\\font1.fnt"); 
		// Load a font
		fnt= new hgeFont(str.c_str());
		
		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		
		hge->Texture_Free(curs);
		hge->Texture_Free(quad.tex);
		delete sprcurs;
		delete fnt;
		delete wcont;
	}
	hge->System_Shutdown();
	hge->Release();

	return 0;

}