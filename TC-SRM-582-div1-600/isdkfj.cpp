#include <bits/stdc++.h>

using namespace std;

const int mo=1000000009;
typedef long long LL;
int f[1300][1300],tot,c[1300],s[1300],s0[1300][1300],fa[1300],rf[1300];
map<string,int>mp;
LL ksm(LL x,int k){
	LL ret=1;
	for(;k;k>>=1,x=x*x%mo)if(k&1)ret=ret*x%mo;
	return ret;
}

class ColorfulBuilding {
public:
	int count(vector <string> color1, vector <string> color2, int L) {
		int n;
		string c1,c2;
		for(int i=0;i<color1.size();++i)c1+=color1[i];
		for(int i=0;i<color2.size();++i)c2+=color2[i];
		n=c1.size();
		for(int i=0;i<n;++i){
			string tmp;
			tmp+=c1[i];tmp+=c2[i];
			if(!mp.count(tmp))mp[tmp]=++tot;
			c[i+1]=mp[tmp];//求出每个位置的颜色 
		}
		fa[0]=1;for(int i=1;i<1300;++i)fa[i]=LL(fa[i-1])*i%mo;//预处理阶乘 
		rf[1299]=ksm(fa[1299],mo-2);
		for(int i=1298;i>=0;--i)rf[i]=LL(rf[i+1])*(i+1)%mo;//预处理阶乘逆元 
		f[n][1]=1;s[1]=rf[0];s0[c[n]][1]=rf[0];//初始化 
		for(int i=n-1;i>=0;--i)
			for(int j=L+1;j>=1;--j){
				f[i][j]=s[j-1]-s0[c[i]][j-1]+s0[c[i]][j];//同颜色不变，不同颜色+1 
				if(f[i][j]>=mo)f[i][j]-=mo;
				if(f[i][j]<0)f[i][j]+=mo;
				f[i][j]=LL(f[i][j])*fa[n-i-1]%mo;//乘以组合数的阶乘 
				s[j]=(s[j]+LL(f[i][j])*rf[n-i])%mo;//求出除以逆元之后的和 
				s0[c[i]][j]=(s0[c[i]][j]+LL(f[i][j])*rf[n-i])%mo;
			}
		return f[0][L+1];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
