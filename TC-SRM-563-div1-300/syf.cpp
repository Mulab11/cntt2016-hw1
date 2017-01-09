//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define	n	55

int		N, rev[n], cnt[n][n];
string	S;

bool	check(string T)	{	//贪心匹配
		int now= 0;
		For(i, 1, N)	{
			if	(S[i-1] == T[now])	now++;
			if	(now == T.length())	{
				For(j, 0, 25)	if	(cnt[i][j] < rev[j])	return	0;
				return	1;
			}
		}
		return	0;
}

class	FoxAndHandle{
	public:
		string lexSmallestName(string S){
			string T= "";
			
			N= S.length();
			::S= S;
			
			Rep(i, N, 1)	{
				For(j, 0, 25)	cnt[i][j]= cnt[i+1][j];
				cnt[i][S[i-1] - 'a']++;
			}
			
			For(i, 1, N)	rev[S[i-1] - 'a']++;
			For(j, 0, 25)	rev[j]>>= 1;
			
			For(i, 1, N/2)	{	//逐位确定
				string	tmp= T;
				
				For(j, 0, 25)	if	(rev[j]){
					T= tmp + char('a' + j);
					if	(check(T))	{
						rev[j]--;	break;
					}
				}
			}
			
			return	T;
		}
};