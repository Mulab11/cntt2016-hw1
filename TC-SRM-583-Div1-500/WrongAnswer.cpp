#include <vector>
#include <string>
using namespace std;
class TurnOnLamps{
public:
	int minimize(vector <int> roads, string initState, string isImportant){
		int n=roads.size()+1,cnt=0;
		bool s[60]={0};
		for(int i=n-1;i;i--){
			if(isImportant[i-1]=='1'&&initState[i-1]-'0'==s[i])s[i]^=1,cnt++;
			s[roads[i-1]]^=s[i];
		}
		return(cnt+1)/2;
	}
};
