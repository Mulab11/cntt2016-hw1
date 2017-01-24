#include <string>
using namespace std;
class GooseTattarrattatDiv1{
public:
	int fa[26],c[26],s[26],m[26];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	int getmin(string S){
		for(int i=0;i<26;i++)fa[i]=i,c[i]=s[i]=m[i]=0;
		for(int i=S.length();i--;)c[S[i]-'a']++;
		for(int i=0;i<26;i++)s[i]=m[i]=c[i];
		for(int i=0,j=S.length()-1,fi,fj;i<j;i++,j--)
			if((fi=find(S[i]-'a'))!=(fj=find(S[j]-'a')))fa[fi]=fj,s[fj]+=s[fi],m[fi]>m[fj]?m[fj]=m[fi]:1;
		int ans=0;
		for(int i=0;i<26;i++)if(fa[i]==i)ans+=s[i]-m[i];
		return ans;
	}
};
