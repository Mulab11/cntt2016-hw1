#include <vector>
#include <string>
using namespace std;
class LittleElephantAndRGB{
public:
	int l[2510],r[2510],lm[2510],rm[2510],cnt[2510],f[2510][2510];
	long long getNumber(vector <string> list, int minGreen){
		string S;
		for(int i=0;i<list.size();i++)
			for(int j=0;j<list[i].length();j++)S.push_back(list[i][j]);
		int n=S.length();
		l[0]=0;lm[0]=-1;r[n]=n;rm[n]=n+1;cnt[n]=0;
		for(int i=1;i<=n;i++)l[i]=S[i-1]=='G'?l[i-1]:i,lm[i]=i-l[i]>=minGreen?i-minGreen:lm[i-1];
		for(int i=n;i--;)r[i]=S[i]=='G'?r[i+1]:i,rm[i]=r[i]-i>=minGreen?i+minGreen:rm[i+1],cnt[i]=cnt[i+1]+n-rm[i]+1;
		for(int i=n;i>=0;i--){
			for(int j=0;j<=n;j++)f[i][j]=i==n?0:f[i+1][j];
			for(int j=i+1;j<rm[i];j++)f[i][(r[i]>j?j:r[i])-i]++;
		}
		for(int j=n;j--;)
			for(int i=0;i<=n;i++)f[i][j]+=f[i][j+1];
		long long ans=0;
		for(int i=0;i<n;i++)
			for(int j=i+1,d;j<=n;j++)ans+=j>=rm[i]?(n-j)*(n-j+1)/2:cnt[j]+f[j][(d=minGreen-j+(l[j]>i?l[j]:i))<0?0:d];
		return ans;
	}
};
