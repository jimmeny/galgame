#include <hge.h>
#include "singleton.h"

class Engine
    : public Singleton<Engine>
{
public:
    Engine();
    ~Engine();

    void Run();
private:
    static bool FrameFunc();
    static bool ReaderFunc();

    bool Init();
    void Release();
    bool Render();
    bool Update();
private:
    static HGE *main_hge_;
    static char TITLE[50];
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
};