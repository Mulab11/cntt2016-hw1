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

#define n	55
#define P	1000000009
#define INF	(1 << 30)

#define Vec	vector<int>
#define Map	map<int, Vec>

int		N, da[n], db[n], dc[n];

int		Cal(Vec G)	{	//对于只有一个点限制计算方案。
		sort(G.begin(), G.end());
		
		if	(G[0])	return	0;
		
		int	ret= 1, now= 0;
		For(i, 2, G.size())	{
			for (; G[now] < G[i-1]; now++);
			ret= 1ll*ret*now%P;
		}
		
		return	ret;
}

int		Work1(int sa, int sb, int sc)	{	//计算Y形的树个数
		Map	A, B, C;
		A[0].push_back(0);
		B[0].push_back(0);
		C[0].push_back(0);
		
		For(i, 1, N)	{
			if	(db[i] - dc[i] == sb - sc)	{	//分三种情况，从而知道归到哪一类
				int y= db[i] + dc[i] - sb - sc;
				if	(y < 0 || y % 2)	return 0;
				y>>= 1;
				
				int x= da[i] + sa - y;
				if	(x % 2)	return	0;
				x>>= 1;
				
				if	(x < 0 || x > sa)	return	0;
				if	(sa-x > y)	return	0;
				
				A[x].push_back(y - (sa-x));
			}
			lf	(da[i] - dc[i] == sa - sc)	{
				int y= da[i] + dc[i] - sa - sc;
				if	(y < 0 || y % 2)	return	0;
				y>>= 1;
				
				int x= db[i] + sb - y;
				if	(x % 2)	return	0;
				x>>= 1;
				
				if	(x < 0 || x > sb)	return	0;
				if	(sb - x > y)	return	0;
				
				B[x].push_back(y - (sb-x));
			}
			lf	(da[i] - db[i] == sa - sb)	{
				int y= da[i] + db[i] - sa - sb;
				if	(y < 0 || y % 2)	return	0;
				y>>= 1;
				
				int x= dc[i] + sc - y;
				if	(x % 2)	return	0;
				x>>= 1;
				
				if	(x < 0 || x > sc)	return	0;
				if	(sc - x > y)	return	0;
				
				C[x].push_back(y - (sc-x));
			}
			else	return	0;
		}
		
		int	ret= 1;
		for (Map::iterator it= A.begin(); it != A.end(); it++)	ret= 1ll*ret*Cal(it->second)%P;	//计数
		for (Map::iterator it= B.begin(); it != B.end(); it++)	ret= 1ll*ret*Cal(it->second)%P;
		for (Map::iterator it= C.begin(); it != C.end(); it++)	ret= 1ll*ret*Cal(it->second)%P;
		
		return	ret;
}

int		Work3(int*da, int*db, int*dc, int sb, int sc){	//计算链形的方案数
		if	(!sb || !sc)	return	0;
	
		Map	B, C;
		B[0].push_back(0);
		C[0].push_back(0);
		B[sb].push_back(0);
		
		For(i, 1, N)	{	//分类
			if	(dc[i] - da[i] == sc)	{
				int y= db[i] + da[i] - sb;
				if	(y < 0 || y % 2)	return	0;
				y>>= 1;
				
				int x= y+sb-da[i];
				if	(x < 0 || x > sb)	return	0;
				B[x].push_back(y);
			}
			lf	(db[i] - da[i] == sb)	{
				int y= dc[i] + da[i] - sc;
				if	(y < 0 || y % 2)	return	0;
				y>>= 1;
				
				int x= y+sc-da[i];
				if	(x < 0 || x > sc)	return	0;
				C[x].push_back(y);
			}
			else	return	0;
		}
		
		int	ret= 1;
		for (Map::iterator it= B.begin(); it != B.end(); it++)	ret= 1ll*ret*Cal(it->second)%P;
		for (Map::iterator it= C.begin(); it != C.end(); it++)	ret= 1ll*ret*Cal(it->second)%P;
		
		return	ret;
}

inline	void	Plu(int&a,int b){
		a+=b;
		if  (a>=P)	a-=P;
}

int		Work2(int*da, int*db, int*dc){
		int sb1= INF, sb2= INF, sc1= INF, sc2= INF;
		
		For(i, 1, N)	{
			sb1= min(sb1, da[i] + db[i]);
			sb2= min(sb2, abs(da[i] - db[i]));
			
			sc1= min(sc1, da[i] + dc[i]);
			sc2= min(sc2, abs(da[i] - dc[i]));
		}
		
		int	ret= 0;
		Plu(ret, Work3(da, db, dc, sb1, sc1));
		Plu(ret, Work3(da, db, dc, sb1, sc2));
		Plu(ret, Work3(da, db, dc, sb2, sc1));
		Plu(ret, Work3(da, db, dc, sb2, sc2));
		
		return	ret;
}

class	UnknownTree{
	public:
		int 	getCount(vector <int> A, vector <int> B, vector <int> C){
			N= A.size();
			For(i, 1, N)	da[i]= A[i-1], db[i]= B[i-1], dc[i]= C[i-1];
			
			int	p= 1;
			For(i, 2, N)	if	(da[i] + db[i] + dc[i] < da[p] + db[p] + dc[p])	p= i;	//找出到三点距离和最小的点p作为根

			int	Ans= 0;
			Plu(Ans, Work1(da[p], db[p], dc[p]));//	printf("# %d\n", Work1(da[p], db[p], dc[p]));
			Plu(Ans, Work2(da, db, dc));//	printf("# %d\n", Work2(da, db, dc));
			Plu(Ans, Work2(db, da, dc));//	printf("# %d\n", Work2(db, da, dc));
			Plu(Ans, Work2(dc, da, db));//	printf("# %d\n", Work2(dc, da, db));
			
			return	Ans;
		}
};