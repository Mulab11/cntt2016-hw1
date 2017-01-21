// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorBoard.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define P 555555555

const int maxn=2333;
int _c[maxn+5][maxn+5];
void init_c(){
	memset(_c,0,sizeof(_c));
	for (int i=0;i<=maxn;++i){
		_c[i][0]=1;
		for (int j=1;j<=i;++j)
			_c[i][j]=(_c[i-1][j-1]+_c[i-1][j])%P;
	}
}

class XorBoard {
	public:
	int count(int H, int W, int Rcount, int Ccount, int S){
		init_c();
		int r=H,c=W;
//		S=H*W-S;
		int ret=0;
		for (int x=0;x<=r&&x<=Rcount;++x)for (int y=0;y<=c&&y<=Ccount;++y){
			if (r*y+c*x-2*x*y!=S) continue;
			if (((x^Rcount)&1)||((y^Ccount)&1)) continue;
//			printf("%d %d %d %d\n",r,x,c,y);
//			printf("%d %d %d %d\n",(Rcount-x)/2+r-1,r-1,(Ccount-y)/2+c-1,c-1);
			ret=(1LL*_c[r][x]*_c[c][y]%P*_c[(Rcount-x)/2+r-1][r-1]%P*_c[(Ccount-y)/2+c-1][c-1]+ret)%P;
		}
		return ret;
	}
};
