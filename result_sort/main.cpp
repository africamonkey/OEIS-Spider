#include <bits/stdc++.h>

#define N 1000020

using namespace std;

char s[N];
vector< string > tmp;

struct data {
	string id;
	vector< string > seq;
	vector< string > prefix;
	vector< string > suffix;
	string formula;
} t;

vector< data > whole;

bool cmp(const data &x, const data &y) {
	int x_size = x.suffix.size(), y_size = y.suffix.size();
	int size = min(x_size, y_size);
	for (int i = 0; i < size; ++i)
		if (x.suffix[i].length() != y.suffix[i].length())
			return x.suffix[i].length() < y.suffix[i].length();
		else
			if (x.suffix[i] != y.suffix[i])
				return x.suffix[i] < y.suffix[i];
	if (x_size != y_size) return x_size < y_size;
	return x.id < y.id;
}

bool cmp2(const data &x, const data &y) {
	int x_size = x.seq.size(), y_size = y.seq.size();
	if (x_size != y_size) return 0;
	for (int i = 0; i < x_size; ++i)
		if (x.seq[i] != y.seq[i])
			return 0;
	return 1;
}

bool no_a_check(string s) {
	for (int i = 0; i < (int)s.length() - 6; ++i)
		if (s[i] == 'A' && isdigit(s[i + 1]) && isdigit(s[i + 2]) &&
			isdigit(s[i + 3]) && isdigit(s[i + 4]) && isdigit(s[i + 5]) &&
			isdigit(s[i + 6]))
			return 0;
	return 1;
}

void solve(const char *file_name) {
	freopen(file_name, "r", stdin);
	char w;
	while ((w = getchar()) != EOF) {
		while (!isdigit(w)) w = getchar();
		while (isdigit(w)) w = getchar();
		assert(w == ',');
		w = getchar();
		assert(w == '"');
		w = getchar();
		while (w <= 32) w = getchar();
		int top = 0;
		s[top++] = '\n';
		while (1) {
			if (w == '\n') {
				s[top++] = w;
			}
			if (w != '"') {
				s[top++] = w;
				w = getchar();
			} else {
				w = getchar();
				if (w == '"') {
					s[top++] = w;
					w = getchar();
					continue;
				} else {
					break;
				}
			}
		}
		assert(w == ',');
		w = getchar();
		assert(w == '"');
		while (!isdigit(w)) w = getchar();
		tmp.clear();
		while (1) {
			string s = "";
			while (isdigit(w)) {
				s += w;
				w = getchar();
			}
			tmp.push_back(s);
			int ok = 1;
			while (!isdigit(w)) {
				if (w == '"') {
					ok = 0;
					w = getchar();
					break;
				}
				w = getchar();
			}
			if (ok == 0) break;
		}
		assert(w == ',');
		w = getchar();
		assert(w == 'A');
		w = getchar();
		string id = "A";
		for (int i = 0; i < 6; ++i) {
			id += w;
			w = getchar();
		}
		fprintf(stderr, "%s\n", id.c_str());
		t.id = id;
		t.seq = tmp;
		t.formula = "";
		t.prefix.clear();
		t.suffix.clear();
		int T = 0;
		for (int j = 0; j < top; ++j)
			if (s[j] == '\n') {
				if (s[j + 1] == 'a' && s[j + 2] == '(' && T < 6) {
					int k;
					string tf = "";
					for (k = j + 1; k < top && s[k] != '\n'; ++k)
						tf += s[k];
					j = k;
					tf += '\n';
					tf += '\n';
					if (no_a_check(tf)) {
						t.formula += tf;
						++ T;
					}
				}
			}
		int cf = 0;
		for (int i = 0; i < (int)tmp.size() - 1; ++i)
			if (tmp[i] == tmp[i + 1])
				++ cf;
		if (t.formula != string("") && cf < (int)tmp.size() / 2 && tmp.size() > 20)
			whole.push_back(t);
	}
}

int main() {
	solve("result_0_85000.csv");
	solve("result_85000_97000.csv");
	solve("result_97000_109000.csv");
	solve("result_109000_121000.csv");
	solve("result_121000_133000.csv");
	solve("result_133000_145000.csv");
	solve("result_145000_156000.csv");
	solve("result_156000_167000.csv");
	solve("result_167000_178000.csv");
	solve("result_178000_186120.csv");
	solve("result_manual.csv");

	for (int i = 0; i < (int) whole.size(); ++i)
		for (auto j : whole[i].seq)
			if (j == string("0") || j == string("1")) {
				whole[i].prefix.push_back(j);
			} else {
				whole[i].suffix.push_back(j);
			}
	sort(whole.begin(), whole.end(), cmp);
	whole.erase(unique(whole.begin(), whole.end(), cmp2), whole.end());
	freopen("tex.txt", "w", stdout);
	// whole.erase(whole.begin() + 3, whole.end());
	for (int i = 0; i < (int) whole.size(); ++i) {
		printf("\\textbf{[%s]}\n", whole[i].id.c_str());
		printf("\\texttt{");
		for (int j = 0; j < (int) whole[i].prefix.size(); ++j)
			printf("%s, ", whole[i].prefix[j].c_str());
		printf("\\underline{");
		if (whole[i].suffix.size() > 0)
			printf("%s", whole[i].suffix[0].c_str());
		printf("}");
		for (int j = 1; j < (int) whole[i].suffix.size(); ++j)
			printf(", \\underline{%s}", whole[i].suffix[j].c_str());
		printf("}");
		puts("");
		puts("");
		for (int j = 0; j < whole[i].formula.length(); ++j) {
			char c = whole[i].formula[j];
			if (c == '#' || c == '$' || c == '%' || c == '{' || c == '}' || c == '~' || c == '^' || c == '_')
				putchar('\\');
			if (c != '\\')
				putchar(c);
			else
				printf("$\\backslasb$");
			if (c == '~' || c == '^')
				printf("{}");
		}
	}
	return 0;
}
