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

const int N=256;
int n,m;
vi wx,wy,bx,by;
bitset<N> u[N][N],d[N][N];

vi make(vector<string> a){
	string s="";
	int now=0;
	vi res;res.clear();
	for(int i=0;i<a.size();i++) s+=a[i];
	for(int i=0;i<s.length();i++)
		if(s[i]>='0'&&s[i]<='9') now=now*10+s[i]-'0'; else res.pb(now),now=0;
	if(now) res.pb(now);
	return res;
}
ll cross(int ax,int ay,int bx,int by){
	return (ll) ax*by-(ll)ay*bx;
}

class CheckerFreeness{
public:
	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY){
		wx=make(whiteX);wy=make(whiteY);
		bx=make(blackX);by=make(blackY);
		n=wx.size();m=bx.size();
		memset(u,0,sizeof(u));memset(d,0,sizeof(d));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) continue;
				for(int k=0;k<m;k++)
					if(cross(wx[i]-bx[k],wy[i]-by[k],wx[j]-bx[k],wy[j]-by[k])<0) u[k][i][j]=1; else d[k][i][j]=1;
			}
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++){
				bitset<N> tmp=0;
				for(int k=0;k<n;k++)
					if(cross(bx[i]-wx[k],by[i]-wy[k],bx[j]-wx[k],by[j]-wy[k])<0) tmp[k]=1;
				for(int k=0;k<n;k++){
					if(cross(bx[i]-wx[k],by[i]-wy[k],bx[j]-wx[k],by[j]-wy[k])<0) continue;
					if((tmp&u[i][k]&d[j][k]).count()) return "NO";
					if((tmp&u[j][k]&d[i][k]).count()) return "NO";
				}
			}
		return "YES";
	}
};
