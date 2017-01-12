#include <bits/stdc++.h>

using namespace std;

char mp[105][105];
int dr,dg,db;

class PastingPaintingDivOne {
public:
	vector<long long> countColors(vector <string> clipboard, int T) {
		for(int i=1;i<105;++i)
			for(int j=1;j<105;++j)mp[i][j]='.';//全部清空 
		int n=clipboard.size(),m=clipboard[0].size();
		vector<long long>ret;
		ret.push_back(0);
		ret.push_back(0);
		ret.push_back(0);
		for(int i=1;i<=n&&i<=m;++i){
			if(T==0)break;
			--T;
			dr=dg=db=0;
			for(int j=i;j<=n+i-1;++j)
				for(int k=i;k<=m+i-1;++k){
					char ne=clipboard[j-i][k-i];
					if(ne=='.')continue;
					if(ne=='R')++dr;//多出来的 
					if(ne=='G')++dg;
					if(ne=='B')++db;
					if(mp[j][k]=='R')--dr;//扣掉原来的 
					if(mp[j][k]=='G')--dg;
					if(mp[j][k]=='B')--db;
					mp[j][k]=ne;
				}
			ret[0]+=dr;ret[1]+=dg;ret[2]+=db;//累加 
		}
		if(!T)return ret;
		ret[0]+=1ll*dr*T;//后面好多次都一样 
		ret[1]+=1ll*dg*T;
		ret[2]+=1ll*db*T;
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
