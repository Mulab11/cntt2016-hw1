#include <bits/stdc++.h>

using namespace std;

int sl[55][55],sp[55][55],n,m,p,ans,f[55][2000],g[55][2000],det;
char mp[55][55];
int get(int (*a)[55],int x1,int y1,int x2,int y2){//算一个矩形里有几个花 
	return a[x2][y2]-a[x2][y1-1]-a[x1-1][y2]+a[x1-1][y1-1];
}
void dp(){
	p=n*m;memset(sl,0,sizeof sl);memset(sp,0,sizeof sp);//清空数组
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			sl[i][j]=sl[i-1][j]+sl[i][j-1]-sl[i-1][j-1];
			sp[i][j]=sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1];
			if(mp[i][j]=='L')sl[i][j]++;
			if(mp[i][j]=='P')sp[i][j]++;//求前缀和 
		}
	memset(f,-1,sizeof f);//清空数组 
	memset(g,-1,sizeof g);//清空数组
	for(int i=1;i<=m;++i){//dp
		for(int j=-p;j<=p;++j)f[i][j+p]=f[i-1][j+p];
		for(int j=1;j<=n;++j)
			for(int k=j;k<=n;++k)
				for(int l=1;l<=i;++l){
					int x=get(sl,j,i-l+1,k,i),y=get(sp,j,i-l+1,k,i);
					f[i][x-y+p]=max(f[i][x-y+p],x+y);
				}
	}
	for(int i=m;i>=1;--i){//dp
		for(int j=-p;j<=p;++j)g[i][j+p]=g[i+1][j+p];
		for(int j=1;j<=n;++j)
			for(int k=j;k<=n;++k)
				for(int l=1;l<=m-i+1;++l){
					int x=get(sl,j,i,k,i+l-1),y=get(sp,j,i,k,i+l-1);
					g[i][x-y+p]=max(g[i][x-y+p],x+y);
				}
	}
	for(int i=1;i<m;++i)//统计答案 
		for(int j=-p;j<=p;++j)
		if(f[i][j+p]!=-1)
			for(int k=-p;k<=p;++k)
			if(g[i+1][k+p]!=-1)if(abs(j+k)<=det)ans=max(ans,f[i][j+p]+g[i+1][k+p]);
}

class FoxAndFlowerShopDivOne {
public:
	int theMaxFlowers(vector <string> flowers, int maxDiff) {
		n=flowers.size();m=flowers[0].size();
		ans=-1;det=maxDiff;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)mp[i+1][j+1]=flowers[i][j];
		dp();//dp计算答案 
		memset(mp,0,sizeof mp);
		swap(n,m);
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)mp[i+1][j+1]=flowers[j][i];
		dp();//交换行列再做一遍 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
