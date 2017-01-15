#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<string>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
LL cost[300][300];
int id[12][12][12];int tot=0;
int n;
int a[105][105];
int c[105][105];
int b[105][105];
void gao(){
    //矩阵乘法
    rep(i,1,tot)rep(j,1,tot){
        b[i][j]=0;
        rep(k,1,tot)b[i][j]=(b[i][j]+a[i][k]*1ll*a[k][j])%P;
    }
    rep(i,1,tot)rep(j,1,tot)a[i][j]=b[i][j];
}
void cao(){
    //矩阵乘法
    rep(i,1,tot)rep(j,1,tot){
        b[i][j]=0;
        rep(k,1,tot)b[i][j]=(b[i][j]+c[i][k]*1ll*a[k][j])%P;
    }
    rep(i,1,tot)rep(j,1,tot)c[i][j]=b[i][j];
}
class ConversionMachine{
    public:
    int countAll(string word1,string word2,vector<int>co,int maxCost){
        //预处理出每个字符转移到哪个的代价
        cost['a']['b']=co[0]*1ll;
        cost['a']['c']=co[0]*1ll+co[1]*1ll;
        cost['b']['c']=co[1]*1ll;
        cost['b']['a']=co[1]*1ll+co[2]*1ll;
        cost['c']['a']=co[2]*1ll;
        cost['c']['b']=co[2]*1ll+co[0]*1ll;
        n=word1.size();
        LL must=0;
        LL lun=0;
        
        //我们可以发现，首先字符的转移是必须的，剩下的操作都是自己变成自己，也就是代价是co[0]+co[1]+co[2]
        //于是我们可以知道轮数的上限是什么，矩阵乘法记录一下需要0次转化的有几个，需要1次转化的有几个，需要2次转化的有几个
        rep(i,1,n){
            lun+=((3+word2[i-1]-word1[i-1])%3);
            must+=cost[word1[i-1]][word2[i-1]];
        }
        if(must>maxCost)return 0;
        maxCost-=must;
        lun+=3ll*(maxCost/(co[0]*1ll+co[1]*1ll+co[2]*1ll));
        

        //预处理出所有状态，状态数非常少，不超过100种
        rep(i,0,n)rep(j,0,n-i)id[i][j][n-i-j]=++tot;
        
        rep(i,0,n)rep(j,0,n-i){
            int k=n-i-j;
            //构建转移矩阵，枚举怎么转移
            if(k)a[id[i][j][k]][id[i][j+1][k-1]]+=k;
            if(j)a[id[i][j][k]][id[i+1][j-1][k]]+=j;
            if(i)a[id[i][j][k]][id[i-1][j][k+1]]+=i;
        }
        //顺便开一个额外变量累加全0状态的方案，因为maxCost不一定要用完
        ++tot;
        a[id[n][0][0]][tot]=1;
        a[tot][tot]=1;
        lun=lun+1ll;
        
        //矩阵乘法
        rep(i,1,tot)c[i][i]=1;
        
        for(;lun;lun/=2ll,gao()){
            if(lun&1)cao();
        }
        
        //处理初始状态
        int z[3];memset(z,0,sizeof z);
        rep(i,1,n){
            z[(3+word2[i-1]-word1[i-1])%3]++;
        }
        
        return c[id[z[0]][z[1]][z[2]]][tot];
    }
}gt;



