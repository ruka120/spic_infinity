#include "all.h"
using namespace GameLib;
int curScene;
int nextScene;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    GameLib::init(L"ê¬Ç¢íπ", 
        SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
    GameLib::setBlendMode(Blender::BS_ALPHA);
    curScene  = SCENE_TITLE;
    nextScene = SCENE_TITLE;
    title_init();
	audio_init();
    while (GameLib::gameLoop())
    {
        input::update();

        if (nextScene != curScene)  
        {
            switch (curScene)      
            {
            case SCENE_TITLE:
                title_end();
                break;
            case SCENE_GAME:
                game_end();
                break;
            }
            switch (nextScene)    
            {
            case SCENE_TITLE:
                title_init();
                break;
            case SCENE_GAME:
                game_init();
                break;
            }
            curScene = nextScene;   
        }

        switch (curScene)
        {
        case SCENE_TITLE:
            title_update();
            break;
        case SCENE_GAME:
            game_update();
            break;
        }

        switch (curScene)
        {
        case SCENE_TITLE:
            title_draw();
            break;
        case SCENE_GAME:
            game_draw();
            break;
        }
        GameLib::present(1, 0);
    }
    switch (curScene)
    {
    case SCENE_TITLE:
        title_end();
        break;
    case SCENE_GAME:
        game_end();
        break;
    }
	audio_uninit();
    GameLib::uninit();

    return 0;
}