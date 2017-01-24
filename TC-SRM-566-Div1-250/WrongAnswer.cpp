#include <vector>
using namespace std;
class PenguinSledding{
public:
	long long countDesigns(int n, vector <int> a, vector <int> b){
		long long to[55]={0},deg[55]={0},ans=0;
		for(int i=0;i<a.size();i++){
			to[a[i]]|=1ll<<b[i];deg[a[i]]++;
			to[b[i]]|=1ll<<a[i];deg[b[i]]++;
		}
		for(int i=0;i<a.size();i++)ans+=__builtin_popcountll(to[a[i]]&to[b[i]]); // 三个点连成环的情况
		ans=ans/3+1-n-a.size(); // 零图及单边的情况
		for(int i=1;i<=n;i++)ans+=1ll<<deg[i]; // 一个点向其它点连的情况
		return ans;
	}
};
