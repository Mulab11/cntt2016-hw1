#include <vector>
#include <algorithm>
using namespace std;
class BinPacking{
public:
	int solve(vector<int>a,int i){
		int j=a.size()-1,c=0;
		while(i<=j){
			while(i<j&&a[i]+a[j]>300)j--,c++;
			c++;i++;j--;
		}
		return c;
	}
	int minBins(vector <int> item){
		sort(item.begin(),item.end());
		int ans=solve(item,0),tmp;
		for(int i=3;i<=item.size();i+=3){
			if(i==item.size()&&item[i-1]==100&&i/3<ans)ans=i/3;
			else if(item[i-1]==100&&(tmp=i/3+solve(item,i))<ans)ans=tmp;
		}
		return ans;
	}
};
