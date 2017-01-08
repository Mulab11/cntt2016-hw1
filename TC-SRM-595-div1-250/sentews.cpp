#include<algorithm>
#include<vector>
using namespace std;
class LittleElephantAndIntervalsDiv1
{
	public:
	long long getNumber(int M, vector <int> L, vector <int> R)
	{
	bool vis[55]={};int id[1111]={};
int m=L.size();
for(int i=0;i<m;i++)
	for(int j=L[i]-1;j<R[i];j++)
		id[j]=i+1;
int codeforces=0;
for(int i=0;i<M;i++)
	vis[id[i]]=1;
for(int i=1;i<=m;i++)
	if(vis[i])
		codeforces++;
return 1LL<<codeforces;
	}
};
