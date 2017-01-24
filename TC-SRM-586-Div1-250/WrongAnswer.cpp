// FST:把y集合从n个点扩充成2n-1个点的时候忘记令n=n*2-1
#include <vector>
#include <algorithm>
using namespace std;
class PiecewiseLinearFunction{
public:
	int maximumSolutions(vector <int> Y){
		int y[110],a[110]={0},n=0;
		for(int i=0;i<Y.size();i++){
			y[n++]=Y[i]*2;
			if(n>1&&y[n-2]==y[n-1])return-1;
		}
		sort(y,y+n);n=unique(y,y+n)-y;
		for(int i=n-1;i;i--)y[i*2-1]=y[i-1]+(long long)(y[i*2]=y[i])>>1;n=n*2-1;
		for(int i=0,x;i<Y.size();i++)a[x=lower_bound(y,y+n,Y[i]*2)-y]++,a[x+1]--;
		for(int i=1;i<Y.size();i++){
			int l=Y[i-1]*2,r=Y[i]*2,t;
			if(l>r)t=l,l=r,r=t;
			a[lower_bound(y,y+n,l)-y+1]++;
			a[lower_bound(y,y+n,r)-y]--;
		}
		int c=0,m=0;
		for(int i=0;i<n;i++)if((c+=a[i])>m)m=c;
		return m;
	}
};
