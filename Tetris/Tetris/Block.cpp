#include"Block.h"
#include"DxLib.h"
#include"InputControl.h"

/*************************
*�}�N����`
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
*�^��`
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
*�^��`
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
*�ϐ��錾
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
*�v���g�^�C�v�錾
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

	//�u���b�N�摜�ǂݍ���
	ret = LoadDivGraph("images/block.png", E_BLOCK_IMAGE_MAX, 10, 1, BLOCK_SIZE,
		BLOCK_SIZE, BlockImage);

	//SE�̓ǂݍ���
	SoundEffect[0] = LoadSoundMem("sounds/SE3.mp3");
	SoundEffect[1] = LoadSoundMem("sounds/SE4.mp3");
	SoundEffect[2] = LoadSoundMem("sounds/SE5.wav");

	//���ʂ̒���
	ChangeVolumeSoundMem(150, SoundEffect[0]);
	ChangeVolumeSoundMem(150, SoundEffect[1]);
	ChangeVolumeSoundMem(130, SoundEffect[2]);

	//�t�B�[���h�̐���
	create_field();

	//�u���b�N����
	create_block();
	create_block();

	//�ҋ@���Ԃ̏�����
	WaitTime = 0;
	//�X�g�b�N�t���O�̏�����
	Stock_Flg = FALSE;
	//�����t���O�̏�����
	Generate_Flg = TRUE;
	//���������C���̐��̏�����
	DeleteLine = 0;

	//�G���[�`�F�b�N
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
*�u���b�N�@�\�G�X�V����
* �����F�Ȃ�
���߂�l�F�Ȃ�
***************************/

void Block_Update(void)
{
	//�u���b�N�̈ړ�����
	move_block();
	//�u���b�N�̃X�g�b�N
	if ((GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) == TRUE))

	{
		//�����\�ł����
		if (Generate_Flg == TRUE)
		{
			change_block();  //�X�g�b�N��������
			//�u���b�N�̉�]�𐳈ʒu�ɂ���
		}


	}

	//�u���b�N�̉�]�i�����v���j

	if ((GetButtonDown(XINPUT_BUTTON_A) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_Y) == TRUE))
	{
		turn_block(TRUN_CROCKWICE);
	}

	//�u���b�N�̔��](���v���j
	if ((GetButtonDown(XINPUT_BUTTON_B) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_X) == TRUE))
	{
		turn_block(TURN_CROCKWICE);
	}

	//��������
	WaitTime++;
	if (WaitTime > DROP_SPEED)
	{
		if (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
		else
		{
			//�u���b�N�̌Œ�
			lock_block(DropBlock_X, DropBlock_Y);
			//�u���b�N�̏����ƃu���b�N����������
			check_line();
			//�V�����u���b�N�̐���
			create_block();
		}
		//�J�E���^�̏�����
		WaitTime = 0;
	}
}

/****************************
*�u���b�N�@�\�F�`�揈��
*�����G�Ȃ�
*�߂�l�G�Ȃ�
*************************/

void Block_Draw(void)
{
	int i, j;
	//�t�B�[���h�̃u���b�N��`��
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
	//���̃u���b�N�ƃX�g�b�N���ꂽ�u���b�N��`��
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			//���̃u���b�N��`��
			DrawGraph(BLOCK_SIZE * j + BLOCK_NEXT_POS_X, BLOCK_SIZE * i + BLOCK_NEXT_POS_Y, BlockImage[Next[i][j]], TRUE);
			//���̃u���b�N��`��
			DrawGraph(BLOCK_SIZE * j + BLOCK_NEXT_POS_X, BLOCK_SIZE * i + BLOCK_NEXT_POS_Y, BlockImage[Stock[i][j]], TRUE);
		}

	}
	//�����Ă���u���b�N�̕`��
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
*�u���b�N�@�\�G�u���b�N�̐������菈��
*�����G�Ȃ�
*�߂�l�G�Ȃ�
****************************/

int Get_GenerateFlg(void)
{
	return Generate_Flg;
}

/*******************
*�u���b�N�@�\�F���������C���̐��擾����
*�����G�Ȃ�
*�߂�l:�Ȃ�
*************************/

int Get_Line(void)
{
	return DeleteLine;
}


/*********************
*�u���b�N�@�\�F�t�B�[���h��������
*�����F�Ȃ�
*�߂�l�F�Ȃ�
*************************/

void create_field(void)
{
	int i, j;
	//�t�B�[���h�̐���
	for (i = 0; j < FIELD_WIDTH; j++)
	{
		//�t�B�[���h�l�̐ݒ�
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
*�u���b�N�@�\�F�u���b�N��������
�������G�Ȃ�
���߂�l�Ȃ�
*******************************/

void create_block(void)
{
	int i, j;
	int block_type;
	//���ɂ����������u���b�N�����肷��
	block_type = GetRand(BLOCK_TYPE_MAX - 1);

	//�V�����u���b�N���Z�b�g�����̃u���b�N����
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			DropBlock[i][j] = Next[i][j];
			Next[i][j] = (BLOCK_STATE)C_BLOCK_TABLE[block_type][i][j];
		}
	}
	//�o���̈ʒu�̐ݒ�
	DropBlock_X = DROP_BLOCK_INIT_X;
	DropBlock_Y = DROP_BLOCK_INIT_Y;


	//�����ł��Ȃ��������A�Q�[���I�[�o�[�ɂ���
	if (check_overlap(DropBlock_X, DropBlock_Y) == FALSE)
	{
		Generate_Flg = FALSE;
	}
}

/***************************
*�u���b�N�@�\�G�u���b�N�̈ړ�����
*�����Ȃ�
�߂�l�F����
*********************************/

void move_block(void)
{
	//�Ђ���ɂイ��傭
	if (GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (check_overlap(DropBlock_X - 1, DropBlock_Y) == TRUE)
		{
			DropBlock_X--;
		}
	}

	//�E���͎�
	if (GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (check_overlap(DropBlock_X + 1, DropBlock_Y) == TRUE)
		{
			DropBlock_X++;
		}
	}
	//����͎��i�n�[�h�h���b�v�j
	if (GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		while (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
	}
	//�����͎��i�\�t�g�����Տ���)
	if (GetButton(XINPUT_BUTTON_DPAD_DOWN))

}


