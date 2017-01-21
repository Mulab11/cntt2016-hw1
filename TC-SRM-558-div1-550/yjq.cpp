#include <bits/stdc++.h>

using namespace std;

int n, m ;

const int MAXN = 310 ; 

int r[MAXN], b[MAXN], h[MAXN], cnt[MAXN * MAXN] ; 

typedef long long LL ; 

void Parse(const vector<string> &vec, int *a, int &cnt) {
		string str;
		for(int i = 0; i < vec.size(); i++)
				str += vec[i];
		for(int i = 0; i < str.length(); i++)
		{
				if(str[i] == ' ')
						cnt++;
				else
						a[cnt] = a[cnt] * 10 + (str[i] - '0');
		}
		cnt++;
}

LL Calc(int p, int q) {
		return (p - q + p - 1) * q / 2;
}
int getS() {return cnt[10000]; }
int getS(int a) {
		if (a < 0) return 0 ;
		return cnt[min(a, 10000) ] ;
}
class Ear {
		public:
				LL getCount(vector<string> r_vec, vector<string> b_vec, vector<string> h_vec)
				{
						Parse(r_vec, r, n);
						Parse(b_vec, b, m);
						Parse(h_vec, h, m = 0);
						for(int i = 0; i < n; i++) cnt[r[i]]++;
						for(int i = 1; i <= 10000; i++) cnt[i] += cnt[i - 1];
						LL ans = 0;
						for(int i = 0; i < m; i++) {
								for(int j = 0; j < m; j++) {
										if(h[i] <= h[j]) continue;
										ans += Calc(getS(b[j] - 1), getS(min(((b[j] - b[i]) * h[i] + b[i] * (h[i] - h[j]) - 1) / (h[i] - h[j]), b[i] - 1))) *
												Calc(getS() - getS(b[j]), getS() - getS(max(((b[j] - b[i]) * h[i] + b[i] * (h[i] - h[j])) / (h[i] - h[j]), b[i])));
								}
						}
						return ans;
				}
};
