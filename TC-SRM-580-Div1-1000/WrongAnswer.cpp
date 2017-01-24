#include <vector>
#include <string>
#define INF 10000000
using namespace std;
class WallGameDiv1{
public:
	int R,C,c[52][52],S[52][52],f[52][52][52];
	void cmin(int&a,int b){b<a?a=b:a;}
	void cmax(int&a,int b){b>a?a=b:a;}
	// (i,j,k)为当前位于(i,j)，Wall在(j,k]或[k,j)，轮到E时的答案
	int dfs(int i,int j,int k){
		if(i==R-1)return c[i][j];
		int&g=f[i][j][k];
		if(g)return g-1;
		g=c[i][j]+dfs(i+1,j,j); // j不放，走到(i+1,j)
		int t=INF;
		// j放，走到j-1或k+1
		if(j<k){
			if(j)cmin(t,dfs(i,j-1,k)); // 走到j-1，Wall变为(j-1,k]
			if(k+1<C)cmin(t,dfs(i,k+1,j)+S[i][k+1]-S[i][j+1]); // 走到k+1，Wall变为[j,k+1)
		}
		else{
			if(k)cmin(t,dfs(i,k-1,j)+S[i][j]-S[i][k]); // 走到k-1，Wall变为(k-1,j]
			if(j+1<C)cmin(t,dfs(i,j+1,k)); // 走到j+1，Wall变为[k,j+1)
		}
		if(t<INF)cmax(g,t+c[i][j]);
		return g++;
	}
	int play(vector <string> costs){
		R=costs.size();C=costs[0].length();
		for(int i=0;i<R;i++)
			for(int j=S[i][0]=0;j<C;j++)S[i][j+1]=S[i][j]+(c[i][j]=costs[i][j]-'0');
		int ans=INF;
		for(int i=0;i<C;i++)cmin(ans,dfs(0,i,i));
		return ans;
	}
};
