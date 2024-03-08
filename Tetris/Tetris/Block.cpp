#include"Block.h"
#include"DxLib.h"
#include"InputControl.h"

/*************************
*マクロ定義
*****************************/
#define FIELD_HEIGHT (21)
#define FIELD_WIDTH (12)
#define BLOCK_TROUT_SIZE (4)
#define BLOCK_SIZE (36)
#define BLOCK_TYPE_MAX (7)
#define BLOCK_NEXT_POS_X (700)
#define BLOCK_NEXT_POS_Y (500)
#define BLOCK_STOCK_POS_X (500)
#define BLOCK_STOCK_POS (350)
#define DROP_BLOCK_INIT_X (4)
#define DROP_BLOCK_INIT_Y (-1)
#define DROP_SPEED (60)
#define TRUN_CROCKWICE (0)
#define TRUN_ANTICROCWICE (1)

/****************************
*型定義
***************************/

enum BLOCK_STATE
{
	E_BLOCK_EMPTY,
	E_BLOCK_LIGHT_BLUE,
	E_BLOCK_YELLOW_GREEN,
	E_BLOCK_YELLOW,
	E_BLOCK_ORANGE,
	E_BLOCK_BULE,
	E_BLOCK_PINK,
	E_BLOCK_RED,
	E_BLOCK_GLAY,
	E_BLOCK_WALL,
	E_BLOCK__IMAGE_MAX,
};

/**********************
*型定義
***********************/
const int C_BLOCK_TABLE[BLOCK_TYPE_MAX][BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE] = {
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}

	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{3,0,0,0},
		{3,3,3,3},
		{0,0,0,0}
	 },
	{
		{0,0,0,0},
		{0,0,0,4},
		{4,4,4,4},
		{0,0,0,0}
	 },
	{
		{0,0,0,0},
		{0,5,5,0},
		{0,0,5,5},
		{0,0,0,0}
	 },
	{
		{0,0,0,0},
		{0,6,6,0},
		{6,6,0,0},
		{0,0,0,0},
    },
	{
		{0,0,0,0},
		{0,7,0,0},
		{7,7,7,0},
		{0,0,0,0}
    }
};

/**************************
*変数宣言
*****************************/

int BlockImage[E_BLOCK_IMAGE_MAX];
BLOCK_STATE Field[FIELD_HEIGHT][FIELD_WIDTH];
BLOCK_STATE Next[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];
BLOCK_STATE Stock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];
BLOCK_STATE DropBlock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];

int DropBlock_X;
int DropBlock_Y;

int WaitTime;
int Stock_Flg;
int Generate_Flg;
int DeleteLine;
int SoundEffect[3];
/*****************************
*プロトタイプ宣言
********************************/

void create_field(void);
void create_block(void);
void move_block(void);
void change_block(void);
void trun_block(int clockwise);
int check_overlap(int x, int y);
void lock_block(int x, int y);
void check_line(void);

int Block_Initialize(void)
{
	int ret = 0;
	int i = 0;

	//ブロック画像読み込み
	ret = LoadDivGraph("images/block.png", E_BLOCK_IMAGE_MAX, 10, 1, BLOCK_SIZE,
		BLOCK_SIZE, BlockImage);

	//SEの読み込み
	SoundEffect[0] = LoadSoundMem("sounds/SE3.mp3");
	SoundEffect[1] = LoadSoundMem("sounds/SE4.mp3");
	SoundEffect[2] = LoadSoundMem("sounds/SE5.wav");

	//音量の調整
	ChangeVolumeSoundMem(150, SoundEffect[0]);
	ChangeVolumeSoundMem(150, SoundEffect[1]);
	ChangeVolumeSoundMem(130, SoundEffect[2]);

	//フィールドの生成
	create_field();

	//ブロック生成
	create_block();
	create_block();

	//待機時間の初期化
	WaitTime = 0;
	//ストックフラグの初期化
	Stock_Flg = FALSE;
	//生成フラグの初期化
	Generate_Flg = TRUE;
	//消したラインの数の初期化
	DeleteLine = 0;

	//エラーチェック
	for (i = 0; i < 3; i++)
	{
		if (SoundEffect[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	return ret;
}

/*************************
*ブロック機能；更新処理
* 引数：なし
＊戻り値：なし
***************************/

void Block_Update(void)
{
	//ブロックの移動処理
	move_block();
	//ブロックのストック
	if ((GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) == TRUE))

	{
		//生成可能であれば
		if (Generate_Flg == TRUE)
		{
			change_block();  //ストック交換処理
			//ブロックの回転を正位置にする
		}


	}

	//ブロックの回転（反時計回り）

	if ((GetButtonDown(XINPUT_BUTTON_A) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_Y) == TRUE))
	{
		turn_block(TRUN_CROCKWICE);
	}

	//ブロックの反転(時計回り）
	if ((GetButtonDown(XINPUT_BUTTON_B) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_X) == TRUE))
	{
		turn_block(TURN_CROCKWICE);
	}

	//落下処理
	WaitTime++;
	if (WaitTime > DROP_SPEED)
	{
		if (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
		else
		{
			//ブロックの固定
			lock_block(DropBlock_X, DropBlock_Y);
			//ブロックの消去とブロックを下す処理
			check_line();
			//新しいブロックの生成
			create_block();
		}
		//カウンタの初期化
		WaitTime = 0;
	}
}

/****************************
*ブロック機能：描画処理
*引数；なし
*戻り値；なし
*************************/

void Block_Draw(void)
{
	int i, j;
	//フィールドのブロックを描画
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			if (Field[i][j] != E_BLOCK_WALL)
			{
				DrawGraph(j * BLOCK_SIZE, i * BLOCK_SIZE, BlockImage[Field[i][j]],
					TRUE);
			}
		}
	}
	//次のブロックとストックされたブロックを描画
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			//次のブロックを描画
			DrawGraph(BLOCK_SIZE * j + BLOCK_NEXT_POS_X, BLOCK_SIZE * i + BLOCK_NEXT_POS_Y, BlockImage[Next[i][j]], TRUE);
			//次のブロックを描画
			DrawGraph(BLOCK_SIZE * j + BLOCK_NEXT_POS_X, BLOCK_SIZE * i + BLOCK_NEXT_POS_Y, BlockImage[Stock[i][j]], TRUE);
		}

	}
	//落ちてくるブロックの描画
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			DrawGrap((DropBlock_X + j) * BLOCK_SIZE, (DropBlock_Y + i) * BLOCK_SIZE,
				BlockImage[DropBlock[i][j]], TRUE);
		}
	}
}
/**********************
*ブロック機能；ブロックの生成判定処理
*引数；なし
*戻り値；なし
****************************/

int Get_GenerateFlg(void)
{
	return Generate_Flg;
}

/*******************
*ブロック機能：消したラインの数取得処理
*引数；なし
*戻り値:なし
*************************/

int Get_Line(void)
{
	return DeleteLine;
}


/*********************
*ブロック機能：フィールド生成処理
*引数：なし
*戻り値：なし
*************************/

void create_field(void)
{
	int i, j;
	//フィールドの生成
	for (i = 0; j < FIELD_WIDTH; j++)
	{
		//フィールド値の設定
		if (j == 0 || j == FIELD_WIDTH -1 || i == FIELD_HEIGHT -1)

		{
			Field[i][j] = E_BLOCK_WALL;  
		}
		else
		{
			Field[i][j] = E_BLOCK_EMPTY;
		}
	}
}

/*****************************
*ブロック機能：ブロック生成処理
＊引数；なし
＊戻り値なし
*******************************/

void create_block(void)
{
	int i, j;
	int block_type;
	//つぎにしゅつげさせるブロックを決定する
	block_type = GetRand(BLOCK_TYPE_MAX - 1);

	//新しいブロックをセット＆次のブロック生成
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			DropBlock[i][j] = Next[i][j];
			Next[i][j] = (BLOCK_STATE)C_BLOCK_TABLE[block_type][i][j];
		}
	}
	//出現の位置の設定
	DropBlock_X = DROP_BLOCK_INIT_X;
	DropBlock_Y = DROP_BLOCK_INIT_Y;


	//生成できなかった時、ゲームオーバーにする
	if (check_overlap(DropBlock_X, DropBlock_Y) == FALSE)
	{
		Generate_Flg = FALSE;
	}
}

/***************************
*ブロック機能；ブロックの移動処理
*引数なし
戻り値：無し
*********************************/

void move_block(void)
{
	//ひだりにゅうりょく
	if (GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (check_overlap(DropBlock_X - 1, DropBlock_Y) == TRUE)
		{
			DropBlock_X--;
		}
	}

	//右入力時
	if (GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (check_overlap(DropBlock_X + 1, DropBlock_Y) == TRUE)
		{
			DropBlock_X++;
		}
	}
	//上入力時（ハードドロップ）
	if (GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		while (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
	}
	//下入力時（ソフトそっぷ処理)
	if (GetButton(XINPUT_BUTTON_DPAD_DOWN))

}


