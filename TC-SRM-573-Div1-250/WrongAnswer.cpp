#include <vector>
#include <set>
using namespace std;
class TeamContest{
public:
	int worstRank(vector <int> strength){
		int s=1<<30,t=0,ans=1;
		multiset<int> S;
		for(int i=0;i<3;i++)strength[i]>t?t=strength[i]:1,strength[i]<s?s=strength[i]:1;
		s+=t;
		for(int i=3;i<strength.size();i++)S.insert(strength[i]);
		while(S.size()>=3){
			multiset<int>::iterator it1,it2,it3;
			it1=S.end();it1--;
			it2=it1;it2--;
			it3=it2;it3--;
			if(*it1+*it3<=s)break;
			it2=it3=S.upper_bound(s-*it1);it3++;
			S.erase(it1);S.erase(it2);S.erase(it3);ans++;
		}
		return ans;
	}
};
