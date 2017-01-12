#include <bits/stdc++.h>

using namespace std;

const int mo=1000000007;
int f[100005],r[100005];
typedef long long LL;
LL ksm(LL x,int k){//快速幂 
	LL ret=1;
	for(;k;k>>=1,x=x*x%mo)if(k&1)ret=ret*x%mo;
	return ret;
}
LL c(int x,int y){//组合数 
	if(x<y)return 0;
	return LL(f[x])*r[y]%mo*r[x-y]%mo;
}

class WolfPack {
public:
	int calc(vector <int> x, vector <int> y, int m) {
		int n=x.size(),lx=-300000,rx=300000,ly=-300000,ry=300000;
		for(int i=0;i<n;++i){
			x[i]=x[i]+y[i];
			y[i]=x[i]-2*y[i];//(x,y)->(x+y,x-y)
			lx=max(lx,x[i]-m);
			rx=min(rx,x[i]+m);
			ly=max(ly,y[i]-m);
			ry=min(ry,y[i]+m);
		}
		f[0]=1;
		for(int i=1;i<=m;++i)f[i]=f[i-1]*LL(i)%mo;
		r[m]=ksm(f[m],mo-2);
		for(int i=m;i>=1;--i)r[i-1]=r[i]*LL(i)%mo;//预处理阶乘和逆元 
		int sx=0,sy=0;
		for(int i=lx;i<=rx;++i){//枚举x 
			int tmp=1;
			for(int j=0;j<n;++j){
				int k=m+i-x[j];
				if(k&1){tmp=0;break;}
				tmp=tmp*c(m,k>>1)%mo;
			}
			if((sx+=tmp)>=mo)sx-=mo;
		}
		for(int i=ly;i<=ry;++i){//枚举y 
			LL tmp=1;
			for(int j=0;j<n;++j){
				int k=m+i-y[j];
				if(k&1){tmp=0;break;}
				tmp=tmp*c(m,k>>1)%mo;
			}
			if((sy+=tmp)>=mo)sy-=mo;
		}
		return LL(sx)*sy%mo;//乘起来 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
