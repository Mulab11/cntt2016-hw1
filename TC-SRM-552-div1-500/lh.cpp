#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class Heap{
	priority_queue<int> rl,dl;
	public:
	inline int top(){
		while(dl.size()&&rl.top()==dl.top()){
			rl.pop();
			dl.pop();
		}
		if (!rl.empty()) return rl.top();
		else return -300000000;
	}
	inline void push(int x){rl.push(x);}
	inline void pop(int x){dl.push(x);}
	inline void clear(){
		while(rl.size()) rl.pop();
		while(dl.size()) dl.pop();
		return; 
	}
};

class FoxAndFlowerShopDivOne{
	static const int maxn=32,maxm=maxn*maxn*maxn*maxn/4;
	int n,m,sum[maxn][maxn][2];
	int rec[maxn][maxn][maxn][maxn][2],base;
	int lt[maxm<<2],rt[maxm<<2],mx[maxm<<2];
	Heap sav[maxm];
	
	void build(int p,int l,int r){
		lt[p]=l-base;
		rt[p]=r-base;
		mx[p]=-300000000;
		if (l==r){
			sav[l].clear();
			return;
		}
		int mid=(l+r)/2;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		return;
	}
	
	void insert(int p,int pos,int dat){
//		printf("[%d,%d]: insert [%d] %d\n",lt[p],rt[p],pos,dat);
		if (lt[p]==rt[p]){
			sav[lt[p]+base].push(dat);
			mx[p]=sav[lt[p]+base].top();
			return;
		}
		if (rt[p<<1]>=pos) insert(p<<1,pos,dat);
		else insert(p<<1|1,pos,dat);
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
		return;
	}
	
	int ask(int p,int l,int r){
		if (l>rt[p]||r<lt[p]) return -300000000;
//		printf("[%d,%d],ask %d,%d\n",lt[p],rt[p],l,r);
		if (l<=lt[p]&&r>=rt[p]) return mx[p];
		return max(ask(p<<1,l,r),ask(p<<1|1,l,r));
	}
	
	int _sum(int a,int b,int c){
		if (a<0||b<0) return 0;
		return sum[a][b][c];
	}
	
	public:
	int theMaxFlowers(vector<string> flo, int lim){
		n=flo.size();
		m=flo[0].length();
		base=n*m;
		
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j){
			sum[i][j][0]=_sum(i-1,j,0)+_sum(i,j-1,0)-_sum(i-1,j-1,0)+((flo[i][j]=='L')?1:0);
			sum[i][j][1]=_sum(i-1,j,1)+_sum(i,j-1,1)-_sum(i-1,j-1,1)+((flo[i][j]=='P')?1:0);
		}
		for (int t=0;t<n;++t)
		for (int b=t;b<n;++b)
		for (int l=0;l<m;++l)
		for (int r=l;r<m;++r){
			rec[t][b][l][r][0]=_sum(b,r,0)-_sum(b,l-1,0)-_sum(t-1,r,0)+_sum(t-1,l-1,0);
			rec[t][b][l][r][1]=_sum(b,r,1)-_sum(b,l-1,1)-_sum(t-1,r,1)+_sum(t-1,l-1,1);
		}
		int ans=-1;
		build(1,0,base<<1);
		for (int i=1;i<n;++i){
			for (int j=0;j<i;++j)
			for (int l=0;l<m;++l)
			for (int r=l;r<m;++r){
				insert(1,rec[j][i-1][l][r][0]-rec[j][i-1][l][r][1],rec[j][i-1][l][r][0]+rec[j][i-1][l][r][1]);
//				printf("insert %d,%d,%d,%d, %d - %d\n",j,i-1,l,r,rec[j][i-1][l][r][0]-rec[j][i-1][l][r][1],rec[j][i-1][l][r][0]+rec[j][i-1][l][r][1]);
			}
			for (int j=i;j<n;++j)
			for (int l=0;l<m;++l)
			for (int r=l;r<m;++r){
				ans=max(ans,ask(1,-lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]),lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]))+rec[i][j][l][r][0]+rec[i][j][l][r][1]);
//				printf("%d,%d,%d,%d ask(%d,%d), ans=%d\n",i,j,l,r,-lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]),lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]),ans);
			}
		}
		build(1,0,base<<1);
		for (int l=1;l<m;++l){
			for (int i=0;i<n;++i)
			for (int j=i;j<n;++j)
			for (int k=0;k<l;++k) insert(1,rec[i][j][k][l-1][0]-rec[i][j][k][l-1][1],rec[i][j][k][l-1][0]+rec[i][j][k][l-1][1]);
			for (int i=0;i<n;++i)
			for (int j=i;j<n;++j)
			for (int r=l;r<m;++r) ans=max(ans,ask(1,-lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]),lim-(rec[i][j][l][r][0]-rec[i][j][l][r][1]))+rec[i][j][l][r][0]+rec[i][j][l][r][1]);
		}
		return ans;
	}
};
