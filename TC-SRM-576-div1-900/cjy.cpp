#include<bits/stdc++.h>
#define LL long long 
using namespace std;
int P=1e9+9,i,j,n,m,f;
LL x,k,s;
set<LL> D;
map<LL,char> T;
LL Pow(LL x,int y){LL r=1;for(;y;x=x*x%P,y>>=1)if(y&1)r=r*x%P;return r;} 
class CharacterBoard
{
	public:
		int countGenerators(vector<string> a,LL W,int _,int __)//对序列长度讨论
		{
			for(n=a.size(),m=a[0].size();i<n;i++)for(j=1-m;j<m;j++)for(x=W*i+j,k=1;k*k<=x;k++)if(x%k==0)D.insert(k),D.insert(x/k);
			if(W>=n*m)s=(Pow(26,W-n*m+1)+P-1)*Pow(25,P-2)%P;
			for(auto d : D)if(d<=W)
			{
				for(T.clear(),f=1,i=0;i<n;i++)for(j=0;j<m;j++)if(T.find(x=(W*i+j)%d)==T.end())T[x]=a[i][j];else f&=T[x]==a[i][j];
				if(s=(s+Pow(26,d-T.size())*f)%P,d>=n*m)s=(s+P-Pow(26,d-n*m))%P;
			}
			return s;
		}
};
