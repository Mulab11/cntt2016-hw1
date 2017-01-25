#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class ShoutterDiv1{
public:
	int n,s[2510],t[2510],lmin[10000],rmax[10000],dl[10000],dr[10000];
	int num(char a,char b,char c,char d){return(((a-'0')*10+b-'0')*10+c-'0')*10+d-'0';}
	int min(int a,int b){return a<b?a:b;}
	int max(int a,int b){return a>b?a:b;}
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1){
		int smax=-1,tmin=10000;
		for(int i=n=0;i<s1.size();i++)
			for(int j=0;j<s1[i].length();j++,n++)
				smax=max(smax,s[n]=num(s1000[i][j],s100[i][j],s10[i][j],s1[i][j])),
				tmin=min(tmin,t[n]=num(t1000[i][j],t100[i][j],t10[i][j],t1[i][j]));
		if(smax<=tmin)return 0;
		for(int i=0;i<n;i++)s[i]=max(s[i],tmin),t[i]=min(t[i],smax);
		for(int i=tmin;i<=smax;i++)lmin[i]=rmax[i]=i;
		for(int i=0;i<n;i++)lmin[t[i]]=min(lmin[t[i]],s[i]),rmax[s[i]]=max(rmax[s[i]],t[i]);
		for(int i=smax-1;i>=tmin;i--)lmin[i]=min(lmin[i],lmin[i+1]);
		for(int i=tmin+1;i<=smax;i++)rmax[i]=max(rmax[i],rmax[i-1]);
		int ans=0,sum=0;dl[tmin]=dr[smax]=0;
		for(int i=tmin;i<smax;i=rmax[i],ans++)if(rmax[i]==i)return-1;
		for(int i=tmin+1;i<=smax;i++)dl[i]=1+dl[lmin[i]];
		for(int i=smax-1;i>=tmin;i--)dr[i]=1+dr[rmax[i]];
		for(int i=0;i<n;i++)sum+=min(ans,dl[s[i]]+dr[t[i]]);
		return sum;
	}
};
