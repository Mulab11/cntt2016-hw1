#include <bits/stdc++.h> 

using namespace std;

int n, m;

const int MAXN = 300010 ; 

typedef long long  LL ; 

struct Point {
		int x, y;
		Point(int a = 0 , int b = 0 ) {x = a, y = b; }
		Point operator - (const Point &_ano) const {
				return Point(x - _ano.x, y - _ano.y);
		}
		LL operator * (const Point &_ano) const {
				return 1LL * x * _ano.y - 1LL * y * _ano.x;
		}
} usd[MAXN], ano[50];

LL S[MAXN];

int q[MAXN] ;

bool check(Point a, Point b) { 
		for(int i = 0; i < m; i++) 
				if((b - a) * (i[ano] - a) > 0)
						return 0;
		return 1;
}
class EnclosingTriangle {
		public:
				LL getNumber(int M, vector<int> x, vector<int> y) {
						m = M;
						for(int i = 0; i < m; i++) (n ++)[usd] = Point(0, i);
						for(int i = 0; i < m; i++) (n ++)[usd] = Point(i, m);
						for(int i = 0; i < m; i++) (n ++)[usd] = Point(m, m - i);
						for(int i = 0; i < m; i++) (n ++)[usd] = Point(m - i, 0);
						m = x.size();
						for(int i = 0; i < m; i++) ano[i] = Point(x[i], y[i]);
						LL ans = 0;
						int l = 0, r = 1 ;  
						for(int i = 0, j = 0, k = 1; i < n; i ++) {
								while(k < n && !check(k[usd], usd[i])) k++;
								while(j < n && check(usd[i], usd[j])) {
										for (r[q] = (r - 1)[q]; r[q] < n && check(j[usd], r[q][usd]); r[q] ++);
										S[r] = S[r - 1] + r[q] ;  
										r = r + 1 ; 
										j = j + 1 ;  
								}
								while(l < r && k >= l[q]) l++;
								if (i + 2 > l) l = i + 2 ;  
								ans += S[r - 1] - S[l - 1] - (LL)k * (r - l); 
								if(r - 1 == k + 1) ans--;
						}
						return ans;
				}
} sol ;


