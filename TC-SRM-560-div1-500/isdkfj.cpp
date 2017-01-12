#include <bits/stdc++.h>

using namespace std;


class DrawingPointsDivOne {
public:
	int maxSteps(vector <int> x, vector <int> y) {
		int l=0,r=150,mid; static int f[300][300];
		while(l<r){
			mid=(l+r+1)>>1;
			memset(f,0,sizeof f);
			for(int i=0;i<x.size();++i){
				++f[x[i]+75][y[i]+75];
				++f[x[i]+76+mid][y[i]+76+mid];
				--f[x[i]+75][y[i]+76+mid];
				--f[x[i]+76+mid][y[i]+75];//插入一个正方形 
			}
			for(int i=1;i<300;++i)
				for(int j=1;j<300;++j)f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
			//前缀和 
			int cnt=0;
			for(int i=298;i>=0;--i)
				for(int j=298;j>=0;--j)
				if(f[i][j]){
					f[i][j]=min(f[i+1][j+1],min(f[i+1][j],f[i][j+1]))+1;
					//dp求向右上方扩展的正方形边长 
					if(f[i][j]>mid)++cnt;
				}
			if(cnt==x.size())l=mid;//是否有多余的点 
			else r=mid-1;
		}
		if(l==150)return -1;
		return l;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
