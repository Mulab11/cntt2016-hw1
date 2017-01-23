#include<bits/stdc++.h>
#define sqr(x) ((x)*(x))
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

string ss;
int a[2505],n,s;
double ch[20];
class TheSwapsDivOne{
public:
	double find(vector<string> sequence, int k){
		ss="";s=0;
		for(int i=0;i<sequence.size();i++) ss+=sequence[i];
		n=ss.size();
		for(int i=0;i<n;i++) a[i]=ss[i]-'0';
		for(int i=0;i<n;i++) s+=a[i];
		double ans=0.0;
		for(int i=0;i<10;i++) ch[i]=i;
		for(;k--;) {for(int i=0;i<10;i++) ch[i]+=(s-ch[i]*n)*2/n/(n-1);}
		for(int i=0;i<n;i++)
			ans+=(double)ch[a[i]]*(i+1)*(n-i)*2/n/(n+1);
		return ans;
	}
};
