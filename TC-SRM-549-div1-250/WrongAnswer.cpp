#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class PointyWizardHats{
public:
	struct item{int t,h,r;bool operator<(const item&it)const{int x=h*it.r-r*it.h;return x?x>0:t>it.t;}}a[110];
	multiset<int> S;
	int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius){
		int n=0,ans=0;
		for(int i=0;i<topHeight.size();i++)a[n++]=(item){0,topHeight[i],topRadius[i]};
		for(int i=0;i<bottomHeight.size();i++)a[n++]=(item){1,bottomHeight[i],bottomRadius[i]};
		sort(a,a+n);
		multiset<int>::iterator it;
		for(int i=0;i<n;i++){
			if(a[i].t){
				it=S.lower_bound(a[i].r);
				if(it!=S.begin())S.erase(--it),ans++;
			}
			else S.insert(a[i].r);
		}
		return ans;
	}
};
