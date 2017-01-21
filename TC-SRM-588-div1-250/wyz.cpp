// BEGIN CUT HERE

// END CUT HERE
#line 5 "GUMIAndSongsDiv1.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=50;

class GUMIAndSongsDiv1 {
	int n,a[maxn];
	public:
	int maxSongs(vector <int> duration, vector <int> tone, int T){
		n=duration.size();
		int ret=0,s;
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)if (tone[i]<=tone[j]&&(s=tone[j]-tone[i])<T){
				int m=0,res=0;
				for (int k=0;k<n;++k)if (tone[i]<=tone[k]&&tone[k]<=tone[j])a[m++]=duration[k];
				sort(a,a+m);
				for (int k=0;k<m;++k)
					if (s+a[k]<=T) s+=a[k],++res;
					else break;
				ret=max(ret,res);
			}
		return ret;
	}
};
