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
int num[26];

/*

每个字符最多只动一次
不用动的一定是B的后缀
求出B的最长后缀使得其是A的子序列

*/

class LittleElephantAndString{
public:
	int getNumber(string a,string b){
		 int n=a.size(),ans=0;
		 rep(i,0,n-1) num[a[i]-'A']++,num[b[i]-'A']--;
		 rep(i,0,25) if (num[i]) return -1;
		 rep(i,0,n-1){
		 	int cnt=0,nw=i;
		 	for (int j=0;j<n&&nw<n;j++) if (a[j]==b[nw]) nw++;
			if (nw==n) ans=max(ans,nw-i);
		 }
		 return n-ans;
	}
};
