#include <vector>
#include <string>
using namespace std;
class ThreeColorability{
public:
	int H,W;
	bool G[110][110],E[110][110],vis[110],val[110];
	int f(int c){return c==0?'N':c==1?'Z':c=='N'?0:1;}
	bool fill(int i,int c){
		vis[i]=1;val[i]=c;
		for(int j=0;j<=H+W;j++)
			if(G[i][j]&&(vis[j]&&val[j]!=(c^E[i][j])||!vis[j]&&!fill(j,c^E[i][j])))return 0;
		return 1;
	}
	vector <string> solve(vector <string> cells){
		vector<string>ans;
		H=cells.size();W=cells[0].size();val[0]=f(cells[0][0]);
		for(int i=0;i<=H+W;vis[i++]=0)
			for(int j=0;j<=H+W;j++)G[i][j]=0;
		for(int i=1;i<H;i++)
			for(int j=1;j<W;j++)if(cells[i][j]!='?')G[i+W][j]=G[j][i+W]=1,E[i+W][j]=E[j][i+W]=f(cells[i][j])^val[0];
		for(int i=1;i<W;i++)if(cells[0][i]!='?'&&!fill(i,f(cells[0][i])))return ans;
		for(int i=1;i<H;i++)if(cells[i][0]!='?'&&!fill(i+W,f(cells[i][0])))return ans;
		for(int i=1;i<W;i++)if(!vis[i]&&!fill(i,0))return ans;
		for(int i=1;i<H;i++)if(!vis[i+W]&&!fill(i+W,0))return ans;
		for(int i=0;i<H;i++)
			for(int j=0;j<W;j++)cells[i][j]=='?'?cells[i][j]=f(val[i?i+W:0]^val[j]^val[0]):1;
		return cells;
	}
	vector <string> lexSmallest(vector <string> cells){
		if(cells[0][0]=='?'){
			cells[0][0]='N';
			vector<string>ans=solve(cells);
			if(ans.size())return ans;
			cells[0][0]='Z';
		}
		return solve(cells);
	}
};
