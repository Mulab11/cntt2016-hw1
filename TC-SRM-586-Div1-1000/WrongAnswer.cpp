#include <vector>
#define INF 100000000
using namespace std;
class StringWeight{
public:
	int n,L[51],S[51],f[51][27][27];
	bool vis[51][27][27];
	void cmin(int&a,int b){b<a?a=b:1;}
	int dfs(int i,int now,int past){
		if(i==n)return now?INF:0;
		if(vis[i][now][past])return f[i][now][past];
		vis[i][now][past]=1;
		int res=INF,sig=L[i]<26?L[i]:26;
		for(int leave=0,lsum=0;leave<=sig&&leave<=now;lsum+=S[i]+leave++)
			for(int arrive=0,asum=0;arrive+leave<=sig&&now+past+arrive<=26;asum+=S[i]+L[i]-++arrive)
				for(int appear=0;leave+arrive+appear<=sig&&now+past+arrive+appear<=26;appear++)
					if(sig-leave-arrive-appear<=now-leave)cmin(res,dfs(i+1,now-leave+arrive,past+leave+appear)+lsum-asum+(sig-leave-arrive-appear>0?0:L[i]-sig));
		return f[i][now][past]=res;
	}
	int getMinimum(vector <int> L){
		n=L.size();
		for(int i=0;i<n;i++)S[i+1]=S[i]+(this->L[i]=L[i]);
		return dfs(0,0,0);
	}
};
