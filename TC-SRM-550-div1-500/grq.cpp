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

inline int c(ll x,ll y){
	if(x<y) return 0;
	if(!y) return 1;
	ll tx=x&1,ty=y&1;
	if(tx<ty) return 0;
	return c(x/2,y/2);
}//利用Lucas定理算组合数 

class CheckerExpansion{
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
		t--;
		vector<string> ans;
		ans.clear();
		for(int i=0;i<h;i++){
			string t="";
			for(int j=0;j<w;j++) t=t+'.';
			ans.pb(t);
		}//初始化 
		if(x0==0&&y0==0) ans[0][0]='A';
		for(ll x=x0;x<x0+w;x++){
			for(ll y=y0;y<y0+h;y++){
				ll k=x+y;
				if(k&1) continue;//通过x+y模2判断是否可能存在检验器 
				k/=2;if(k>t||y>k) continue;//判断是否超过t轮 
				if(c(k,y)){//判断此方格对应的组合数是否模2为1 
					if(k&1) ans[y-y0][x-x0]='B'; else ans[y-y0][x-x0]='A';//判断是谁的检验器 
				}
			}
		}
		reverse(ans.begin(),ans.end());
		return ans;
	}
};
