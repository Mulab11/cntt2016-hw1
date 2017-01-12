#include <bits/stdc++.h>

using namespace std;

const int mo=1000000009;
typedef long long LL;
LL ksm(LL x,int k){//快速幂 
	LL t=1;
	for(;k;k>>=1,x=x*x%mo)if(k&1)t=t*x%mo;
	return t;
}

char mp[55][55];
int ys[555555],tot;

int splay(int i0,int j0,int W,int len,int n,int m){//求可以乱填的方案数 
	map<int,char>check;
	for(int x=i0;x<i0+n;++x)
		for(int y=j0;y<j0+m;++y){
			int i=(1ll*x*W+y)%len;
			if(check.find(i)!=check.end()){
				if(mp[x-i0][y-j0]!=check[i])return 0;
			} else check[i]=mp[x-i0][y-j0];
		}
	return ksm(26,len-check.size());
	
}

class CharacterBoard {
public:
	int countGenerators(vector <string> fragment, int W, int i0, int j0) {
		int n=fragment.size(),m=fragment[0].size();
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)mp[i][j]=fragment[i][j];
		map<LL,bool>sss;
		for(int x1=i0;x1<i0+n;++x1)
			for(int y1=j0;y1<j0+m;++y1)
				for(int x2=i0;x2<i0+n;++x2)
					for(int y2=j0;y2<j0+m;++y2){
						LL i=1ll*x1*W+y1,j=1ll*x2*W+y2;
						LL tmp=abs(i-j);
						if(i>j)continue;
						if(sss.count(tmp))continue;//优化，同样的数不用再分解 
						sss[tmp]=1;
						for(LL k=1;k*k<=tmp;++k)
						if(tmp%k==0){
							if(k<=W)ys[++tot]=k;
							if(tmp/k<=W)ys[++tot]=tmp/k;//因数都是可能重复的 
						}
					}
		sort(ys+1,ys+tot+1);
		tot=unique(ys+1,ys+tot+1)-ys-1;
		LL ans=ksm(26,W+1)-26;
		ans=(ans+mo)%mo;
		ans=ans*ksm(25,mo-2)%mo;
		LL xs=ksm(ksm(26,n*m),mo-2);
		ans=ans*xs%mo;//等差数列求和 
		for(int i=1;i<=tot;++i){
			int len=ys[i];
			ans=ans-ksm(26,len)*xs%mo;//先扣掉 
			ans=(ans+mo)%mo;
			ans=(ans+splay(i0,j0,W,len,n,m))%mo;//再加上 
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
