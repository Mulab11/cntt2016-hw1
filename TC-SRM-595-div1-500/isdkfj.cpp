#include <bits/stdc++.h>

using namespace std;

int f[2505],g[2505][2505];

class LittleElephantAndRGB {
public:
	long long getNumber(vector <string> list, int minGreen) {
		string s;
		for(int i=0;i<list.size();++i)s+=list[i];
		int n=s.size(),m=minGreen;
		for(int i=n-1,j=0,k=n;i>=0;--i){
			if(s[i]=='G')++j;else j=0;//开头的连续段 
			if(j>=m)k=i+m-1;//最后一个连续G的结尾 
			f[i]=f[i+1]+n-k;//包含连续G的个数 
			for(int t=1;t<m;++t)g[i][t]=g[i+1][t];
			if(j&&j<m){
				for(int t=1;t<j;++t)++g[i][t];
				g[i][j]+=k-i-j+1;//开头为j且中间不连续的个数 
			}else if(j>=m){
				for(int t=1;t<m;++t)++g[i][t];
			}
		}
		for(int i=0;i<n;++i)
			for(int j=m-1;j>=1;--j)g[i][j]+=g[i][j+1];//前缀和 
		long long ret=0;
		for(int i=0;i<n-1;++i)
			for(int j=i,k=0,l=1,t=0,q=0;j>=0;--j){
				if(l){if(s[j]=='G')++k;else l=0;}//开头的G 
				if(s[j]=='G'){++t;if(t>=m)q=1;}else t=0;//是否连续 
				if(q)ret+=(n-i-1)*(n-i)/2;//连续随便取 
				else ret+=g[i+1][m-k]+f[i+1];//不连续的答案 
			}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
