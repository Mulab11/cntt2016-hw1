#include <string>
using namespace std;
class FoxAndMountainEasy{
public:
	string possible(int n, int h0, int hn, string history){
		int L=history.length(),d=0,y=0;
		for(int i=0;i<L;i++)history[i]=='U'?++y:--y<d?d=y:1;
		int x=hn-h0-L-y+n;
		return x%2==0&&(x/=2)>=0&&x+L<=n&&h0+x+d>=0?"YES":"NO";
	}
};
