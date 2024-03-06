#include <stdio.h>
#include <string.h>

struct student
{
	int id;
	char name[256];
	int age;
};

int main(void)
{
	struct student date;
	date.id = 1;
	strcpy_s(date.name, "山田太郎");
	date.age = 18;
	printf ("学生番号：%d名前 : %s 年齢:%d",
		date.id, date. name, date. age);
		return 0;
};
