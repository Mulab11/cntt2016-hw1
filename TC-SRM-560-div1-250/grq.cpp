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

vi a,b;

class TomekPhone{
public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes){
		a=frequencies;
		b.clear();
		for(int i=0;i<keySizes.size();i++)
			for(int j=1;j<=keySizes[i];j++)
				b.pb(j);
		sort(a.begin(),a.end());
		reverse(a.begin(),a.end());
		sort(b.begin(),b.end());
		if(a.size()>b.size()) return -1;
		int ans=0;
		for(int i=0;i<a.size();i++) ans+=a[i]*b[i];
		return ans;
	}
};
