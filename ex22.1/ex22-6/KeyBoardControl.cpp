#include "KeyBoardControl.h"
#include "DxLib.h"

char KeyBoardControl::now_key[KEYCODE_MAX] = {};
char KeyBoardControl::old_key[KEYCODE_MAX] = {};

void KeyBoardControl::Update()
{
	for (int i = 0; i < KEYCODE_MAX; i++)
	{
		old_key[i] = now_key[i];
	}

	GetHitKeyStateAll(now_key);
}
bool KeyBoardControl::GetKeyDown(int key_code)
{
	if (CheckKeyCodeRange(key_code))
	{
		if (now_key[key_code] == TRUE && old_key[key_code] == FALSE)
		{
			return true;
		}
	}
	return false;
}
bool KeyBoardControl::GetKeyUp(int key_code)
{
	if (CheckKeyCodeRange(key_code))
	{
		if (now_key[key_code] == FALSE && old_key[key_code]==TRUE)
		{
			return true;
	}
}
return false;
}
bool KeyBoardControl::CheckKeyCodeRange(int key_code)
{
	if (0 <= key_code && key_code < KEYCODE_MAX)
	{
		return true;
	}
	return false;
}

