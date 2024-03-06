#include<stdio.h>

int main(void)
{

    int t[7] = { 5,10,2,7,8,1,9 };
    int i, j, w, n;

    //配列の中身を表示する
    for (i = 0; i <= 6; i++) {
        printf("t[%d]=%d\n", i, t[i]);
    }

    n = 0;

    while (n < 7) {
        j = 6;
        while (j > n) {
            if (t[j - 1] > t[j]) {
                w = t[j - 1];
                t[j - 1] = t[j];
                t[j] = w;
            }
            j = j - 1;
        }
        n = n + 1;
    }

    //配列の中身を表示する
    for (i = 0; i <= 6; i++) {
        printf("t[%d]=%d\n", i, t[i]);
    }
}