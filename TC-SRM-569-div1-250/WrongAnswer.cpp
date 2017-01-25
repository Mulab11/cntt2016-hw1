#include <vector>
#include <string>
using namespace std;
class TheDevice{
public:
	int f(int x){return x>0?x:0;}
	int minimumAdditional(vector <string> plates){
		int ans=0,tmp,cnt[50][2]={0};
		for(int i=0;i<plates.size();i++)
			for(int j=0;j<plates[i].length();j++)cnt[j][plates[i][j]-'0']++;
		for(int i=0;i<plates[0].length();i++)
			if((tmp=f(1-cnt[i][0])+f(2-cnt[i][1]))>ans)ans=tmp;
		return ans;
	}
};
