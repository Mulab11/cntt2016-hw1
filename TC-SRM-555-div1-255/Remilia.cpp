// by ξ
// program sky  :)

#include <bits/stdc++.h>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)

using namespace std;

struct CuttingBitString{
	int f[55];
	int getmin(string S){
		int n=S.length();S=' '+S;
		For(i,1,n){
			f[i]=99;
			rep(j,0,i)if(f[j]+1<f[i]){
				int x=0;
				For(k,j+1,i)x=(x*10+S[k]-'0')%5;// 是5的倍数
				if(!x)f[i]=f[j];
			}
		}
		return f[n]==99?-1:f[n];
	}
};