#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=555555555;
int c[3001][3001];

class XorBoard {
public:
	int count(int H, int W, int Rcount, int Ccount, int S) {
		c[0][0]=1;
		for(int i=1;i<=3000;++i){//预处理组合数 
			c[i][0]=1;
			for(int j=1;j<=i;++j)if((c[i][j]=c[i-1][j-1]+c[i-1][j])>=mo)c[i][j]-=mo;
		}
		LL ret=0;
		for(int x=0;x<=W&&x<=Ccount;++x)//多少个奇数列 
		if((Ccount-x)%2==0){
			LL t1=LL(c[W][x])*c[W+(Ccount-x)/2-1][W-1]%mo;
			for(int y=0;y<=H&&y<=Rcount;++y)//多少个偶数列 
			if((Rcount-y)%2==0&&H*x+W*y-2*x*y==S)//恰好为S 
				ret=(ret+LL(c[H][y])*c[H+(Rcount-y)/2-1][H-1]%mo*t1)%mo;//用组合数算答案 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
