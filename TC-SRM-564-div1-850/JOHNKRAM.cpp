#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
#define ll long long
int m,i,j,k,x,y,z,I[30],ans;
class DefectiveAddition
{
    public:
        int count(vector <int> cards, int n)
        {
            m=cards.size();
            for(I[0]=i=1;i<30;i++)I[i]=(ll)I[i-1]*(P+1>>1)%P;//预处理2^-i%P 
            for(i=29;~i;i--)
            {
                for(x=1,j=y=0,k=n>>i&1;j<m;j++)if(cards[j]>>i&1)//第j个数第i位可以填1 
                {
                    cards[j]^=1<<i;//去掉高位 
                    k=!k;
                    z=x;
                    x=(((ll)x<<i)+(ll)y*(cards[j]+1))%P;
                    y=((ll)z*(cards[j]+1)+((ll)y<<i))%P;
                }
                else//第j个数第i位只能填0 
                {
                    x=(ll)x*(cards[j]+1)%P;
                    y=(ll)y*(cards[j]+1)%P;
                }
                if(n>>i&1)x=y;
                if(!k&&i)//判断是否算多算了所有数第i位都是可以填的最大值的情况 
                {
                    for(j=0,k=1;j<m;j++)k=(ll)k*(cards[j]+1)%P;
                    x=(x+P-k)%P;
                    k=0;
                }
                ans=(ans+(ll)x*I[i])%P;//计算答案 
                if(k)break;
            }
            return ans;
        }
};