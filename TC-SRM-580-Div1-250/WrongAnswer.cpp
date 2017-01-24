#include <vector>
#include <algorithm>
using namespace std;
class EelAndRabbit{
public:
	int nums[60],cnt,sum[60],max[60];
	struct range{int L,R;bool operator<(const range&r)const{return R<r.R;}}a[60];
	int getmax(vector <int> l, vector <int> t){
		for(int i=0;i<l.size();i++)nums[cnt++]=t[i];
		sort(nums,nums+cnt);cnt=unique(nums,nums+cnt)-nums;
		for(int i=0;i<l.size();i++)a[i]=(range){lower_bound(nums,nums+cnt,t[i])-nums,upper_bound(nums,nums+cnt,t[i]+l[i])-nums};
		sort(a,a+l.size());
		for(int i=0,r=1;r<=cnt;r++)
			for(max[r]=max[r-1];i<l.size()&&a[i].R<=r;i++)
				for(int j=a[i].L;j<a[i].R;j++)++sum[j]>max[r]?max[r]=sum[j]:1;
		int ans=0;
		for(int i=0;i<=cnt;i++)sum[i]+max[i]>ans?ans=sum[i]+max[i]:1;
		return ans;
	}
};
