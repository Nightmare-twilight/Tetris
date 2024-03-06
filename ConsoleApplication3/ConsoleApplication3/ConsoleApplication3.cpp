#include<stdio.h>
int main(void)
{
	int t[5] = { 10,5,7,2,4 };
	int i, j, n, w;
	//配列の中身を表示する
	for (i = 0; i <= 4; i++) {

		printf("t[%d]=%d¥n", i, t[i]);
	}
	n = 1;
	while (i < 5) {
			j = n;
				w =t[1];
    while((j>0)&&(t[j-1]>w)){
		t[j] = t[j - 1];
					
				j = j -1;

	
		}
	t[j] = w;
		n= n + 1;

	}
	//配列の中身を表示する
	for (i = 0; i <= 4; i++) {

		printf("t[%d]=%d¥n", i, t[i]);
	}

}