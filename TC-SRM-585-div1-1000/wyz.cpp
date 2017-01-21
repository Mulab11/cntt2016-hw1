// BEGIN CUT HERE

// END CUT HERE
#line 5 "EnclosingTriangle.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=240004;

class EnclosingTriangle{
	bool judge(int x0,int y0,int x1,int y1,int x2,int y2){
		return 1LL*(x1-x0)*(y2-y0)-1LL*(x2-x0)*(y1-y0)<=0;
	}
	int X[maxn],Y[maxn],n;
	int nxt[maxn],pre[maxn];
	ll s[maxn];
	public:
	long long getNumber(int m, vector <int> x, vector <int> y){
		n=m<<2;
		for (int i=0;i<m;++i) X[i]=0,Y[i]=i;
		for (int i=0;i<m;++i) X[i+m]=i,Y[i+m]=m;
		for (int i=0;i<m;++i) X[i+2*m]=m,Y[i+2*m]=m-i;
		for (int i=0;i<m;++i) X[i+3*m]=m-i,Y[i+3*m]=0;
		for (int i=0;i<n;++i){
			for (nxt[i]=i?nxt[i-1]:1;nxt[i]+1<n;++nxt[i]){
				bool found=0;
				for (int j=0;!found&&j<x.size();++j)
					if (!judge(X[i],Y[i],X[nxt[i]+1],Y[nxt[i]+1],x[j],y[j])) found=1;
				if (found) break;
			}
			for (pre[i]=i?pre[i-1]:1;pre[i]<n;++pre[i]){
				bool found=0;
				for (int j=0;!found&&j<x.size();++j)
					if (!judge(X[pre[i]],Y[pre[i]],X[i],Y[i],x[j],y[j])) found=1;
				if (!found) break;
			}
			s[i]=i?s[i-1]+nxt[i]:nxt[i];
		}
//		for (int i=0;i<n;++i) printf("%d ",nxt[i]);puts("");
//		for (int i=0;i<n;++i) printf("%d ",pre[i]);puts("");
		ll ret=0;
		int p=0;
		for (int i=0;i<n;++i){
			while (p<n&&(nxt[p]<pre[i]||p<=i)) ++p;
//			printf("%d ",p);
			if (p>nxt[i]) continue;
			ret+=s[nxt[i]]-s[p-1]-1LL*(nxt[i]-p+1)*(pre[i]-1);//*(pre[i]-p+pre[i]-nxt[i])/2;
			if (pre[i]==nxt[i]) --ret;
		}
		return ret;
	}
};
