#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int f[55][55];

class ColorfulWolves {
public:
	int getmin(vector <string> colormap) {
		int n=colormap.size();
		for(int i=0;i<n;++i){
			int cnt=0;
			for(int j=0;j<n;++j)
			if(colormap[i][j]=='Y')f[i][j]=cnt++;//建图 
			else f[i][j]=inf;
		}
		for(int k=0;k<n;++k)//弗洛伊德算法求最短路 
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		return f[0][n-1]>=inf?-1:f[0][n-1];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
