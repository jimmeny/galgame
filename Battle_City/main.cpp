#include <hge.h>

HGE *hge=0;
bool RenderFunc()
{
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
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
    hge->System_SetState(HGE_TITLE, "hello world");
    hge->System_SetState(HGE_WINDOWED,true);
    hge->System_SetState(HGE_USESOUND,false);

    if(hge->System_Initiate())
    {
        hge->System_Start();
    }

    hge->System_Shutdown();
    hge->Release();
}