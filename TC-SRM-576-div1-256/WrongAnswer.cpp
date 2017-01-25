#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class ArcadeManao{
public:
	vector<int> ex[60],ey[60];
	int fa[2510];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	int shortestLadder(vector <string> level, int coinRow, int coinColumn){
		int N=level.size(),M=level[0].length();
		for(int i=0;i<N*M;i++)fa[i]=i;
		for(int i=0;i<M;i++){
			int l=0;while(l<N&&level[l][i]!='X')l++;
			if(i<M-1&&level[l][i+1]=='X')fa[find(l*M+i+1)]=find(l*M+i);
			if(l<N)for(int j=l+1;j<N;j++)if(level[j][i]=='X'){
				ex[j-l].push_back(l*M+i);
				ey[j-l].push_back(j*M+i);
				l=j;if(i<M-1&&level[l][i+1]=='X')fa[find(l*M+i+1)]=find(l*M+i);
			}
		}
		for(int i=0;;i++){
			for(int j=0;j<ex[i].size();j++)fa[find(ex[i][j])]=find(ey[i][j]);
			if(find((N-1)*M)==find((coinRow-1)*M+coinColumn-1))return i;
		}
	}
};
