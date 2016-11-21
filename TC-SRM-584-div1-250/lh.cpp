#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class Egalitarianism{
	private:
		static const int inf=1000000000;
		int mp[60][60];
	public:
		int maxDifference(vector <string> rec, int d){
			int n=rec.size();
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) mp[i][j]=(i==j)?0:((rec[i][j]=='Y')?1:inf);
			for (int k=0;k<n;++k)
			for (int i=0;i<n;++i) if (i!=k)
			for (int j=0;j<n;++j) if (j!=i&&j!=k) mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
			int mx=0;
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) mx=max(mx,mp[i][j]);
			if (mx>=inf) return -1;
			return mx*d;
		}
};
