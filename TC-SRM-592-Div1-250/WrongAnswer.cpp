#include <string>
using namespace std;
class LittleElephantAndBalls{
public:
	int f(char c){return c=='R'?0:c=='G'?1:2;}
	int getNumber(string S){
		int cnt[3]={0},ans=0;
		for(int i=0;i<S.length();i++){
			for(int j=0;j<3;j++)ans+=cnt[j];
			if(++cnt[f(S[i])]>2)cnt[f(S[i])]=2;
		}
		return ans;
	}
};
