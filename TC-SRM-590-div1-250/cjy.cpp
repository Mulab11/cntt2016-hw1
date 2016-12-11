#include<bits/stdc++.h>
#define XQJ while(i<n-1&&a[i]=='.')i++;while(j<n-1&&b[j]=='.')j++;
#define GG return"Impossible";
using namespace std;
int i,j,n;
class FoxAndChess
{
	public:
		string ableToMove(string a,string b)
		{
			n=a.size();
			while(i<n&&j<n)//暴力判断是否可以匹配			
			{
				XQJ
				if(a[i]!=b[j]||i!=j&&((a[i]=='L')^(i>j)))GG
				i++;j++;
			}
			XQJ
			if(max(a[i],b[j])>='L')GG
			return"Possible";
		}
};
