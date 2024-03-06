#include <stdio.h>

int fibo(int n) {
	if (n > 0) {
		if (n <= 2) {
			return 1;
		}
		else {
			return fibo(n - 2) + fibo(n - 1);

		}
	}
	else {

		printf("エラー");
		return - 1;
	}
}
int main(void)
{
	int n;
	printf("フィボナッチの数列項を入力して下し\n");
		scanf_s("%d", &n);
	printf("フィボナッチ数列値\n%d", fibo(n));
}