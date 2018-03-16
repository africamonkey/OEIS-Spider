#include <bits/stdc++.h>

#define N 1000020

using namespace std;

char s[N], s2[N];
vector< string > tmp;

struct data {
	string id;
	vector< string > seq;
	vector< string > prefix;
	vector< string > suffix;
	string formula;
	string description;
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
	for (int i = 0; i < (int)s.length() - 7; ++i)
		if (s[i] == 'A' && isdigit(s[i + 1]) && isdigit(s[i + 2]) &&
			isdigit(s[i + 3]) && isdigit(s[i + 4]) && isdigit(s[i + 5]) &&
			isdigit(s[i + 6]) && s[i + 7] == '(')
			return 0;
	return 1;
}

const string d[12] = {(string)"Jan", (string)"Feb", (string)"Mar", (string)"Apr", (string)"May", (string)"Jun", (string)"Jul", (string)"Aug", (string)"Sep", (string)"Oct", (string)"Nov", (string)"Dec"};

string remove_date(string x) {
	for (int i = 0; i < 12; ++i)
		if (x.find(d[i]) != string::npos) {
			int t = x.find(d[i]);
			for (int j = t; j >= 2; --j)
				if (x[j] == '-' && x[j - 1] == ' ' && x[j - 2] == '.') {
					return x.substr(0, j);
				}
		}
	return x;
}

bool not_sim(string x) {
	if (x.size() >= 6 && x[0] == 'a' && x[1] == '(' && x[2] == 'n' && x[3] == ')' && x[4] == ' ' && x[5] == '~') return 0;
	if (x.size() >= 5 && x[0] == 'a' && x[1] == '(' && x[2] == 'n' && x[3] == ')' && x[4] == '~') return 0;
	return 1;
}

string trim(string s) {
	if (s.empty()) return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(0, s.find_first_not_of("\n"));
	s.erase(s.find_last_not_of(" ") + 1);
	s.erase(s.find_last_not_of("\n") + 1);
	return s;
}

void solve(const char *file_name) {
	freopen(file_name, "r", stdin);
	char w;
	while ((w = getchar()) != EOF) {
		while (!isdigit(w)) w = getchar();
		while (isdigit(w)) w = getchar();
		assert(w == ',');
		w = getchar();
		assert(w == '"' || w == ',');
		int top = 0, top2 = 0;
		if (w == '"') {
			w = getchar();
			while (w <= 32) w = getchar();
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
						s[top++] = 0;
						break;
					}
				}
			}
		}
		assert(w == ',');
		w = getchar();
		assert(w == '"');

		w = getchar();
		while (w <= 32) w = getchar();
		s2[top2++] = '\n';
		while (1) {
			if (w == '\n') {
				s2[top2++] = w;
			}
			if (w != '"') {
				s2[top2++] = w;
				w = getchar();
			} else {
				w = getchar();
				if (w == '"') {
					s2[top2++] = w;
					w = getchar();
					continue;
				} else {
					s2[top2++] = 0;
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
		t.description = s2;
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
					// tf = remove_date(tf);
					tf += '\n';
					tf += '\n';
					if (no_a_check(tf) && not_sim(tf)) {
						t.formula += tf;
						++ T;
					}
				}
			}
		int cf = 0;
		for (int i = 0; i < (int)tmp.size() - 1; ++i)
			if (tmp[i] == tmp[i + 1])
				++ cf;
		if (trim(t.formula) != string("") && cf < (int)tmp.size() / 2 && (t.seq.size() < 20 || t.seq[19].length() <= 20)) {
			int ok = 1;
			int k = min(20, (int)t.seq.size());
			for (int j = 0; j < k; ++j)
				if (t.seq[j].length() > 20) ok = 0;
			if (ok) {
				t.seq.resize(min(25, (int)t.seq.size()));
				whole.push_back(t);
			}
		}
	}
}

bool valid(char c) {
	if (c == '#' || c == '$' || c == '%' || c == '{' || c == '}' || c == '~' || c == '^' || c == '_' || c == '&') return 0;
	if (c == '+' || c == '-' || c == '*' || c == '/') return 0;
	if (c == ' ') return 0;
	if (c == '\n') return 0;
	if (c == '\\' || c == '~' || c == '^') return 0;
	return 1;
}

int main() {
//	solve("result_0_85000.csv");
//	solve("result_85000_97000.csv");
//	solve("result_97000_109000.csv");
//	solve("result_109000_121000.csv");
//	solve("result_121000_133000.csv");
//	solve("result_133000_145000.csv");
//	solve("result_145000_156000.csv");
//	solve("result_156000_167000.csv");
//	solve("result_167000_178000.csv");
//	solve("result_178000_186120.csv");
//	solve("result_manual.csv");
	solve("result.csv");

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
//	for (int i = 0; i < (int) 10; ++i) {
	for (int i = 0; i < (int) whole.size(); ++i) {
		//puts("\\begin{sloppypar}");
		printf("\\textbf{[%s]} $\\bullet$ ", whole[i].id.c_str());

		for (int j = 0; j < (int) whole[i].prefix.size(); ++j) {
			printf("\\seqsplit{%s},", whole[i].prefix[j].c_str());
		}
		printf("\\underline{");
		if (whole[i].suffix.size() > 0)
			printf("%s", whole[i].suffix[0].c_str());
		printf("}");
		for (int j = 1; j < (int) whole[i].suffix.size(); ++j)
			printf(",\\seqsplit{%s}", whole[i].suffix[j].c_str());
		//	printf(", \\underline{%s}", whole[i].suffix[j].c_str());
		printf(" $\\star$ ");
		for (int j = 0; j < whole[i].description.length(); ++j) {
			char c = whole[i].description[j];
			if (c == '\n' && j + 1 < whole[i].description.length() && whole[i].description[j + 1] == '\n') {
				printf(" $\\bullet$ ");
				++ j;
				continue;
			}
			if (c == '#' || c == '$' || c == '%' || c == '{' || c == '}' || c == '~' || c == '^' || c == '_' || c == '&')
				putchar('\\');
			if (c != '\\')
				putchar(c);
			else
				printf("$\\backslash$");
			if (c == '~' || c == '^')
				printf("{}");
		}
		bool is_ok = 0;
		for (int j = 0; j < whole[i].formula.length(); ++j) {
			char c = whole[i].formula[j];
			if (valid(c) && !is_ok) {
				printf(" \\seqsplit{");
			}
			if (!valid(c) && is_ok) {
				printf("} ");
			}
			is_ok = valid(c);
			if (c == '\n' && j + 1 < whole[i].formula.length() && whole[i].formula[j + 1] == '\n') {
				printf(" $\\bullet$ ");
				++ j;
				continue;
			}
			if (c == '#' || c == '$' || c == '%' || c == '{' || c == '}' || c == '~' || c == '^' || c == '_' || c == '&')
				putchar('\\');
			if (c != '\\')
				putchar(c);
			else
				printf("$\\backslash$");
			if (c == '~' || c == '^')
				printf("{}");
		}
		puts("");
		puts("");
		//puts("\\end{sloppypar}");
	}
	return 0;
}
