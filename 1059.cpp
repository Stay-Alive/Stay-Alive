#include<iostream>
#include<vector>
using namespace std;

long int N;

bool prime(int n) {
	int i;
	if (n == 1)
		return true;
	for (i = 2; i * i < n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int main() {
	int i, n, k;
	scanf("%d", &N);
	n = N;
	printf("%d=", n);
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	for (i = 2; i <= n; i++) {
		if (prime(i)) {
			k = 0;
			while (n % i == 0) {
				k++;
				n /= i;
			}
			if (k == 1)
				printf("%d", i);
			else if(k > 1)
				printf("%d^%d", i, k);
			if (n != 1 && k != 0)
				printf("*");
		}
	}
	return 0;
}