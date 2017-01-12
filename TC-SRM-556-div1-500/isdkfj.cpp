#include <bits/stdc++.h>

using namespace std;

inline void gmin(string&x,string y){if(x==""||x>y)x=y;}//比较函数 

class LeftRightDigitsGame2 {
public:
	string minNumber(string digits, string lowerBound) {
		static string f[55][55],g[55][55],h[55];
		int n=digits.size();
		for(int i=0;i<n;++i){//初始化 
			if(digits[0]>lowerBound[i])g[0][i]=digits[0];
			if(digits[0]>=lowerBound[i])f[0][i]=digits[0];
		}
		h[0]=digits[0];
		for(int i=1;i<n;++i)h[i]=min(h[i-1]+digits[i],digits[i]+h[i-1]);
		//预处理前i个字符最小能变成多少 
		for(int i=1;i<n;++i)
			for(int j=0;i+j<n;++j){
				char x=digits[i];
				if(x==lowerBound[j]){//x+...
					if(f[i-1][j+1]!="")gmin(f[i][j],x+f[i-1][j+1]);
					if(g[i-1][j+1]!="")gmin(g[i][j],x+g[i-1][j+1]);
				}
				if(x>lowerBound[j])//x+...
					gmin(f[i][j],x+h[i-1]),
					gmin(g[i][j],x+h[i-1]);
				if(x>=lowerBound[i+j]){if(f[i-1][j]!="")gmin(f[i][j],f[i-1][j]+x);}
				else if(g[i-1][j]!="")gmin(f[i][j],g[i-1][j]+x);//...+x
				if(x>lowerBound[i+j]){if(f[i-1][j]!="")gmin(g[i][j],f[i-1][j]+x);}
				else if(g[i-1][j]!="")gmin(g[i][j],g[i-1][j]+x);//...+x
			}
		return f[n-1][0];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
