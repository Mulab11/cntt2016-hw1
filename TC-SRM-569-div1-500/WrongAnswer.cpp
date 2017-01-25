#include <vector>
using namespace std;
class TheJediTest{
public:
	int minimumSupervisors(vector <int> a, int K){
		int n=a.size(),s=0,c=0;
		for(int i=0;i<n;i++){
			if(i==n-1)s+=(c+a[i]+K-1)/K-(c+K-1)/K;
			else if(!c)s+=(a[i]+K-1)/K,c=a[i]%K;
			else if(c+a[i]+a[i+1]<=K)i++,c=0;
			else if(c+a[i]<=K)a[i+1]-=K-c-a[i],c=0;
			else a[i]-=K-c,s+=(a[i]+K-1)/K,c=a[i]%K;
		}
		return s;
	}
};
