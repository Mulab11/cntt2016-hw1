#include <vector>
#define MOD 1000000007
using namespace std;
class DefectiveAddition{
public:
	int f[60][3];
	int count(vector <int> cards, int n){
		int m=cards.size(),x=0,ans=0;
		for(int i=0;i<m;i++)x^=++cards[i];
		for(int j=29;j>=0&&(x>>j+1)==(n>>j+1);j--){
			f[m][0]=f[m][1]=0;f[m][2]=1;
			for(int i=m-1;i>=0;i--){
				for(int k=0;k<3;k++)f[i][k]=(1ll*cards[i]%(1<<j)*f[i+1][k]+(k<2&&(cards[i]>>j&1)?(1ll<<j)*f[i+1][!k]:0))%MOD;
				if(cards[i]>>j&1)f[i][1]=(f[i][1]+f[i+1][2])%MOD;
			}
			ans=(ans+f[0][(x>>j&1)!=(n>>j&1)])%MOD;
		}
		return ans;
	}
};
