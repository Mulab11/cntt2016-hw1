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

int		N, M;

vector<string>	Ans;

void	Push(int x){
		string	s= "";
		for (; x; x/= 10)	s= char('0' + x%10) + s;
		Ans.push_back(s + ".mp3");
		++M;
}

void	Work(int x){
		if	(M == 50)	return;
		Push(x);
		For(i, 0, 9)	if	(10ll*x + i <= N)	Work(10*x+i);	//按照字典序从小到大搜索，并判断合法性。
}

class	FoxAndMp3{
	public:
		vector <string> playList(int N){
			::N= N;
			For(i, 1, 9)	if	(i <= N)	Work(i);
			return	Ans;
		}
};