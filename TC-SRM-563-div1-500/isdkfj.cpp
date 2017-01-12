#include <bits/stdc++.h>

using namespace std;

int a[105],b[105],f[105][55];

class SpellCards {
public:
	int maxDamage(vector <int> level, vector <int> damage) {
		int n=level.size();
		for(int i=0;i<n;++i){
			a[i+1]=a[i+1+n]=level[i];
			b[i+1]=b[i+1+n]=damage[i];
		}
		int ans=0;
		for(int st=1;st<=n;++st){//枚举起点 
			int en=st+n-1;//终点 
			for(int i=st;i<=en+1;++i)
				for(int j=0;j<=n;++j)f[i][j]=-999999999;//初始化 
			f[en+1][0]=0;
			for(int i=en;i>=st;--i)
				for(int j=0;i+j-1<=en;++j){
					if(j)f[i][j]=f[i+1][j-1];//不用 
					if(j+a[i]-1<=n)f[i][j]=max(f[i][j],f[i+1][j+a[i]-1]+b[i]);//用 
					ans=max(ans,f[i][j]);
				}
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
