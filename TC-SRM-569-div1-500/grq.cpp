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

class TheJediTest{
public:
	int minimumSupervisors(vector<int> a, int k){
		n=a.size();
		vi ex(n,0);
		for(int i=0;i<n-1;i++){
			int t;
			t=(ex[i]+a[i])%k;
			if(t<=a[i]){a[i]-=t;ex[i+1]+=t;continue;}
			t=k-t;
			if(t<=a[i+1]){ex[i]+=t;a[i+1]-=t;continue;}
			ex[i]+=a[i+1];a[i+1]=0;
		}
		int ans=0;
		for(int i=0;i<n;i++) ans+=((ll)ex[i]+a[i]+k-1)/k;
		return ans;
	}
};

