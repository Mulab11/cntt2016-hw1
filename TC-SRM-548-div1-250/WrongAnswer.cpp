#include <vector>
using namespace std;
class KingdomAndTrees{
public:
	int n,a[60];
	bool check(int X){
		int b=0;
		for(int i=0;i<n;i++){
			b=a[i]-X<b+1?b+1:a[i]-X;
			if(b>a[i]+X)return 0;
		}
		return 1;
	}
	int minLevel(vector <int> heights){
		n=heights.size();
		for(int i=0;i<n;i++)a[i]=heights[i];
		int left=-1,right=1000000001,mid;
		while(right-left>1){
			mid=(left+right)/2;
			if(check(mid))right=mid;
			else left=mid;
		}
		return right;
	}
};
