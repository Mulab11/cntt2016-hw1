#include <vector>
#define INF 100000000
using namespace std;
class SpellCards{
public:
	int f[2][60];
	void cmax(int&a,int b){b>a?a=b:1;}
	int maxDamage(vector <int> level, vector <int> damage){
		int n=level.size(),ans=0;
		for(int p=0;p<n;p++){
			for(int i=0;i<n;i++)f[0][i]=i?-INF:0,f[1][i]=-INF;
			for(int i=(p+n-1)%n;i!=p;i=(i+n-1)%n){
				for(int j=0;j<n;j++)cmax(f[1][j+1],f[0][j]),j>=level[i]-1?cmax(f[1][j-level[i]+1],f[0][j]+damage[i]),1:1;
				for(int j=0;j<n;j++)f[0][j]=f[1][j],f[1][j]=-INF;
			}
			for(int i=level[p]-1;i<n;i++)cmax(ans,f[0][i]+damage[p]);
		}
		return ans;
	}
};
