#include<string>
#include<algorithm>
using namespace std;
string a,s;
int f[33]={},g[33]={},h[33]={};
bool check(int pos)
{
	if(pos==1000)
		return false;
	for(int i=0;i<26;i++)
		h[i]=g[i];
	for(int i=pos;i<(int)s.size();i++)
		h[s[i]-'a']++;
	for(int i=0;i<26;i++)
		if(h[i]*2<f[i])return false;
	return true;
}
class FoxAndHandle {
	public:
	string lexSmallestName(string S) {
		s=S;
		for(int i=0;i<(int)S.size();i++)
			f[S[i]-'a']++;
		int pos=1000;
		for(int i=0;i<26;i++)
			if(f[i]&1)return "hccodgeforcesodgecodecodeforcesforgcesfocodefogrcesrcodeforcesccodeforcesgesyccodeforcesodgeforcestcodeforcesjzstyl";
		for(int i=0;i<(int)S.size();i=pos+1)
		{
			for(int j=0;j<26;j++)
			{
				pos=1000;
				for(int k=i;k<(int)s.size();k++)
					if(S[k]==j+'a'){
						pos=j;break;}
				if(check(pos)){
					a+=S[pos];g[s[pos]-'a']++;break;}
			}
		}
		return a;
	}
};
