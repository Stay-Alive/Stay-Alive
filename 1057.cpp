#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define Push 0
#define Pop 1
#define Peek 2
int N, cnt[100001];

int main() {
	//freopen("1.txt", "r", stdin);
	int i, j = 0, key, med = 0;
	char cmd[11], *s[3] = { "Push", "Pop", "PeekMedian" };
	vector<int> v;
	scanf("%d", &N);
	memset(cnt, 0, 100001 * sizeof(int));
	for (i = 0; i < N; i++) {
		scanf("%s", cmd);
		if (!strcmp(cmd, s[Push])) {
			scanf("%d", &key);
			v.push_back(key);
			cnt[key]++;
			if (key <= j)
				med++;
		}
		else if (!strcmp(cmd, s[Pop])) {
			if (v.empty()) {
				printf("Invalid\n");
				j = 0;
				med = 0;
			}
			else {
				key = v.back();
				printf("%d\n", key);
				cnt[key]--;
				v.pop_back();
				if (key <= j)
					med--;
			}
		}
		else if (!strcmp(cmd, s[Peek])) {
			if (v.empty())
				printf("Invalid\n");
			else {
				while (j < 100001) {
					if (med < (v.size() + 1) / 2) {
						j++;
						med += cnt[j];
						if (med >= (v.size() + 1) / 2)
							break;
					}
					else if (med >(v.size() + 1) / 2) {
						med -= cnt[j];
						j--;
					}
					else {
						while (cnt[j] == 0) j--;
						break;
					}
				}
				key = j;
				printf("%d\n", key);
			}
		}
	}
	//fclose(stdin);
	return 0;
}