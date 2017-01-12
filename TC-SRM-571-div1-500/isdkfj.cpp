#include <bits/stdc++.h>

using namespace std;

int n,lim,g[55][55],ans,v[55],f[55];

void dfs(int x,int y,int z,int sum){
	if(sum<ans||z<lim)return;
	if(x==n-1)ans=sum;//搜完了 
	else if(y==n)dfs(x+1,x+2,z,sum);//一行搜完了 
	else {
		if(g[x][y]||v[x]||v[y])dfs(x,y+1,z,sum);//有边或者有的删掉了 
		else {
			v[x]=1;dfs(x,y+1,z-1,sum-f[x]);v[x]=0;
			v[y]=1;dfs(x,y+1,z-1,sum-f[y]);v[y]=0;
		}
	}
}

class MagicMolecule {
public:
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond) {
		n=magicPower.size();
		while(3*lim<2*n)++lim;//最低限制 
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)g[i][j]=magicBond[i][j]=='Y';
		ans=-1;
		memset(v,0,sizeof v);
		int sum=0;
		for(int i=0;i<n;++i)sum+=(f[i]=magicPower[i]);
		dfs(0,1,n,sum);
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
