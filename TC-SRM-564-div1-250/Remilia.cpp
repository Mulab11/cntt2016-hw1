#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>

using namespace std;

struct KnightCircuit2{
	int maxSize(int w,int h){
		if (w>h) swap(w,h);
		if (w==1) return 1;
		if (w==2) return (h+1)/2;
		if (w==3&&h==3) return 8;
		return w*h;
	}
};
