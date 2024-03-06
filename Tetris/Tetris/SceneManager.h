#pragma once

/*******************
マクロ定義
**********************/

#define D_MODR (-1)
#define D_NORMALITY (0)

/**********************
*型定義
*********************/

enum GAME_MODE
{
	E_TITLE,
	E_GAMEMAIN,
	E_RANKING,
	E_END,
	E_MODE_MAX
};

void SceneManager_Initialize(GAME_MODE mode);
void SceneManager_Update(void);
void SceneManager_Darw(void);

void Change_Initialize(GAME_MODE mode);
int ErrorChek(void);