#include <bits/stdc++.h>

using namespace std;

double pr[55],pp[55],ps[55],f[51][51][51][51];
int n;

class RockPaperScissors {
public:
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb) {
		n=rockProb.size();
		for(int i=0;i<n;++i)pr[i]=rockProb[i]/300.0,pp[i]=paperProb[i]/300.0,ps[i]=scissorsProb[i]/300.0;
		for(int i=0;i<n;++i)f[i][0][0][0]=1;//初始化 
		for(int i=1;i<=n;++i)
			for(int j=0;j<n;++j)
				for(int m=i;m>=0;--m)
					for(int r=0;r<=m;++r)
						for(int p=0;r+p<=m;++p){
							int s=m-r-p;
							double tmp=1.*m/i;
							if(j==i-1)f[j][r][p][s]*=1-tmp;//不扔这个骰子 
							else {
								double orz=0;
								if(r)orz+=pr[i-1]*f[j][r-1][p][s];
								if(p)orz+=pp[i-1]*f[j][r][p-1][s];
								if(s)orz+=ps[i-1]*f[j][r][p][s-1];
								//扔i-1为r,p,s的概率乘上对应的前继状态 
								f[j][r][p][s]=f[j][r][p][s]*(1-tmp)+tmp*orz;
							}
						}
		double ans=0;
		for(int r=0;r<n;++r)
			for(int p=0;r+p<n;++p)
				for(int s=0;r+p+s<n;++s){//枚举所有局面 
					double xr=0,xp=0,xs=0;
					for(int i=0;i<n;++i){
						double tmp=f[i][r][p][s]/(n-r-p-s);
						xr+=tmp*pr[i];
						xp+=tmp*pp[i];
						xs+=tmp*ps[i];//当前局面下扔出每种的概率
						//P(A|B)=P(AB)/P(B)
					}
					double tmp=0;
					tmp=max(tmp,3*xs+xr);
					tmp=max(tmp,3*xr+xp);
					tmp=max(tmp,3*xp+xs);//选择最优的决策 
					ans+=tmp;
				}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
