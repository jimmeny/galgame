#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <GfxFont.h>

HGE *hge=0;
HTEXTURE bgtex;
HTEXTURE fishtex;
HTARGET  target;

hgeSprite *bgspr;
hgeSprite *tar;
GfxFont *font;
hgeAnimation *anim;

bool GfxRestoreFunc()
{
    if(tar && target)
        tar->SetTexture(hge->Target_GetTexture(target));
    return false;
}

float speed = -0.5;
float x = 800,y = 40;
float dt ;

bool RenderFunc()
{
    dt = hge->Timer_GetDelta();
    anim->Update(dt); 

    hge->Gfx_BeginScene(target);
    hge->Gfx_Clear(0xFF000000);
    anim->Render(0,0);
    hge->Gfx_EndScene();

    hge->Gfx_BeginScene();
    tar->Render(x,y);
    hge->Gfx_EndScene();

    x += speed;
    //hge->Gfx_BeginScene();

    //bgspr->Render(0,0);
    //font->Print(5, 5, L"测试 dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());
    //printf("dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());
    //hge->Gfx_EndScene();
    return false;
}

bool FrameFunc()
{
    
    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{ 
#ifndef  NDEBUG     
    AllocConsole();
    FILE *stream;
    freopen_s(&stream,"CONOUT$","a",stdout);
#endif
    printf("Start!\n\n");

    hge=hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT,600);
    hge->System_SetState(HGE_SHOWSPLASH, false);
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
    hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
    hge->System_SetState(HGE_FPS,30);
    hge->System_SetState(HGE_TITLE, "hello world");
    hge->System_SetState(HGE_WINDOWED,true);
    hge->System_SetState(HGE_USESOUND,false);
    hge->System_SetState(HGE_DONTSUSPEND, true);

    target = 0;
    tar = 0;

    if(hge->System_Initiate())
    {
        //bgtex=hge->Texture_Load("bg.png");
        fishtex = hge->Texture_Load("fish.png");
        anim = new hgeAnimation(fishtex,20,20,0,0,hge->Texture_GetWidth(fishtex,false)/10.0,hge->Texture_GetHeight(fishtex,false)/2.0);
        anim->Play();
        target = hge->Target_Create(hge->Texture_GetWidth(fishtex,false)/10.0,hge->Texture_GetHeight(fishtex,false)/2.0,false);
        tar=new hgeSprite(hge->Target_GetTexture(target), 0, 0, hge->Texture_GetWidth(fishtex,false)/10.0, hge->Texture_GetHeight(fishtex,false)/2.0);
        //bgspr=new hgeSprite(bgtex,0,0,800,600);
        //font = new GfxFont(L"Microsoft YaHei",12);
        //font->SetColor(0xffffffff);
        hge->System_Start();
        
        delete anim;
        delete font;
        delete bgspr;
        delete tar;
        hge->Texture_Free(bgtex);
    }

    hge->System_Shutdown();
    hge->Release();
}