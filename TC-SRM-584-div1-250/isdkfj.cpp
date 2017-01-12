#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int f[55][55];

class Egalitarianism {
public:
	int maxDifference(vector <string> isFriend, int d) {
		int n=isFriend.size();
		memset(f,0x3f,sizeof f);
		for(int i=0;i<n;++i)f[i][i]=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)if(isFriend[i][j]=='Y')f[i][j]=1;
		for(int k=0;k<n;++k)
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//floyd
		int ans=0;
		for(int i=0;i<n;++i){
			int mx=0;
			for(int j=0;j<n;++j)mx=max(mx,f[i][j]);//最长的最短路 
			if(mx==inf)return -1;//不可达 
			ans=max(ans,mx);
		}
		return ans*d;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
