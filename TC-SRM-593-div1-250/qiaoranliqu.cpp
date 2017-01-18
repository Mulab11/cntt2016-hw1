#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

#define N 55

using namespace std;

struct Node{int x,y;}Q[N*N];
int cnt,n,i,j,k,color[N][N];
const int x[6]={0,0,-1,1,-1,1};
const int y[6]={1,-1,0,0,1,-1};
int check(int x,int y)
{
    if (x<0||x>=n||y<0||y>=n) return 0;
	return 1;
}
int work(int sx,int sy,vector<string> v)
{
	   int l=1,r=0,i;
	   Q[++r]=(Node){sx,sy};
	   color[sx][sy]=1;
	   for (;l<=r;++l)
	   {
	   	  Node p=Q[l];
	   	  for (i=0;i<6;++i)
	   	   if(check(p.x+x[i],p.y+y[i])&&v[p.x+x[i]][p.y+y[i]]=='X')
	   	   {
	   	   	      if (color[p.x][p.y]==color[p.x+x[i]][p.y+y[i]]) return 0;
	   	   	      if (color[p.x+x[i]][p.y+y[i]]==-1)
	   	   	      {
	   	   	      	 color[p.x+x[i]][p.y+y[i]]=color[p.x][p.y]^1;
	   	   	      	 Q[++r]=(Node){p.x+x[i],p.y+y[i]};
	   	   	      }
	   	   }
	   }
	   return 1;
}
class HexagonalBoard{
   public:
   int minColors(vector<string> v)
   {
   	    n=v.size();
   	    for (i=0;i<n;++i)
   	      for (j=0;j<n;++j)
   	        if (v[i][j]=='X') ++cnt;
   	    if (!cnt) return 0;
   	    cnt=0;
   	    memset(color,-1,sizeof(color));
   	    for (i=0;i<n;++i)
   	      for (j=0;j<n;++j)
   	        if (v[i][j]=='X')
   	        {
   	          for (k=0;k<6;++k)
				    if (check(i+x[k],j+y[k])&&v[i+x[k]][j+y[k]]=='X') break; 
			  if (k!=6) ++cnt;
		    }
		if (!cnt) return 1;
		for (i=0;i<n;++i)
		  for (j=0;j<n;++j) 
		     if (color[i][j]==-1&&v[i][j]=='X') if (!work(i,j,v)) return 3;
		return 2;
   }
}FFT;
int main()
{
     vector<string> s;
     s.push_back("XXXX"),
     s.push_back("---X"),
 	 s.push_back("---X"),
 	 s.push_back("---X");
 	 FFT.minColors(s);
 }
