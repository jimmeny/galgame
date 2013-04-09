#include <hge.h>
#include <hgesprite.h>

HGE *hge=0;
HTEXTURE bgtex;
hgeSprite *bgspr;

bool RenderFunc()
{
    hge->Gfx_BeginScene();

    bgspr->Render(0,0);

    hge->Gfx_EndScene();
    return false;
}

bool FrameFunc()
{
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
    hge->System_SetState(HGE_FPS,30);
    hge->System_SetState(HGE_TITLE, "hello world");
    hge->System_SetState(HGE_WINDOWED,true);
    hge->System_SetState(HGE_USESOUND,false);

    if(hge->System_Initiate())
    {
        bgtex=hge->Texture_Load("bg.png");
        bgspr=new hgeSprite(bgtex,0,0,800,600);
        
        hge->System_Start();
        
        delete bgspr;
        hge->Texture_Free(bgtex);
    }

    hge->System_Shutdown();
    hge->Release();
}