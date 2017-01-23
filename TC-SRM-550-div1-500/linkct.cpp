#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
typedef long long int LL;
const int c[2][2] = {{1, 0}, {1, 1}};
//1 0 0 4 4
class CheckerExpansion{
	public:
		LL t;
		int C(LL n, LL m){ //Lucas theorem
			if(n <= 1 && m <= 1) return c[n][m];
			return C(n >> 1, m >> 1) * c[n & 1][m & 1];
		}
		char getChar(LL x, LL y){
			if((x ^ y) & 1LL) return '.';
			if(y > x) return '.';
			if(((x + y) >> 1LL) >= t) return '.';
			if((C((x + y) >> 1LL, y) & 1) == 0) return '.';
			return 'A' + (((x + y) >> 1LL) & 1LL);
		}
		vector <string> resultAfter(LL turn, LL x0, LL y0, int w, int h){
			t = turn;
			vector <string> ret; string cur; int i, j;
			for(i = 0; i < h; ++ i){ //Pascal's triangle
				cur = "";
				for(j = 0; j < w; ++ j)
					cur += getChar(x0 + j, y0 + h - i - 1);
				ret.push_back(cur);
			} return ret;
		}
};
