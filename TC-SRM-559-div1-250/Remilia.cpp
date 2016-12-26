#include <bits/stdc++.h>

using namespace std;

struct HyperKnight{
	//点在界内
	bool iii(int x, int y, int n, int m){
		return x>=0 && x<n && y>=0 && y<m;
	}
	long long countCells(int a, int b, int n, int m, int k){
		int dx[8]={a,a,-a,-a,b,b,-b,-b},dy[8]={b,-b,b,-b,a,-a,a,-a},x[6]={0,a,b,n-a,n-b,n},y[6]={0,a,b,m-a,m-b,m};
		sort(x,x+6);
		sort(y,y+6);
		long long ans = 0;
		// 枚举每个块
		for(int i=0;i<5;++i)
		for(int j=0;j<5;++j){
			int tmp=0;
			for(int t=0;t<8;++t)
				tmp+=iii(x[i]+dx[t],y[j]+dy[t],n,m);
			if(tmp==k)
				ans+=1ll*(x[i+1]-x[i])*(y[j+1]-y[j]);
		}
		return ans;
	}
};