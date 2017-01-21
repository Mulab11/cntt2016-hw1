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

const int mod=555555555;
int ans,C[3005][3005],w,h,r,c,s;

void solve(int a,int b){
	if(a*(w-b)+b*(h-a)!=s) return ;
	if(a>r||b>c) return;
	int tmp=0;
	tmp=(ll)C[h][a]*C[w][b]%mod;a=r-a;b=c-b;
	if((a&1)||(b&1)) return ;
	a/=2;b/=2;
	tmp=(ll)tmp*C[h+a-1][h-1]%mod*C[w+b-1][w-1]%mod;
	ans=(ans+tmp)%mod;
}

class XorBoard{
public:
	int count(int H, int W, int R, int CC, int S){
		h=H;w=W;r=R;c=CC;s=S;
		for(int i=0;i<=3000;i++){
			C[i][0]=C[i][i]=1;
			for(int j=1;j<i;j++)
				C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}ans=0;
		for(int a=0;a<=h;a++)
			for(int b=0;b<=w;b++)
				solve(a,b);
		return ans;
	}
};
