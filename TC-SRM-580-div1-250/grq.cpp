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

vi a,b,c;
bool con(int x,int l,int r){return l<=x&&x<=r;}

class EelAndRabbit{
public:
	int getmax(vector<int> l, vector<int> t){
		a.clear();b.clear();c.clear();
		int n=l.size();
		for(int i=0;i<n;i++){
			a.pb(-t[i]-l[i]);b.pb(-t[i]);
			c.pb(-t[i]-l[i]),c.pb(-t[i]);
		}
		int ans=0;
		for(int i=0;i<n*2;i++)
			for(int j=i+1;j<n*2;j++){
				int cnt=0;
				for(int k=0;k<n;k++) if(con(c[i],a[k],b[k])||con(c[j],a[k],b[k])) cnt++;
				ans=max(ans,cnt);
			}
		return ans;
	}
};
