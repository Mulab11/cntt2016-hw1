#include <bits/stdc++.h>

using namespace std;

int w;

bool check(int n,int x){//判断能否一次搞定 
	if(n<=w&&(x==1||x==n))return 1;//只有不足一行而且x在头尾 
	if(w==1&&(x==1||x==n))return 1;//只有一列而且x在头尾 
	if(x==n&&n%w==1)return 1;//最后一行恰好多一个x 
	if(n<2*w&&x==w)return 1;//最后一列只有x 
	return 0;
}

int dfs(int n,int x,int s){
	if(check(n,x))return 1;
	if(s==2)return 2;//剪枝，至多四次 
	int ret=998244353,u=(x-1)/w;
	for(int i=1;i<=u;++i)
		for(int j=1;j<=w;++j)
		ret=min(ret,dfs(n-i*j,x-i*j,s+1));//删除上面 
	int d=(n-1)/w,l=(x-1)%w,r=w-l-1,ll=(n-1)%w+1;
	for(int i=1;i<=u+1;++i)
		for(int j=1;j<=l;++j){
			int tmp=i*j;
			if(j<=ll)tmp+=(d-u)*j;
			else tmp+=(d-u-1)*j+ll;//为了删的多尽量靠左 
			ret=min(ret,dfs(n-tmp,x-i*j,s+1));//删除左边 
		}
	for(int i=1;i<=u+1;++i)
		for(int j=1;j<=r;++j){
			int tmp=i*j,res=ll-l-1;
			if(res<0)res=0;
			if(j<=res)tmp+=(d-u)*j;
			else tmp+=(d-u-1)*j+res;//为了删的多尽量靠左 
			ret=min(ret,dfs(n-tmp,x-(i-1)*j,s+1));//删除右边 
		}
	if(d!=u)ret=min(ret,dfs((u+1)*w,x,s+1));//删除下面 
	return ret+1;
}

class FoxAndAvatar {
public:
	int minimalSteps(int n, int width, int x) {
		w=width;
		if(n==1)return 0;//特判 
		return min(4,dfs(n,x,0));
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
