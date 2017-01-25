// FST:问题考虑不周到，没注意到若干轮之后原本非最优的会变成最优
#include <vector>
#include <string>
using namespace std;
class StringGame{
public:
	vector <int> getWinningStrings(vector <string> S){
		int cnt[50][26]={0};
		vector<int> ans;
		for(int i=0;i<S.size();i++)
			for(int j=0;j<S[i].length();j++)cnt[i][S[i][j]-'a']++;
		for(int i=0;i<S.size();i++){
			long long A=(1ll<<S.size())-1;
			int P[26],tot=26;
			for(int j=0;j<26;j++)P[j]=j;
			for(int j=0;j<tot&&A!=1ll<<i;j++){
				int m=0;
				for(int k=0;A>>k;k++)if((A>>k&1)&&cnt[k][P[j]]>m)m=cnt[k][P[j]];
				if(cnt[i][P[j]]==m){
					for(int k=0;A>>k;k++)if((A>>k&1)&&cnt[k][P[j]]<m)A-=1ll<<k;
					P[j]=P[--tot];j=-1;
				}
			}
			if(A==1ll<<i)ans.push_back(i);
		}
		return ans;
	}
};
