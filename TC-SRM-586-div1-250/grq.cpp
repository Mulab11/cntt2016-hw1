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

vector<double> a;
vector<int> b,X;
int n;

bool contain(int x,int y,double a){
	return a>=min(x,y)&&a<=max(x,y);
}

class PiecewiseLinearFunction{
public:
	int maximumSolutions(vector<int> Y){
		n=Y.size();b.clear();a.clear();
		X=Y;sort(X.begin(),X.end());
		for(int i=0;i<n;i++){
			if(i) b.pb(0),a.pb((double)(X[i]+X[i-1])/2.0);
			a.pb(X[i]);b.pb(0);
		}
		//建出n-1条线段和n个点 
		for(int i=0;i<n-1;i++)
			if(Y[i]==Y[i+1]) return -1;
		for(int i=0;i<n-1;i++){
			int l=Y[i],r=Y[i+1];
			for(int j=0;j<n*2-1;j++)
				if(contain(l,r,a[j])&&a[j]!=r) b[j]++;
		}//对于每条线，更新在上面线段和点的情况 
		for(int j=0;j<n*2-1;j++) if(a[j]==Y[n-1]) b[j]++;
		int ans=0;
		for(int i=0;i<n*2-1;i++) ans=max(ans,b[i]);
		return ans;
	}
};

