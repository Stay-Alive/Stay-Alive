#include<iostream>
#include<vector>
using namespace std;

int NP, NG;
int *W, *P, *r;

void ranking(vector<int> v) {
	int i, j, idx, max = 0, n = v.size() / NG;
	vector<int> win;
	for (i = 0; i < n; i++) {
		max = 0;
		for (j = 0; j < NG; j++) {
			if (max < W[v[i * NG + j]]) {
				max = W[v[i * NG + j]];
				idx = v[i * NG + j];
			}
		}
		win.push_back(idx);
	}
	max = 0;
	for (i = i * NG; i < v.size(); i++) {
		if (max < W[v[i]]) {
			max = W[v[i]];
			idx = v[i];
		}
	}
	if(v.size() % NG != 0)
		win.push_back(idx);
	n = win.size();
	for (i = 0; i < v.size(); i++)
		r[v[i]] = n + 1;
	if (n > 1) {
		ranking(win);
	}
	else {
		r[idx] = 1;
	}
}

int main() {
	//freopen("1.txt", "r", stdin);
	int i;
	vector<int> v;
	scanf("%d%d", &NP, &NG);
	W = (int *)malloc(sizeof(int) * NP);
	P = (int *)malloc(sizeof(int) * NP);
	r = (int *)malloc(sizeof(int) * NP);
	for (i = 0; i < NP; i++) {
		scanf("%d", &W[i]);
	}
	for (i = 0; i < NP; i++) {
		scanf("%d", &P[i]);
		v.push_back(P[i]);
	}
	ranking(v);
	printf("%d",r[0]);
	for (i = 1; i < NP; i++) {
		printf(" %d", r[i]);
	}
	//fclose(stdin);
	return 0;
}