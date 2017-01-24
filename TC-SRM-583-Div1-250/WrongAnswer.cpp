#include <vector>
using namespace std;
class TravelOnMars{
public:
	int N,r[60];
	void cmin(int&a,int b){b<a?a=b:1;}
	void cmax(int&a,int b){b>a?a=b:1;}
	int minTimes(vector <int> range, int startCity, int endCity){
		N=range.size();
		for(int i=0;i<N;i++)r[i]=range[(i+startCity)%N];
		endCity=(endCity-startCity+N)%N;
		int L=0,R=N,ll=r[0],rr=N-r[0],ans=0; // 当前经过的区间为[0,L],[R,N)，ans为步数
		while(endCity>L&&endCity<R){
			int lmax=ll,rmin=rr;++ans;
			while(L<ll){
				if(++L==endCity)return ans;
				cmax(lmax,L+r[L]);cmin(rmin,L-r[L]+N);
			}
			while(R>rr){
				if(--R==endCity)return ans;
				cmax(lmax,R+r[R]-N);cmin(rmin,R-r[R]);
			}
			L=ll;ll=lmax;R=rr;rr=rmin;
		}
		return ans;
	}
};
