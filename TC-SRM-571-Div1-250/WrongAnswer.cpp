#include <vector>
#include <string>
#include <cstdio>
using namespace std;
class FoxAndMp3{
public:
	int N,tot;
	vector<string> ans;
	void dfs(int x){
		char op[20];
		sprintf(op,"%d.mp3",x);
		ans.push_back(op);--tot;
		for(int i=0;i<=9;i++){
			if(x*10ll+i>N||!tot)return;
			dfs(x*10+i);
		}
	}
	vector <string> playList(int n){
		N=tot=n;if(tot>50)tot=50;
		for(int i=1;i<=9;i++)if(i<=n&&tot)dfs(i);
		return ans;
	}
};
