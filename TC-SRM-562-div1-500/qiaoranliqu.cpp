#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 233
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const double pi=acos(-1.0);
int i,j,m,n,p,k,wtot,btot,tot,ID[N],id[N];
double A[N],B[N];
struct Point{
	double x,y;
}w[N],b[N];
inline bool cmp(int a,int b)
{
		return A[a]<A[b];
}
inline bool cmp2(int a,int b)
{
	  	return B[a]<B[b];
}
bitset<N>ls[N][N],r[N][N],E,md,rest;
double cross(Point x,Point y,Point z)
{
		return (y.x-x.x)*(z.y-x.y)-(z.x-x.x)*(y.y-x.y);
}
class CheckerFreeness{
	public:
		string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY)
		{
					string s; int now=0;
					for (i=0;i<(int)whiteX.size();++i) s+=whiteX[i];
					tot=0;
					for (i=0;i<(int)s.length();++i)
					{
							if (s[i]==' ') w[++tot].x=now,now=0;
							else now=now*10+s[i]-'0';
					}
					w[++tot].x=now; now=0;
					s="";
					for (i=0;i<(int)whiteY.size();++i) s+=whiteY[i];
					tot=0;
					for (i=0;i<(int)s.length();++i) 
					{
							if (s[i]==' ') w[++tot].y=now,now=0;
							else now=now*10+s[i]-'0';
					}
					w[++tot].y=now; now=0;
					wtot=tot;
					s="";
					for (i=0;i<(int)blackX.size();++i) s+=blackX[i];
					tot=0;
					for (i=0;i<(int)s.length();++i)
					{
							if (s[i]==' ') b[++tot].x=now,now=0;
							else now=now*10+s[i]-'0';
					}
					b[++tot].x=now; now=0; 
					s="";
					for (i=0;i<(int)blackY.size();++i) s+=blackY[i];
					tot=0;
					for (i=0;i<(int)s.length();++i)
					{
							if (s[i]==' ') b[++tot].y=now,now=0;
							else now=now*10+s[i]-'0';
					}
					b[++tot].y=now; now=0;
					btot=tot;
					//还原出所有点的坐标 
					for (i=1;i<=btot;++i)
						for (j=1;j<=btot;++j)
							if (i!=j)
						{
								for (k=1;k<=wtot;++k)
								{
									double wo=cross(b[i],b[j],w[k]);
									if (wo>0) ls[i][j][k]=1;
									if (wo<0) r[i][j][k]=1;
								}
						}
					//判断每个白色在每条黑色线段的左侧还是右侧 
				   for (i=1;i<=wtot;++i)
				   {
				   		  for (j=1;j<=btot;++j)
				   		  	  A[j]=atan2(b[j].y-w[i].y,b[j].x-w[i].x),ID[j]=j;
				   		  sort(ID+1,ID+btot+1,cmp);
				   		  for (j=1;j<=wtot;++j)
				   		  {
							 	if (i!=j)
							 	B[j]=atan2(w[j].y-w[i].y,w[j].x-w[i].x);
							id[j]=j;
						  }		 
						  sort(id+1,id+wtot+1,cmp2);
						  for (j=1;j<=btot;++j) //枚举一个黑点作为起始点 
						  {	
				   	      		rest=md=E;
				   	      		for (k=1;k<=wtot;++k) if (i!=k) rest[k]=1;
						  		int l=1;
						  		while (l<=wtot)  
						  		{
						  				if (id[l]==i) ++l;
						  				else 
						  				if (B[id[l]]<=A[ID[j]]) ++l;
						  				else 
										break;
								} 
						  		for (k=j+1;k<=btot;++k) 
						  		{
						  				while (l<=wtot)
						  				{
						  						if (id[l]==i) ++l;
						  						else
						  						if (B[id[l]]>=A[ID[k]]) break;
						  						else 
						  						{
						  							rest[id[l]]=0,md[id[l]]=1,++l;
						  						}
						  				}
						  				double wo=cross(b[ID[j]],b[ID[k]],w[i]);
						  				if (wo>0) //判断极角序在某个范围内并在某个点某侧的点是否存在 
						  				{
						  					if (A[ID[k]]-A[ID[j]]>pi)
						  					{
						  							if ((rest&r[ID[j]][ID[k]])!=E)
						  							return "NO";
						  					}
						  					else 
						  					{
						  							if ((md&r[ID[j]][ID[k]])!=E)
						  							{
						  								return "NO";
						  							}
						  					}
						  				}
						  				else if (wo<0)
						  				{
						  					if (A[ID[k]]-A[ID[j]]>pi)
						  					{
						  							if ((rest&ls[ID[j]][ID[k]])!=E)
													return "NO"; 
						  					}
						  					else 
						  					{
						  							if ((md&ls[ID[j]][ID[k]])!=E)
						  							{
						  								return "NO";
						  							}
						  					}
						  				}
						  		}
						  }
				   }
				   return "YES";
		}
}FFT;

int main()
{
	 cout<<FFT.isFree({"219211 1996214 1706774 3634920 909831 1774128 8503"
,"52 2233050 2099138 3380396 1128982 3682525 1483700"
," 763080 487867 8203 1791027 463556 1103323 1406861"
," 6374234 760949 4340236 727393 2073832 1289052 103"
,"8147 4448130 151066 412440 1068735 377239 2677933 "
,"1299598 339843 289973 3707319 555280 230418 431719"},
{"1638083 5698739 3105504 9726902 9745795 5049444 15"
,"80592 3952120 6606668 7460527 7239299 8726128 4913"
,"547 6264100 5701660 8865937 4969114 8014845 327236"
,"1 6389154 9739755 2561669 9412417 5452337 3150506 "
,"5832197 1571976 8779325 3306446 948271 5133709 949"
,"394 6919798 7525636 3568024 6833196 9237472 733313"
,"1 9939064 9720014"},
{"5860334 8007503 7455523 4864927 9573526 2718360 81"
,"12104 6684287 9921506 4840886 5415948 3451454 5320"
,"996 9268757 9261724 8254668 2292750 8035828 233352"
,"1 7676906 5234406 8533320 6562751 4884098 4971897 "
,"5569360 8519168 3100295 9351613 7733878 7579030 32"
,"46775 7297460 8370542 7099759 5782969 2978083 3390"
,"488 7482758 1332401 6094629 9717305 5503121 572842"
,"1 4903563 6331656 2867455 3410007 7751527 7228221 "
,"4111694 5171296 6847697 4601273 7599828 5515929 94"
,"60593 9332762 5389080 4512091 8668538 5711743 5838"
,"534 4825079 8145628 3810005 2964724 5594550 785748"
,"3 6283769"},
{"5911694 8009943 212555 5838688 9896256 607434 5857"
,"663 4616750 1477573 7168026 3090917 4379806 326465"
,"7 4189076 2104028 3279691 94211 8503556 78457 4394"
,"360 3344176 3223317 2624498 4883494 1532240 732937"
,"1 1518674 1353567 892134 5536454 8527392 2603965 6"
,"623264 8830827 2030444 3002706 83058 4475866 20876"
,"25 1790695 4034441 5409379 3571098 4600050 736561 "
,"250475 3733256 3011439 2144994 4523046 3119883 607"
,"582 8361403 6525451 7518329 926803 4884524 8424659"
," 7088689 5762049 9532481 4914186 7314621 4339084 3"
,"741685 3837953 3177252 612550 9688871 5872931"});
}
