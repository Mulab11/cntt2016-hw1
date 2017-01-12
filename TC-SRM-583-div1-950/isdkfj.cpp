#include <bits/stdc++.h>

using namespace std;

const int maxT=1500;
int n,m,T,p[30][30],s1[30],s2[30],cnt[maxT],f[30][maxT][2];

class RandomPaintingOnABoard {
public:
	double expectedSteps(vector <string> prob) {
		n=prob.size();m=prob[0].size();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)T+=(p[i][j]=prob[i-1][j-1]-48);//求出总和 
		if(n>m){//把较小的那维变成行 
			for(int i=1;i<=n;++i)
				for(int j=1;j<i;++j)
				swap(p[i][j],p[j][i]);
			swap(n,m);
		}
		for(int i=1;i<=m;++i)
			for(int j=1;j<=n;++j)
			s1[i]+=p[j][i];
		for(int s=0;s<1<<n;++s){//不取哪些行 
			for(int i=1;i<=m;++i){
				s2[i]=0;
				for(int j=1;j<=n;++j)
				if(s&(1<<j-1))s2[i]+=p[j][i];
			}
			for(int i=0;i<=m;++i)
				for(int j=0;j<=T;++j)
				f[i][j][0]=f[i][j][1]=0;
			f[0][0][0]=1;//初始化 
			for(int i=1;i<=m;++i)
				for(int j=0;j<=T;++j)
					for(int k=0;k<2;++k){
						if(j>=s1[i])f[i][j][k]+=f[i-1][j-s1[i]][k^1];//选
						if(j>=s2[i])f[i][j][k]+=f[i-1][j-s2[i]][k];//不选 
					}
			int flag=0;
			for(int i=1;i<=n;++i)if(s&(1<<i-1))flag^=1;//容斥的系数 
			if(flag) for(int i=0;i<=T;++i)cnt[i]+=f[m][i][0]-f[m][i][1];
			else for(int i=0;i<=T;++i)cnt[i]+=f[m][i][1]-f[m][i][0];
		}
		double ans=1;
		for(int i=1;i<=T;++i)ans+=cnt[i]*((double)T/i-1);//统计答案 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
