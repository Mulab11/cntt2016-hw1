#include<algorithm>
#include<vector>
using namespace std;
int getsum(int l,int r){return (l+r)*(r-l+1)/2;}
class AlternateColors2
{
public:
	long long countWays(int n, int k)
	{
		long long ans=0;
		if(k%3==1&&n-k-2>=0)ans+=getsum(1,n-k-1);//rgbrgbrgbrgb......
		for(int i=1;i*3<k;i++)//rgb cnt
			ans+=(n-3*i-1)/2*2;//rgbrgbrgrgrrrr.....  rgbrgbrbrbrrrr.....
		ans+=(k+2)/3;//rgbrgbrgbrrrr.....  include rrrrrrrrrrrr......
		ans+=(k-1)/2*2;//rgrgrgrgrrrr......  rbrbrbrbrrrr......
		for(int i=0;i*3<k;i++)//rgbrgbrgbrgrgrg....   rgbrgbrgbrbrbrb.... include rgrgrgrgrg.....  rbrbrbrb....
			if(k-i*3&1)
				ans+=2*(n-k+1>>1);
		return ans;
	}
};
