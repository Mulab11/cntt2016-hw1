#include <vector>
#include <string>
using namespace std;
class XorTravelingSalesman{
public:
	int N,Q[60];
	bool vis[60];
	int maxProfit(vector <int> cityValues, vector <string> roads){
		N=roads.size();Q[0]=0;vis[0]=1;
		for(int i=1;i<N;i++)vis[i]=0;
		int head=0,tail=1;
		for(;head<tail;head++)
			for(int i=Q[head],j=0;j<N;j++)if(!vis[j]&&roads[i][j]=='Y')vis[Q[tail++]=j]=1;
		int ans=0;N=tail;
		for(int i=0;i<N;i++)Q[i]=cityValues[Q[i]];
		for(int i=0,t;i<N;i++){
			for(int j=i+1;j<N;j++)if(Q[j]>Q[i])t=Q[i],Q[i]=Q[j],Q[j]=t;
			for(int j=i+1;j<N;j++)if((Q[j]^Q[i])<Q[j])Q[j]^=Q[i];
			if((ans^Q[i])>ans)ans^=Q[i];
		}
		return ans;
	}
};
