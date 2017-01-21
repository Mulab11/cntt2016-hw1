#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

class TheBrickTowerEasyDivOne{
public:
	int find(int rc, int rh, int bc, int bh){
		int ans=0;
		if(rh!=bh) ans=min(rc,bc)+min(rc-1,bc)+min(rc,bc-1)+2;
		else ans=min(rc,bc)*2+(rc!=bc);
		return ans;
	}
};
