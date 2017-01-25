// FST:Two pointers右指针移动左指针忘记移动
#include <vector>
#include <string>
using namespace std;
class ColorfulChocolates{
public:
	vector<int> a[26];
	int maximumSpread(string chocolates, int maxSwaps){
		for(int i=0;i<chocolates.length();i++)a[chocolates[i]-'A'].push_back(i);
		int ans=0;
		for(int c=0;c<26;c++){ // 枚举最大连续段的字符A~Z
			int r=0,n=a[c].size(),sum=0;
			for(int i=0;i<n;i++)a[c][i]-=i; // 将下标减i，方便处理
			for(int l=0;l<n;l++){ // 枚举区间
				for(;r<n&&sum<=maxSwaps;r++){
					if(r-l>ans)ans=r-l; // 更新答案ans
					sum+=a[c][r]-a[c][l+r>>1]; // 更新最小交换次数sum
				}
				if(sum<=maxSwaps&&r-l>ans)ans=r-l; // 更新答案ans
				sum+=a[c][l]-a[c][l+r>>1]; // 更新最小交换次数sum
			}
		}
		return ans;
	}
};
