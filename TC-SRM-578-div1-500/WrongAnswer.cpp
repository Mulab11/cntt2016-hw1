#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class WolfInZooDivOne{
public:
	int n,m,left[310],right[310];
	void read(vector<string>a,int*b,int&s){
		for(int i=s=*b=0;i<a.size();i++)
			for(int j=0;j<a[i].length();j++)a[i][j]==' '?b[++s]=0:b[s]=b[s]*10+a[i][j]-'0';
		s++;
	}
	int r[310],f[310][310];
	int calc(int i,int j){
		if(i==n)return 1;
		if(f[i][j=i>j?i:j])return f[i][j]-1;
		f[i][j]=(calc(i+1,j)+calc(i==j?i+1:j,r[i]))%MOD;
		return f[i][j]++;
	}
	int count(int N, vector <string> L, vector <string> R){
		n=N;read(L,left,m);read(R,right,m);
		for(int i=0;i<n;i++)r[i]=i+1;
		for(int i=0;i<m;i++)right[i]>=r[left[i]]?r[left[i]]=right[i]+1:1;
		for(int i=1;i<n;i++)r[i-1]>r[i]?r[i]=r[i-1]:1;
		return calc(0,0);
	}
};
