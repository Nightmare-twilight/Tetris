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
	strcpy_s(date.name, "�R�c���Y");
	date.age = 18;
	printf ("�w���ԍ��F%d���O : %s �N��:%d",
		date.id, date. name, date. age);
		return 0;
};
