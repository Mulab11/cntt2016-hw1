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

bitset<128> vis[1<<12][128];//vis[S][x][y]表示状态为S，红色有x个，绿色有y个是否被访问过 
int n;
queue<pair<pii,int> > q;

class KeyDungeonDiv1{
public:
	int maxKeys(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys){
		n=doorR.size();
		memset(vis,0,sizeof(vis));
		q.push(mp(mp(keys[0],keys[1]),0));
		vis[0][keys[0]][keys[1]]=1;
		int ans=0;
		while(!q.empty()){
			int x=q.front().SS,r=q.front().FF.FF,g=q.front().FF.SS,w=keys[0]+keys[1]+keys[2]-r-g;q.pop();
			for(int i=0;i<n;i++) if(x&(1<<i)) w+=roomW[i]+roomR[i]+roomG[i]-doorR[i]-doorG[i];
			ans=max(ans,r+g+w);
			for(int i=0;i<n;i++)
				if(!(x&(1<<i))&&r+g+w>=doorR[i]+doorG[i]&&r+w>=doorR[i]&&g+w>=doorG[i]){
					int rr=max(0,r-doorR[i])+roomR[i],gg=max(0,g-doorG[i])+roomG[i];
					if(!vis[x^(1<<i)][rr][gg]) q.push(mp(mp(rr,gg),x^(1<<i))),vis[x^(1<<i)][rr][gg]=1;
				}//加入新的状态 
		}
		return ans;
	}
};
