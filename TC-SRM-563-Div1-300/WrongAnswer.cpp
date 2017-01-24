#include <string>
#include <cstdio>
using namespace std;
class FoxAndHandle{
public:
	string lexSmallestName(string S){
		string H;
		int n=S.length(),c[26]={0},g[26]={0},q[26]={0},l=0,r=0,tot=0;
		bool flag=0;
		for(int i=0;i<n;i++)c[S[i]-='a']++;
		for(int i=0;i<26;i++)tot+=(g[i]=c[i]/2);
		while(tot--){
			for(;r<n&&!flag;r++)q[S[r]]++,--c[S[r]]<g[S[r]]?flag=1:1;
			for(int i=0;i<26;i++)if(g[i]&&q[i]){
				while(S[l]!=i)q[S[l++]]--;
				H.push_back(S[l]+'a');
				c[S[l]]<g[S[l]]--?flag=0:1,q[S[l++]]--;
				break;
			}
		}
		return H;
	}
};
