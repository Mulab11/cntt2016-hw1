#include <vector>
#include <algorithm>
using namespace std;
class SpaceWarDiv1{
public:
	int n;
	struct item{int ty,val;long long cnt;bool operator<(const item&it)const{return val<it.val||val==it.val&&ty<it.ty;}}items[110];
	bool check(long long m){
		long long s=0;
		for(int i=0;i<n;i++)items[i].ty?(s-=m)<0?s=0:1:s+=items[i].cnt;
		return!s;
	}
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount){
		n=0;
		for(int i=0;i<magicalGirlStrength.size();i++)items[n++]=(item){1,magicalGirlStrength[i],1};
		for(int i=0;i<enemyCount.size();i++)items[n++]=(item){0,enemyStrength[i],enemyCount[i]};
		sort(items,items+n);
		long long left=-1,right=1ll<<53,mid;
		while(right-left>1){
			mid=left+right>>1;
			if(check(mid))right=mid;
			else left=mid;
		}
		return right==1ll<<53?-1:right;
	}
};
