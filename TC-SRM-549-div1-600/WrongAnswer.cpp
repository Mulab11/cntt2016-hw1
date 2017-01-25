// FST:使用map导致内存爆炸
#include <vector>
#include <string>
#include <algorithm>
#define INF 10000000
using namespace std;
class MagicalHats{
public:
	int N,K,n,x[13];
	vector<int> C;
	int popc[1<<13],tr[1<<13],sets[1<<13];
	int f[1594323];
	bool vis[1594323],ex[1594323];
	int Min(int a,int b){return a<b?a:b;}
	void Cmax(int&a,int b){b>a?a=b:1;}
	int F(int S,int T){
		int V=tr[S]+tr[T];
		if(vis[V])return f[V];
		vis[V]=1;
		if(!ex[V])return f[V]=-INF;
		if(popc[S]==K)return f[V]=0;
		int ans=-INF;
		for(int i=0;i<n;i++)if(!(S>>i&1)){
			if(!ex[tr[S|1<<i]+tr[T]])Cmax(ans,C[popc[T]]+F(S|1<<i,T|1<<i));
			else if(!ex[tr[S|1<<i]+tr[T|1<<i]])Cmax(ans,F(S|1<<i,T));
			else Cmax(ans,Min(C[popc[T]]+F(S|1<<i,T|1<<i),F(S|1<<i,T)));
		}
		return f[V]=ans;
	}
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses){
		N=board.size()+board[0].length();K=numGuesses;C=coins;
		std::sort(C.begin(),C.end());
		n=*popc=*tr=*sets=0;
		for(int i=0;i<board.size();i++)
			for(int j=0;j<board[0].length();j++)if(board[i][j]=='H')x[n++]=1<<i|1<<j+board.size();
		for(int S=1;S<(1<<n);S++){
			int i=0;while(!(S>>i&1))i++;
			popc[S]=popc[S&(S-1)]+1;
			tr[S]=tr[S>>1]*3+S%2;
			sets[S]=sets[S&(S-1)]^x[i];
		}
		for(int S=0;S<(1<<n);S++)if(popc[S]==C.size()&&sets[S]==sets[(1<<n)-1])
			for(int T=0;T<(1<<n);T++)ex[tr[T]+tr[S&T]]=1;
		int ans=F(0,0);
		return ans<0?-1:ans;
	}
};
