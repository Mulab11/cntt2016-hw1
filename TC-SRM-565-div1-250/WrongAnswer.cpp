#include <vector>
#define INF 10000000000000000ll
using namespace std;
class MonstersValley{
public:
	long long f[2][110];
	void cmax(long long&a,long long b){b>a?a=b:1;}
	int minimumPrice(vector<long long> dread, vector <int> price){
		int n=dread.size();
		for(int i=0;i<=n*2;i++)f[0][i]=i?-INF:0,f[1][i]=-INF;
		for(int i=0;i<n;i++){
			for(int j=0;j<=n*2;j++)f[0][j]>=dread[i]?cmax(f[1][j],f[0][j]),1:1,cmax(f[1][j+price[i]],f[0][j]+dread[i]);
			for(int j=0;j<=n*2;j++)f[0][j]=f[1][j],f[1][j]=-INF;
		}
		for(int i=0;;i++)if(f[0][i]>=0)return i;
	}
};
