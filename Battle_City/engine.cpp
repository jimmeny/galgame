#include "engine.h"

HGE *Engine::main_hge_ = 0;
char Engine::TITLE[50] = "Game";
const int Engine::SCREEN_WIDTH = 800;
const int Engine::SCREEN_HEIGHT = 600;

bool Engine::FrameFunc()
{
    return Engine::Instance().Update();
}

bool Engine::ReaderFunc()
{
    return Engine::Instance().Render();
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
    main_hge_ = hgeCreate(HGE_VERSION);	

    main_hge_->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    main_hge_->System_SetState(HGE_RENDERFUNC, ReaderFunc);
    main_hge_->System_SetState(HGE_TITLE, TITLE);
    main_hge_->System_SetState(HGE_WINDOWED, true);
    main_hge_->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
    main_hge_->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
    main_hge_->System_SetState(HGE_SCREENBPP, 32);
    main_hge_->System_SetState(HGE_USESOUND, false);
    main_hge_->System_SetState(HGE_SHOWSPLASH, false);	
    main_hge_->System_SetState(HGE_DONTSUSPEND, true);					

    if(main_hge_->System_Initiate())
    {
        Release();
    }

    main_hge_->System_Shutdown();
    main_hge_->Release();
}

bool Engine::Init()   
{
   // if(!m_pMgr->Init())
    //    return false;
    return true;
}

void Engine::Release()    
{
   // m_pMgr->Cleanup();
}

bool Engine::Render()        
{
    main_hge_->Gfx_BeginScene();
    main_hge_->Gfx_Clear(0);


    main_hge_->Gfx_EndScene();
    return false;
}

bool Engine::Update()
{
    if(main_hge_->Input_GetKeyState(HGEK_ESCAPE))
        return true;
    float dt = main_hge_->Timer_GetDelta();

    //return m_pMgr->Update(dt);
    return false;
}

