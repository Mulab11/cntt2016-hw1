#include<bits/stdc++.h>
using namespace std;typedef long long LL;const LL MaxN=80000000000000000ll;const int MaxN_2=282842712;const int MaxN_3=430886;const int MaxN_4=16817;bool isP2[1+MaxN_3],isP3[1+MaxN_4];int*cntP2[1+MaxN_3];vector<int>fac[1+MaxN_3];inline int gcd(int a,int b){while(b!=0){a%=b;swap(a,b);}return a;}class SemiPerfectPower{private:inline int floor_sqrt(const LL&n){int le=1,ri=MaxN_2+1;while(le!=ri){int mid=(le+ri)>>1;if(1LL*mid*mid<=n)le=mid+1;else ri=mid;}return le-1;}inline int floor_cubert(const LL&n){int le=1,ri=MaxN_3+1;while(le!=ri){int mid=(le+ri)>>1;if(1LL*mid*mid*mid<=n)le=mid+1;else ri=mid;}return le-1;}inline LL calc(const LL&n){LL res=0;for(int c=1;1LL*c*c*c<n;c++)if(isP2[c])res+=floor_sqrt(n/c)-c;for(int b=1;1LL*b*b*b*b<n;b++)if(isP3[b])for(int k=1;k*k*k<=b;k++){int g=gcd(b,k*k);int sb=b/g;int sk=k*k/g;if(!isP2[sb])continue;int minY=b,maxY=floor_cubert(n/b);for(int ds=0;ds<(1<<fac[sb].size());ds++){int d=1;int mu=1;for(int i=0;i<(int)fac[sb].size();i++)if(ds>>i&1)d*=fac[sb][i],mu*=-1;res+=mu*(cntP2[d][maxY/sk/d]-cntP2[d][minY/sk/d]);}}return res;}public:SemiPerfectPower(){fill(isP2+1,isP2+MaxN_3+1,true);for(int i=2;i*i<=MaxN_3;i++)for(int j=i*i;j<=MaxN_3;j+=i*i)isP2[j]=false;fill(isP3+1,isP3+MaxN_4+1,true);for(int i=2;i*i*i<=MaxN_4;i++)for(int j=i*i*i;j<=MaxN_4;j+=i*i*i)isP3[j]=false;for(int i=1;i<=MaxN_3;i++){int l=MaxN_3/i;cntP2[i]=new int[1+l];cntP2[i][0]=0;for(int j=1;j<=l;j++)cntP2[i][j]=cntP2[i][j-1]+isP2[i*j];}for(int i=2;i<=MaxN_3;i++)if(fac[i].empty())for(int j=i;j<=MaxN_3;j+=i)fac[j].push_back(i);}~SemiPerfectPower(){for(int i=1;i<=MaxN_3;i++)delete[]cntP2[i];}LL count(LL numL,LL numR){return calc(numR)-calc(numL-1);}};