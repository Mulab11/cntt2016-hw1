#include <vector>
#include <cstdio>
using namespace std;
class PolygonTraversal{
public:
	long long f[1<<18][19];
	int l[19],r[19];
	long long count(int N, vector <int> points){
		int T=(1<<N)-1,x;
		for(int i=points.size();i--;)T-=1<<(points[i]=(points[i]-points[0]+N)%N);
		T+=1<<(x=points[points.size()-1]);
		for(int S=1;S<1<<N;S++)if((S&T)==S){
			for(int i=1;i<N;i++)l[i]=S>>i&1?l[i-1]:i;
			for(int i=N-1;i;i--)r[i]=S>>i&1?r[i+1]:i;
			for(int i=0;i<N;i++){
				f[S][i+1]=f[S][i];
				if(S>>i&1)f[S][i+1]+=S==(1<<i)?l[i]&&r[i]:(r[i]>i?f[S-(1<<i)][N]:0)+f[S-(1<<i)][l[i]]-f[S-(1<<i)][r[i]];
			}
		}
		return f[T][x+1]-f[T][x];
	}
};
