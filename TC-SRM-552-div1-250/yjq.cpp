#include <bits/stdc++.h>

using namespace std ;

typedef long long LL ; 

class FoxPaintingBalls{
public:
    LL theMax(LL R, LL G, LL B, int N){
        LL ans = 0;
        LL n = N;
        if(n % 3 != 1)
            return min(B,min(R,G)) / ((LL)n * (n + 1) / 6);
        if(R<G) swap(R,G);
        if(R<B) swap(R,B);
        if(G<B) swap(G,B);
        if(n == 1)  return B + R + G;
        ans = min(R / (n * (n + 1) / 6),min(G / ((n + 1) * n / 6),B / (n * (n + 1) / 6)));
        LL leftR = R-(ans * (n * (n + 1) / 6));
        LL leftG = G-(ans * (n * (n + 1) / 6));
        LL leftB = B-(ans * (n * (n + 1) / 6));
        if(leftB + leftG + leftR>= ans)  return ans;
        return ans-(ans-(leftB + leftG + leftR) + n * (n + 1) / 2-1) / (n * (n + 1) / 2);
    }
};
