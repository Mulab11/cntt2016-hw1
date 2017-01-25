#include <vector>
#include <algorithm>
using namespace std;
class LittleElephantAndIntervalsDiv1{
public:
	int num[110],cnt,f[110];
	int find(int i){return f[i]==i?i:f[i]=find(f[i]);}
	long long getNumber(int M, vector <int> L, vector <int> R){
		M=L.size();cnt=0;
		for(int i=0;i<M;i++)num[cnt++]=L[i],num[cnt++]=++R[i];
		std::sort(num,num+cnt);cnt=std::unique(num,num+cnt)-num;
		for(int i=0;i<cnt;i++)f[i]=i;
		long long ans=1;
		for(int i=M;i--;)if(find(L[i]=std::lower_bound(num,num+cnt,L[i])-num)<(R[i]=std::lower_bound(num,num+cnt,R[i])-num)){
			for(int j=find(L[i]);j<R[i];j=find(j))f[j]=j+1;
			ans<<=1;
		}
		return ans;
	}
};
