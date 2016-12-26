#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;

/*
判断是否相对位置不变，并且对应的L只能向左移，对应的R只能向右移即可。
*/

class FoxAndChess{
public:
	string ableToMove(string a,string b){
		int n=a.size(),i=0,j=0;
		while (i<n){
			while (i<n&&a[i]=='.') i++;
			while (j<n&&b[j]=='.') j++;
			if (i<n){
				if (a[i]=='L'){
					if (b[j]!='L'||j>i) return "Impossible";
				}
				else if (b[j]!='R'||j<i) return "Impossible";
				i++,j++;
			}
			else if (j!=n) return "Impossible";
		}
		while (j<n&&b[j]=='.') j++;
		if (j!=n) return "Impossible";
		return "Possible";
	}
};
