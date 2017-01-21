// BEGIN CUT HERE

// END CUT HERE
#line 5 "SweetFruits.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define P 1000000007
int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=(ll)ret*x%P;
		x=(ll)x*x%P;
		y=y>>1;
	}
	return ret;
}

#define inc(x,y) if(((x)+=(y))>=P)(x)-=P
#define dec(x,y) if(((x)-=(y))<0)(x)+=P

const int maxn=44;

int a[maxn][maxn];
int n;
int gauss(int u){
	if (u>n-1) return 1;
	if (u==n-1) return a[u][u];
	int v=-1;
	for (int i=u;i<n;++i)if (a[i][u]){v=i;break;}
	if (v==-1) return 0;
	if (v>u)for (int i=u;i<n;++i)swap(a[u][i],a[v][i]);
	for (int i=u+1;i<n;++i){
		int k=1LL*a[i][u]*fast_pow(a[u][u],P-2)%P;
		for (int j=u;j<n;++j) (a[i][j]+=P-1LL*k*a[u][j]%P)%=P;
	}
	return 1LL*gauss(u+1)*a[u][u]%P;
}

void addedge(int u,int v){
	inc(a[u][u],1);inc(a[v][v],1);
	dec(a[u][v],1);dec(a[v][u],1);
}
int calc(int RealSweet,int Sweet){
//	printf("%d %d\n",RealSweet,Sweet);
	memset(a,0,sizeof(a));
	for (int i=0;i<RealSweet;++i)for (int j=i+1;j<RealSweet;++j) addedge(i,j);
	for (int i=0;i<RealSweet;++i)for (int j=Sweet;j<n;++j) addedge(i,j);
	for (int i=RealSweet;i<Sweet;++i)for (int j=Sweet;j<n;++j) addedge(i,j);
	for (int i=Sweet;i<n;++i)for (int j=i+1;j<n;++j) addedge(i,j);
	return gauss(1);
}

const int maxm=(1e6)+(1e5);

class SweetFruits{
	void Get(int *a,int n,pair<int,int> *res,int &m){
		m=0;
		for (int msk=(1<<n)-1;msk>=0;--msk){
			int cnt=0,sum=0;
			for (int j=0;j<n;++j)
				if (msk&(1<<j)) ++cnt,sum+=a[j];
			res[m++]=make_pair(sum,cnt);
		}
		sort(res,res+m);
	}
	pair<int,int> a0[maxm],a1[maxm];
	int n0,n1,m0,m1;
	int swt,a[maxn];
	int cnt[maxn];
	int res[maxn];
	public:
	int countTrees(vector <int> sweetness, int maxSweetness){
		n=sweetness.size();
		swt=0;
		for (int i=0;i<n;++i)if (sweetness[i]>=0)a[swt++]=sweetness[i];
		for (int i=0;i<=swt;++i){
			res[i]=calc(i,swt);
			int _c=1,tmp;
			for (int j=0;j<i;++j){
				tmp=1LL*_c*res[j]%P;
				dec(res[i],tmp);
				_c=1LL*_c*(i-j)%P*fast_pow(j+1,P-2)%P;
			}
		}
//		return 2333;
		n0=swt>>1;n1=swt-n0;
		Get(a,n0,a0,m0);
		Get(a+n0,n1,a1,m1);
		int j=0;
		memset(cnt,0,sizeof(cnt));
		int ret=0;
		for (int i=m0-1;i>=0;--i){
			while (j<m1&&a1[j].first+a0[i].first<=maxSweetness) ++cnt[a1[j++].second];
			for (int j=0;j<=n1;++j) ret=(1LL*cnt[j]*res[j+a0[i].second]+ret)%P;
		}
		return ret;
	}
};
