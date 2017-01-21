// BEGIN CUT HERE

// END CUT HERE
#line 5 "DrawingPointsDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=150;

class DrawingPointsDivOne{
	int n;
	bool b[maxn*2][maxn*2];
	bool a[maxn*2][maxn*2],last[maxn*2][maxn*2];
	int r,c;
	bool judge(int key){
		memcpy(a,b,sizeof(b));
		for (int k=0;k<key;++k){
			memcpy(last,a,sizeof(a));
			for (int i=0;i<r+k;++i)for (int j=0;j<c+k;++j)if (last[i][j]){
				a[i+1][j]=1;
				a[i][j+1]=1;
				a[i+1][j+1]=1;
			}			
		}
		for (int k=key;k;--k){
			memcpy(last,a,sizeof(a));
			memset(a,0,sizeof(a));
			for (int i=0;i<r+k;++i)for (int j=0;j<c+k;++j)
				if (last[i][j]&&last[i+1][j]&&last[i][j+1]&&last[i+1][j+1])
					a[i][j]=1;
		}
		for (int i=0;i<r+key;++i)for (int j=0;j<c+key;++j)
			if (a[i][j]^b[i][j]) return 0;
		return 1;
	}
//	pair<int,int> P[maxn];
	public:
	int maxSteps(vector <int> x, vector <int> y){
		n=x.size();
//		for (int i=0;i<n;++i) P[i]=make_pair(x[i],y[i]);
//		sort(P,P+n);
//		for (int i=0;i<n;++i) printf("%d %d\n",P[i].first,P[i].second);
		int mnx=x[0],mny=y[0];
		for (int i=1;i<n;++i)
			mnx=min(mnx,x[i]),
			mny=min(mny,y[i]);
		r=c=0;
		for (int i=0;i<n;++i)
			r=max(r,x[i]-=mnx),
			c=max(c,y[i]-=mny);
		memset(b,0,sizeof(b));
		for (int i=0;i<n;++i) b[x[i]][y[i]]=1;
		r+=5;c+=5;
//		for (int i=0;i<r;++i,puts(""))for (int j=0;j<c;++j)printf("%d",a[i][j]);
		int _l=0,_r=max(r,c);
		while (_l+1<_r){
			int mid=(_l+_r)>>1;
			if (judge(mid)) _l=mid;
			else _r=mid;
		}
		if (_r==max(r,c)) _l=-1;
//		for (int i=0;i<=_l;++i) printf("%d %d\n",i,judge(i));
		return _l;
	}
};
