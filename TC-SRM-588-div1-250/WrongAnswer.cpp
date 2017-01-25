#include <vector>
#include <algorithm>
using namespace std;
class GUMIAndSongsDiv1{
public:
	struct item{int d,t;bool operator<(const item&it)const{return t<it.t;}}a[51];
	int f[51][51];
	int min(int a,int b){return a<b?a:b;}
	int maxSongs(vector <int> duration, vector <int> tone, int T){
		int n=tone.size(),ans=0;
		for(int i=0;i<n;i++)a[i]=(item){duration[i],tone[i]};
		sort(a,a+n);
		for(int i=n-1;i>=0;i--){
			for(int j=1;i+j<=n;j++){
				if(j==1)f[i][j]=i<n-1?min(a[i].d,a[i+1].t-a[i].t+f[i+1][j]):a[i].d;
				else if(i+j==n)f[i][j]=a[i].d+a[i+1].t-a[i].t+f[i+1][j-1];
				else f[i][j]=min(f[i+1][j],a[i].d+f[i+1][j-1])+a[i+1].t-a[i].t;
				if(f[i][j]<=T&&j>ans)ans=j;
			}
		}
		return ans;
	}
};
