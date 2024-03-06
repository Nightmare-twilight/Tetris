#include <stdio.h>
#include <string.h>


//学生を表す構造体
//構造体 struct gakusei型
struct gakusei {
    char studentNo[10];
    char name[20];
    int kokugo;
    int sugaku;
    int eigo;
};


int main(void)
{
    //構造体配列を使う場合は配列にも名前をつける必要がある。
    //データは、1つだけ入力している。

    struct gakusei gakusei[10];
    int i;

    strcpy_s(gakusei[0].studentNo, "1001");
    strcpy_s(gakusei[0].name, "山田一郎");
    gakusei[0].kokugo = 52;
    gakusei[0].sugaku = 71;
    gakusei[0].eigo = 46;

    strcpy_s(gakusei[1].studentNo, "1004");
    strcpy_s(gakusei[1].name, "鈴木次郎");
    gakusei[1].kokugo = 90;
    gakusei[1].sugaku = 98;
    gakusei[1].eigo = 99;

    //ドット演算子 (.operator）を用いて表す
    for (i = 0; i < 2; i++) {
        printf("番号 = %s\n", gakusei[i].studentNo);
        printf("氏名 = %s\n", gakusei[i].name);
        printf("国語 = %d\n", gakusei[i].kokugo);
        printf("数学 = %d\n", gakusei[i].sugaku);
        printf("英語 = %d\n", gakusei[i].eigo);
    }
}