#include <string>
using namespace std;
class NewArenaPassword{
public:
	int minChange(string oldPassword, int K){
		int L=oldPassword.length(),ans=0,cnt[128]={0},maxc;
		for(int i=0;i<L-K;i++){
			maxc=0;
			for(int j=i;j<L;j+=L-K,ans++)
				if(++cnt[oldPassword[j]]>maxc)maxc=cnt[oldPassword[j]];
			ans-=maxc;
			for(int j=i;j<L;j+=L-K)cnt[oldPassword[j]]=0;
		}
		return ans;
	}
};
