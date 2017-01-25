#include <vector>
#include <string>
#define INF 10000000
using namespace std;
class Egalitarianism{
public:
	int N,D[60][60];
	void cmin(int&a,int b){b<a?a=b:1;}
	int maxDifference(vector <string> isFriend, int d){
		N=isFriend.size();
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)D[i][j]=i==j?0:isFriend[i][j]=='Y'?d:INF;
		for(int k=0;k<N;k++)
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)cmin(D[i][j],D[i][k]+D[k][j]);
		int ans=0;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)cmin(ans,-D[i][j]);
		return ans<=-INF?-1:-ans;
	}
};
