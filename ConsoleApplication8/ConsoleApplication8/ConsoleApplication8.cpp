#include <iostream>
#include <string>

//クラス「Item」を定義
class Item
{
public:
    std::string name;
    int price;

    Item(std::string name, int price);

};

//コンストラクタ インスタンス作成時に一度だけ呼び出される特殊なメソッド
Item::Item(std::string name, int price)
{
    this->name = name;
    this->price = price;
}

int main()
{
    int sum;
    //定義したクラスの変数(インスタンス)を宣言
    Item i1("鉛筆", 80);
    Item i2("消しゴム", 100);
    Item i3("ノート", 120);

    sum = i1.price + i2.price + i3.price;


    std::cout << "合計: " << sum;

}