#include<bits/stdc++.h>
using namespace std;
class JumpFurther
{
    public:
        int furthest(int N, int badStep)
        {
            int i=sqrt(badStep<<1);
            return (N*(N+1)>>1)-(i<=N&&i*(i+1)==badStep<<1);
        }
};
