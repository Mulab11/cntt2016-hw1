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

class TheTree{
public:
	int maximumDiameter(vector <int> cnt){
		int si=0;
		for(int i=0;i<cnt.size();i++){
			if(cnt[i]!=1) si++;
			else{
				int ans=cnt.size()+si;
				vi tmp;tmp.clear();
				for(int j=i+1;j<cnt.size();j++) tmp.pb(cnt[j]);
				ans=max(ans,maximumDiameter(tmp));
				return ans;
			}
		}
		return cnt.size()*2;
	}
};
