#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=35;
int l[N][N],r[N][N];
int num[N];
int n;
int a[N];
int f[N][N];
class History{
public:
    string verifyClaims(vector <string> dy, vector <string> bat, vector <string> que){
        n=dy.size();
        rep(i,1,n){
            int now=0;
            int m=0;
            rep(j,0,dy[i-1].size()-1){
                if(dy[i-1][j]==' '){
                    a[++m]=now;
                    now=0;
                }
                else{
                    now=now*10+dy[i-1][j]-'0';
                }
            }
            a[++m]=now;

            num[i]=m-1;
            rep(j,1,m-1){
                l[i][j]=a[j];
                r[i][j]=a[j+1]-1;
            }
        }
        rep(i,1,n)rep(j,1,n)f[i][j]=-(int)(1e9);
        rep(i,1,n)f[i][i]=0;

        string bg="";
        rep(i,0,bat.size()-1)bg=bg+bat[i];

        for(int i=0;i<bg.size();i+=6){
            int d1=bg[i+0]-'A'+1;
            int g1=bg[i+1]-'0'+1;
            int d2=bg[i+3]-'A'+1;
            int g2=bg[i+4]-'0'+1;

            //printf("%d %d %d %d\n",d1,g1,d2,g2);

            f[d2][d1]=max(f[d2][d1],l[d1][g1]-r[d2][g2]);
            f[d1][d2]=max(f[d1][d2],l[d2][g2]-r[d1][g1]);
        }
        rep(k,1,n)rep(i,1,n)rep(j,1,n)f[i][j]=max(f[i][j],f[i][k]+f[k][j]);

        //rep(i,1,n)rep(j,1,n)printf("f[%d][%d]=%d\n",i,j,f[i][j]);

        string ans="";
        rep(i,0,que.size()-1){
            int d1=que[i][0]-'A'+1;
            int g1=que[i][1]-'0'+1;
            int d2=que[i][3]-'A'+1;
            int g2=que[i][4]-'0'+1;

            if(l[d1][g1]+f[d1][d2]>r[d2][g2])ans=ans+"N";
            else
            if(l[d2][g2]+f[d2][d1]>r[d1][g1])ans=ans+"N";
            else ans=ans+"Y";
        }
        return ans;
    }
}gt;