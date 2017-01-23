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

int n;
vi a,b;

class TeamContest{
public:
	int worstRank(vector<int> strength){
		a=strength;b.clear();
		n=a.size()/3;
		int rat=max(a[0],max(a[1],a[2]))+min(a[0],min(a[1],a[2]));
//		debug(rat);
		for(int i=3;i<n*3;i++) b.pb(a[i]);
		sort(b.begin(),b.end());
		reverse(b.begin(),b.end());
//		for(int i=0;i<b.size();i++) printf("%d ",b[i]);puts("");
		int l=0,r=n-1;
		while(l<r){
			int mid=l+r>>1,m=(n-1-mid)*3;
//			if(mid==1) debug(m);
			bool isok=1;
			for(int i=0;i<m/3;i++)
				if(b[i]+b[m-i*2-1]<=rat) isok=0;
			if(isok) r=mid; else l=mid+1;
		}
		return n-r;
	}
};
