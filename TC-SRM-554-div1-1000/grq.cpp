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

vi h;
int n,r[55],vis[55];
bool cmp(int x,int y){
	if(h[x]!=h[y]) return h[x]>h[y];
	return x<y;
}
class TheBrickTowerMediumDivOne{
public:
	vector <int> find(vector <int> height){
		vi ans,tmp;ans.clear();tmp.clear();
		h=height;n=h.size();
		for(int i=0;i<n;i++) r[i]=i;
		sort(r,r+n,cmp);
		memset(vis,0,sizeof(vis));
		int now=0;
		for(int i=0;i<n;i++){
			if(r[i]==now){
				ans.pb(r[i]);
				now++;while(now<n&&vis[now]) now++;
			}
			else tmp.pb(r[i]);
			vis[r[i]]=1;
		}
		for(int i=0;i<tmp.size();i++){
			int l=i,r=i;
			while(r<tmp.size()&&h[tmp[r]]==h[tmp[l]]) r++;
			reverse(tmp.begin()+l,tmp.begin()+r);
			i=r-1;
		}
		while(tmp.size()>0) ans.pb(tmp[tmp.size()-1]),tmp.pop_back();
		return ans;
	}
};
