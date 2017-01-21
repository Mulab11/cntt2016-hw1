// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConversionMachine.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define P 1000000007

const int maxm=123;

struct matrix{
	int x,y;
	int a[maxm][maxm];
	matrix(){}
	matrix(int _x,int _y):x(_x),y(_y){memset(a,0,sizeof(a));}
	matrix(int _x){
		x=y=_x;
		memset(a,0,sizeof(a));
		for (int i=1;i<=_x;++i) a[i][i]=1;
	}
	void print(){
		for (int i=1;i<=x;++i,puts(""))
			for (int j=1;j<=y;++j)
				printf("%d",a[i][j]);
	}
};
 
inline matrix operator *(matrix a,matrix b){
	if (a.y!=b.x) swap(a,b);
	matrix ret=matrix(a.x,b.y);
	int z=a.y;
	for (int i=1;i<=ret.x;++i)
		for (int j=1;j<=ret.y;++j){
			ret.a[i][j]=0;
			for (int k=1;k<=z;++k)
				ret.a[i][j]=(1LL*a.a[i][k]*b.a[k][j]+ret.a[i][j])%P;
		}
	return ret;
}
 
matrix fast_pow(matrix x,ll y){
	matrix ret=matrix(x.x);
	while (y){
		if (y&1) ret=ret*x;
		y/=2;
		x=x*x;
	}
	return ret;
}

const int maxn=13;

class ConversionMachine{
	matrix A;
	int m;
	int n;
	int id[maxn][maxn];
	public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost){
		n=word1.size();
		int _left=maxCost,t=0;
		int cnt[3];
		for (int i=0;i<n;++i){
			int ch=word1[i],tmp=0;
			while (ch!=word2[i]){
				if ((_left-=costs[ch-'a'])<0) return 0;
				if ((++ch)>'c') ch='a';
				++tmp;
			}
			++cnt[tmp];t+=tmp;
		}
		t+=_left/(costs[0]+costs[1]+costs[2])*3;
//		printf("%d\n",t);
		m=0;
		for (int i=0;i<=n;++i)for (int j=0;i+j<=n;++j)
			id[i][j]=++m;
		++m;
		A=matrix(m,m);
		for (int i=0;i<=n;++i)for (int j=0;i+j<=n;++j){
			if (n-i-j) A.a[id[i+1][j]][id[i][j]]+=(n-i-j);
			if (i) A.a[id[i-1][j+1]][id[i][j]]+=i;
			if (j) A.a[id[i][j-1]][id[i][j]]+=j;
		}
		A.a[m][id[0][0]]+=1;
		A.a[m][m]+=1;
//		A.print();
		A=fast_pow(A,t+1);
		return A.a[m][id[cnt[2]][cnt[1]]];
	}
};
