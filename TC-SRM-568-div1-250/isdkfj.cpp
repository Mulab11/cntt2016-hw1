#include <bits/stdc++.h>

using namespace std;

int f[55][8];
inline void gmin(int&x,int y){
	if(x>y)x=y;
}

class BallsSeparating {
public:
	int minOperations(vector <int> red, vector <int> green, vector <int> blue) {
		int n=red.size();
		memset(f,0x3f,sizeof f);
		f[0][0]=0;//初始化 
		for(int i=0;i<n;++i)
			for(int j=0;j<8;++j){
				gmin(f[i+1][j|1],f[i][j]+green[i]+blue[i]);//留红的 
				gmin(f[i+1][j|2],f[i][j]+red[i]+blue[i]);//留绿的 
				gmin(f[i+1][j|4],f[i][j]+red[i]+green[i]);//蓝的 
			}
		return f[n][7]==0x3f3f3f3f?-1:f[n][7];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
