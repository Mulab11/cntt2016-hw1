#include <vector>
#define MOD 1000000007
using namespace std;
class LISNumber{
public:
	int C[1300][1300];
	int count(vector <int> cardsnum, int K){
		int f[1300]={0,1},S=*C[0]=*C[1]=C[1][1]=1;
		for(int i=0;i<cardsnum.size();i++){
			int g[1300]={0},a=cardsnum[i];
			for(int j=S+1;j<=S+a;j++)
				for(int k=*C[j]=1;k<=j;k++)C[j][k]=(C[j-1][k-1]+C[j-1][k])%MOD;
			for(int j=0;j<=S;j++)if(f[j])
				for(int k=0;k<=j&&k<=a;k++)g[j+a-k]=(g[j+a-k]+f[j]*(long long)C[j][k]%MOD*C[a+S-j-1][a-k])%MOD;
			S+=a;
			for(int j=0;j<=S;j++)f[j]=g[j];
		}
		return f[K];
	}
};
