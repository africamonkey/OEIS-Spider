#include <bits/stdc++.h>

#define N 2000020

using namespace std;

char id[20], st[N], lastans[N], ans[N];

bool cmp(char *x, char *y) {
	int lenx = strlen(x), leny = strlen(y);
	if (lenx != leny) return lenx < leny;
	return strcmp(x, y) <= 0;
}

int main() {
	freopen("stripped", "r", stdin);
	freopen("verified", "w", stdout);
	while (~scanf("%s", id)) {
		fgets(st, N - 1, stdin);
		int len = strlen(st);
		int t = 0;
		while (!isdigit(st[t])) ++ t;
		lastans[0] = '0';
		lastans[1] = 0;
		int top = 0;
		int ok = 1;
		int test = 0;
		for (int i = t; i < len; ++i) {
			if (st[i] == ',') {
				ans[top++] = 0;
				++ test;
				if (!cmp(lastans, ans)) {
					ok = 0;
					break;
				}
				strcpy(lastans, ans);
				top = 0;
			} else
			if (isdigit(st[i])) {
				ans[top++] = st[i];
			} else
			if (st[i] == '-') {
				ok = 0;
				break;
			}
		}
		if (ok && test > 1) {
			printf("%s\n", id);
		}
	}
}