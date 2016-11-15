// hge_test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "hge_test.h"

#include <string>

using namespace std;

#pragma comment (lib, "hge.lib")
#pragma comment (lib, "hgehelp.lib")
//#pragma comment (lib,"libcmt.lib")

#define MAX_LOADSTRING 100



// Pointers to the HGE objects we will use
HGE *hge;
//
Position mousePos;
bool mouse_down = false;
std::shared_ptr<hgeSprite>		sprcurs;

HTEXTURE			curs;
hgeQuad				quad;
shared_ptr<WidgetContainer> wcont;   
std::vector<shared_ptr<Widget>> renderVect;

int push = 0;
//main function for update elements
bool FrameFunc()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	mouse_down = hge->Input_GetKeyState(HGEK_LBUTTON);
	hge->Input_GetMousePos(&mousePos.x, &mousePos.y);
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
	if(hge->Input_IsMouseOver() && sprcurs) sprcurs->Render(mousePos.x,mousePos.y);
	hge->Gfx_EndScene();

	return false;
}
//callback functions
void OnMouseEnter(Widget*  widget)
{
  widget->GetWidgetContainer()->GetWidget("img2")->Show();
}
void OnMouseLeave(Widget*  widget)
{
  widget->GetWidgetContainer()->GetWidget("img2")->Hide();
}
void OnMouseClick(Widget*  widget)
{
std::shared_ptr<WidgetContainer> container = widget->GetWidgetContainer()->GetWidgetContainer("container2");
container->Show(!container->IsVisible());
}
bool sortfunc(std::shared_ptr<Widget> i,shared_ptr<Widget>  j) 
{ 
	if (i->GetOrder()<j->GetOrder())
		return true;
	else
		if (i->GetOrder()==j->GetOrder()&& i->GetCreateID()<j->GetCreateID())
			return true;
		else
			return false;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{


	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_TITLE, "HGE");
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate()) {
		quad.tex=hge->Texture_Load("bg.png");
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
		std::vector<HTEXTURE> textures;
		textures.push_back(hge->Texture_Load("btnpop.png"));
		textures.push_back(hge->Texture_Load("btnpush.png"));
		
		wcont = make_shared<WidgetContainer> (WidgetContainer());
				
		auto btn = std::make_shared<WidgetBtn>( WidgetBtn(Position(100.,100.), Size(140.,24.),"btn1",7,TRUE,textures[1], textures[0]));
		btn->AddEventHandler(MSG_BTNCLICK, OnMouseClick);
		wcont->AddWidget(btn, wcont); 
		textures.push_back(hge->Texture_Load("img1.png"));
		auto img = std::make_shared<Widget>(WidgetImg(Position(100.,200.),Size(201.,126.),"img1",1,TRUE,textures[2]));
		img->AddEventHandler(MSG_MOUSEENTER, OnMouseEnter);
		img->AddEventHandler(MSG_MOUSELEAVE, OnMouseLeave);
		wcont->AddWidget(img, wcont);

		textures.push_back(hge->Texture_Load("img2.png"));
		wcont->AddWidget(std::make_shared<Widget>(WidgetImg(Position(100.,200.),Size(201.,126.),"img2",5,FALSE,textures[3])), wcont);
		wcont->Show(true);
		auto wcont2 = std::make_shared<WidgetContainer> (WidgetContainer());
		wcont2->AddWidget(std::make_shared<Widget>(WidgetBtn(Position(350.,100.),Size(140.,24.),"btnz",5,TRUE,textures[1], textures[0])), wcont2);
		wcont2->AddWidget(std::make_shared<Widget>(WidgetImg(Position(350.,200.),Size(201.,126.),"imgz1",2,TRUE,textures[3])), wcont2);
		wcont2->Show(false);
		wcont->AddWidgetCont("container2", wcont2);
		curs=hge->Texture_Load("cursor.png");
	
		sprcurs= std::make_shared<hgeSprite>(hgeSprite(curs,0,0,32,32));
	
		//sort render vector
		std::sort(renderVect.begin(), renderVect.end(),sortfunc);

		hge->System_Start();

		// Delete created objects and free loaded resources
		for(auto i = textures.begin(); i!=textures.end();i++)
			hge->Texture_Free(*i);
		hge->Texture_Free(curs);
		hge->Texture_Free(quad.tex);
	}
	hge->System_Shutdown();
	hge->Release();

	return 0;

}
