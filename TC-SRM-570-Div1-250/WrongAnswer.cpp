#include <vector>
using namespace std;
class RobotHerb{
public:
	long long getdist(int T, vector <int> a){
		int vx[4]={1,0,-1,0},vy[4]={0,1,0,-1},d=0;
		long long x=0,y=0;
		for(int t=0;t<4;t++)
			for(int i=0;i<a.size();i++)x+=a[i]*vx[d]*(T/4ll+(t<T%4)),y+=a[i]*vy[d]*(T/4ll+(t<T%4)),d=(d+a[i])%4;
		return (x<0?-x:x)+(y<0?-y:y);
	}
};
