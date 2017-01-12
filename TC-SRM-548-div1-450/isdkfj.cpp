#include <bits/stdc++.h>

using namespace std;

bool f[2505][55];
int tt[55];

class KingdomAndDice {
public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X) {
		int n=firstDie.size(),m=0,s=0;
		vector <int> fd=firstDie,sd=secondDie;
		for(int i=0;i<n;++i){
			m+=fd[i]==0;
			for(int j=0;j<n;++j)s+=fd[i]>sd[j];//求出初始的概率 
		}
		sort(sd.begin(),sd.end());
		sd.push_back(X+1);//方便处理 
		for(int i=0;i<n;++i){
			tt[i]=sd[i+1]-sd[i]-1;
			for(int j=0;j<n;++j)
				if(sd[i]<fd[j]&&fd[j]<sd[i+1])--tt[i];
			//求出每个区间可以填的数的个数 
		}
		for(int k=0;k<=m;++k)f[0][k]=1;//初始化 
		for(int i=0;i<n;++i)
			for(int j=n*m;j>=0;--j)
				for(int k=m;k>=0;--k)
				if(f[j][k])
					for(int l=1;l<=tt[i]&&l+k<=m;++l)
						f[j+l*(i+1)][k+l]=1;//DP
		double ret=1.0*s/(n*n);
		int ans=s;
		for(int t=0;t<=n*m;++t)
			if(f[t][m])
				if(abs(n*n-2*(s+t))<abs(n*n-2*ans))ret=1.0*(s+t)/(n*n),ans=s+t;
				//用整数判断避免精度误差 
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
