//教科書 187ページ　継承・オーバーライドのサンプルプログラム
#include <iostream>
#include <string>

//クラス「Date」を定義
class Date
{
public:
    int year;
    int month;
    int day;

public:

    void toString() {
        std::cout << year << "/" << month << "/" << day << std::endl;
    }
    void getWeekDay() {
        std::cout << "Sunday" << std::endl;
    }
};

//クラスDateを継承してクラスJapaneseDateを定義する。
class JapaneseDate : public Date
{
public:
    //追加したメンバ変数
    std::string gengo;

public:
    //メソッドのオーバーライド
    void getWeekDay() {
        std::cout << "日曜日" << std::endl;
    }
    //追加したメソッド
    void getWarekiYear() {
        std::cout << "5" << std::endl;
    }
};


int main() {

    // クラス　Dateをインスタンス化
    Date d;
    d.year = 2023;
    d.month = 4;
    d.day = 1;
    d.toString();
    d.getWeekDay();

    JapaneseDate jd;
    jd.year = 2023;
    jd.month = 4;
    jd.day = 1;
    jd.gengo = "令和";
    //継承したメソッド
    jd.toString();
    //継承したメソッドをオーバーライド
    jd.getWeekDay();
    //追加したメンバ変数を表示
    std::cout << jd.gengo << std::endl;
    //追加したメソッド
    jd.getWarekiYear();
}