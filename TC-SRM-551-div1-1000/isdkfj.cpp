#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1e9+7;

int c[55][55],n,m,ans[99],w[55],f[99],g[99],t1,t2;
struct orz{int s,c;
	bool operator<(const orz&rhs)const{return s<rhs.s;}}//排序 
	p1[1<<21],p2[1<<21];
LL ksm(LL x,int k){//快速幂 
	LL r=1;
	for(;k;k>>=1,x=x*x%mo)if(k&1)r=r*x%mo;
	return r;
}
int get(int kk){//用matrixtree定理求生成树 
	static int a[55][55];
	memset(a,0,sizeof a); 
	for(int i=1;i<=n-m;++i)a[i][i]=n-1;
	for(int i=n-m+1;i<=n-kk;++i)a[i][i]=n-m;
	for(int i=n-kk+1;i<=n;++i)a[i][i]=n-1-m+kk;
	for(int i=1;i<=n-m;++i)
		for(int j=1;j<=n;++j)if(i!=j)a[i][j]=mo-1;
	for(int i=n-m+1;i<=n-kk;++i)
		for(int j=1;j<=n-m;++j)a[i][j]=mo-1;
	for(int i=n-kk+1;i<=n;++i)
		for(int j=1;j<=n;++j)if(i!=j&&(j<=n-m||j>n-kk))a[i][j]=mo-1;
	//构造矩阵 
	bool sg=0;//符号 
	for(int i=1;i<n;++i){
		int t=0;
		for(int j=i;j<n;++j)if(a[j][i]){t=j;break;}
		if(!t)return 0;
		if(t!=i){
			for(int j=1;j<n;++j)swap(a[t][j],a[i][j]);
			sg^=1;//交换两行符号要取反 
		}
		for(int j=i+1;j<n;++j)
		if(a[j][i]){
			t=a[j][i]*ksm(a[i][i],mo-2)%mo;//要乘的系数 
			for(int k=i;k<n;++k)
			if((a[j][k]-=LL(t)*a[i][k]%mo)<0)a[j][k]+=mo;//消掉a[j][i] 
		}
	}
	LL ret=1;
	for(int i=1;i<n;++i)ret=ret*a[i][i]%mo;//求行列式 
	if(sg)ret=(mo-ret)%mo;//最终答案 
	return ret;
}
void dfs(int x,int ed,orz*a,int&tot,int sum,int cnt){//搜索 
	if(x>ed){
		++tot;
		a[tot].s=sum;
		a[tot].c=cnt;//记录个数和和 
		return;
	}
	dfs(x+1,ed,a,tot,sum,cnt);
	dfs(x+1,ed,a,tot,sum+w[x],cnt+1);
}

class SweetFruits {
public:
	int countTrees(vector <int> sweetness, int maxSweetness) {
		n=sweetness.size();
		for(int i=0;i<n;++i)
		if(sweetness[i]!=-1)w[++m]=sweetness[i];
		c[0][0]=1;
		for(int i=1;i<=50;++i){
			c[i][0]=1;
			for(int j=1;j<=i;++j)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mo;
			//预处理组合数，利用公式c[i][j]=c[i-1][j-1]+c[i-1][j] 
		}
		for(int i=0;i<=m;++i){
			ans[i]=get(i);
			for(int j=1;j<=i;++j)
			if((ans[i]-=LL(ans[i-j])*c[i][j]%mo)<0)ans[i]+=mo;
		}
		int mid=m/2;
		dfs(1,mid,p1,t1,0,0);
		dfs(mid+1,m,p2,t2,0,0);//搜索 
		sort(p1+1,p1+t1+1);
		sort(p2+1,p2+t2+1);//排序 
		for(int i=1;i<=t2;++i)++g[p2[i].c];
		for(int i=1,j=t2;i<=t1&&j>=1;++i){//统计答案 
			while(j>=1&&p1[i].s+p2[j].s>maxSweetness)--g[p2[j--].c];
			for(int k=0;k<=m;++k)if((f[k+p1[i].c]+=g[k])>=mo)f[k+p1[i].c]-=mo;
		}
		int ret=0;
		for(int i=0;i<=m;++i)ret=(ret+LL(ans[i])*f[i])%mo;
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
