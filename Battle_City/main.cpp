#include <hge.h>
#include <hgesprite.h>
#include <hgegui.h>
#include "menu.h"

HGE *hge=0;
HTEXTURE bgtex;
HTEXTURE cursortex;
hgeSprite *bgspr;
hgeSprite *cursorspr;
GfxFont *font;
hgeGUI *gui;

bool RenderFunc()
{
    hge->Gfx_BeginScene();
	bgspr->Render(0,0);

	gui->Render();
    

    font->Print(5, 5, L"かみさまの测试 dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());

    hge->Gfx_EndScene();
    return false;
}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	int id;
	static int lastid=0;

	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		lastid=4; gui->Leave();
	}
	id=gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
			case 1:
			case 2:
			case 3:
				gui->SetFocus(1);
				gui->Enter();
				break;

			case 4: return true;
		}
	}
	else if(id)
	{
		lastid=id; gui->Leave();
	}
    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{ 
    hge=hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT,600);
    hge->System_SetState(HGE_SHOWSPLASH, false);
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
    hge->System_SetState(HGE_FPS,1000);
    hge->System_SetState(HGE_TITLE, "hello world");
    hge->System_SetState(HGE_WINDOWED,true);
    hge->System_SetState(HGE_USESOUND,false);

    if(hge->System_Initiate())
    {
        bgtex=hge->Texture_Load("bg.png");
		cursortex=hge->Texture_Load("cursor.png");

        bgspr=new hgeSprite(bgtex,0,0,800,600);
        font = new GfxFont(L"Microsoft YaHei",12);
        font->SetColor(0xffffffff);

		cursorspr=new hgeSprite(cursortex,0,0,32,32);
		gui=new hgeGUI();

		gui->AddCtrl(new MenuItem(1,400,200,0.0f,L"スタート"));
		gui->AddCtrl(new MenuItem(2,400,240,0.1f,L"オプション"));
		gui->AddCtrl(new MenuItem(3,400,280,0.2f,L"説明"));
		gui->AddCtrl(new MenuItem(4,400,320,0.3f,L"終了"));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(cursorspr);
		gui->SetFocus(1);
		gui->Enter();

        hge->System_Start();

        delete font;
        delete bgspr;
		delete gui;
		delete cursorspr;
        hge->Texture_Free(bgtex);
        hge->Texture_Free(cursortex);
    }

    hge->System_Shutdown();
    hge->Release();
}