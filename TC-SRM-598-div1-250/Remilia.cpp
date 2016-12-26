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
using namespace std;
const int maxn=55;
bool use[maxn];

/*
先把>200的都放掉
枚举用几个100*3，剩下的贪心大配小即可
*/

class BinPacking{
public:
	int minBins(vector<int>a){
		sort(a.begin(),a.end());
		int i=a.size()-1,ans=0;
		while (i>=0&&a[i]>200) ans++,i--;
		for (;i>=0;i--){
			if (use[i]) continue;
			int j=i-1;ans++;
			int rem=300-a[i];
			while (j>=0&&a[j]>rem) j--;
			while (j>=0&&use[j]) j--;
			if (j>-1) use[j]=1,rem-=a[j];
			if (rem>=100){
				while (j>=0&&a[j]>rem) j--;
				while (j>=0&&use[j]) j--;
				if (j>-1) use[j]=1,rem-=a[j];
			}
		}
		return ans;
	}
};
