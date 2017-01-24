#include <vector>
#include <algorithm>
using namespace std;
class TomekPhone{
public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes){
		std::sort(frequencies.begin(),frequencies.end());
		int cnt[52]={0},ans=0;
		for(int i=0;i<keySizes.size();i++)cnt[keySizes[i]]++;
		for(int i=50;i;i--)cnt[i]+=cnt[i+1];
		for(int i=frequencies.size()-1,j=1;i>=0;i--){
			while(j<51&&!cnt[j])++j;
			if(j==51)return -1;
			ans+=frequencies[i]*j;--cnt[j];
		}
		return ans;
	}
};
