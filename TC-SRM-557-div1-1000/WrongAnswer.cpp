#include <vector>
using namespace std;
class XorAndSum{
public:
	long long maxSum(vector<long long> number){
		int n=number.size();
		long long a[60],x,t,ans=0;
		for(int i=n-1;i>=0;i--){ // 高斯消元
			for(int j=0;j<i;j++)number[j]>number[i]?t=number[i],number[i]=number[j],number[j]=t:1;
			for(int j=0;j<i;j++)(number[j]^number[i])<number[j]?number[j]^=number[i]:1;
		}
		for(int i=0,l,r;i<n;i++){ // 用拟阵的思想，每次贪心选取最大的独立集
			a[i]=x=t=l=0; // a[i]:选哪些数xor x:xor的结果 t:a[i]被a[0,i)消的结果
			for(r=1;r<=i&&a[i-r]<(1ll<<r);r++);r--; // r:用a[0,i)可以组合成2^r以内的所有数
			for(int j=n-1;j>=0;j--){ // 从大到小决定a[i]的每一位
				if((x^number[j])>x)x^=number[j],a[i]|=1ll<<j; // 贪心取尽可能大
				while(l<i&&a[l]>=(1ll<<j+1))l++; // l:a[l]的最高位不超过j
				if(l==i||a[l]<(1ll<<j)){ // j这一位为空
					if(j==r&&(a[i]>>j)==(t>>j))x^=number[j],a[i]^=1ll<<j; // 如果不改变决策就会不独立（t=x），就改变决策
				}
				else if((a[i]>>j&1)!=(t>>j&1))t^=a[l]; // j这一位不为空，用a[l]消使得t和x这一位相同
			}
			ans+=x; // 将最大的可选的x加入答案
			for(int j=0;j<i;j++)if((a[i]^a[j])<a[i])a[i]^=a[j]; // 前面部分消元
			for(int j=i;j&&a[j-1]<a[j];j--)t=a[j],a[j]=a[j-1],a[j-1]=t;
		}
		return ans;
	}
};
