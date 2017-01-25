#include <vector>
#include <string>
#define INF 23333
using namespace std;
class ColorfulWolves{
public:
	int N,G[60][60],D[60]; // N:点数 G[i][j]:从i到j至少要删的边数 D[i]:从0到i至少要删的边数
	bool vis[60];
	int getmin(vector <string> colormap){
		N=colormap.size();
		for(int i=0;i<N;i++){
			vis[i]=0;D[i]=INF;
			int k=0;
			for(int j=0;j<N;j++){
				if(colormap[i][j]=='Y')G[i][j]=k++; // i->j需要删的边数等于编号比j小的边数
				else G[i][j]=INF;
			}
		}
		// 求0到N-1的最短路
		D[0]=0;
		while(!vis[N-1]){ 
			int k=N-1;
			for(int i=0;i<N;i++)if(!vis[i]&&D[i]<D[k])k=i;
			vis[k]=1;
			for(int i=0;i<N;i++)if(!vis[i]&&D[k]+G[k][i]<D[i])D[i]=D[k]+G[k][i];
		}
		return D[N-1]>=INF?-1:D[N-1];
	}
};
