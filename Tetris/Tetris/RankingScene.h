#pragma once
/***************************
*マクロ定義
**************************/
#define RUNKING_INPUT_MOUSE (1)
#define RUNKING_DISP_MOUSE (2)
/*************************
*型定義
***************************/

int RankingScene_Initialize(void);
void  RankingScene_Update(void);
void RankingScene_Draw(void);
void  Set_RankingMode(int mode);
void  Set_RankingMode(int mode);
void  Set_RankingScore(int score);
