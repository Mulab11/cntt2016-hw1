#include <vector>
#include <bitset>
using namespace std;
class MayTheBestPetWin{
public:
	int calc(vector <int> A, vector <int> B){
		int SA=0,SB=0,ans=1<<30,tmp;
		bitset<1000010>f;f[0]=1;
		for(int i=0;i<A.size();i++)SA+=A[i],SB+=B[i],f|=f<<A[i]+B[i];
		for(int i=0;i<=SA+SB;i++)if(f[i]&&(tmp=i-SA>SB-i?i-SA:SB-i)<ans)ans=tmp;
		return ans;
	}
};
