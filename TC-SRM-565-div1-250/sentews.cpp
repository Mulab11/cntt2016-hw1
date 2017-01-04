#include<algorithm>
#include<vector>
using namespace std;
long long f[55][155]={};
int n;
class MonstersValley
{
public:
	int minimumPrice(vector<long long> dread, vector <int> price)
	{
		for(int i=0;i<52;i++)
			for(int j=0;j<152;j++)
				f[i][j]=-1000000000000000LL;
		f[0][0]=0;
		for(int i=1;i<=dread.size();i++)
			for(int j=133;j>=0;j--)
				if(f[i-1][j]<dread[i-1])
					f[i][j+price[i-1]]=max(f[i][j+price[i-1]],f[i-1][j]+dread[i-1]);
				else
					f[i][j+price[i-1]]=max(f[i][j+price[i-1]],f[i-1][j]+dread[i-1]),
					f[i][j]=max(f[i][j],f[i-1][j]);
		for(int i=1;i<=135;i++)
			if(f[dread.size()][i]>0)
				return i;
	}
};
