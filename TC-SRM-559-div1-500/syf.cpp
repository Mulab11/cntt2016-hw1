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

struct HatRack
{
    long long dp[52][52];
    vector<int> knob1, knob2;
    
    int n;
    
    
    long long rec(int x, int parent, int index)
    {
        if (index >= n ) {
            return 0;
        }
        // In practice, we will do the rooting process as we
        // solve the recurrence. That is the reason for the
        // {parent} argument. This is not necessary though you can
        // make the correct graph in a separate part.
        //
        long long & res = dp[x][index];
        if (res == -1) {
            res = 0;
            // rooting: Find the children of x.
            vector<int> children;
            for (int i=0; i<n-1; i++) {
                int v;
                if (knob1[i] == x) {
                    v = knob2[i];
                } else if (knob2[i] == x) {
                    v = knob1[i];
                } else {
                    continue;
                }
                if ( v != parent ) {
                    children.push_back(v);
                }
            }
            if (children.size() > 2) {
                // We would like the tree to be binary
                res = 0;
                return 0;
            }
            if (children.size() == 2) {
                // two children
                long long p, q;
                // 0->left, 1->right
                p = rec( children[0], x, index*2 + 1 );
                q = rec( children[1], x, index*2 + 2 );
                res += p*q;
                // 1->left, 0->right
                p = rec( children[1], x, index*2 + 1 );
                q = rec( children[0], x, index*2 + 2 );
                res += p*q;                
            } else if (children.size() == 1) {
                if (index*2 + 2 < n ) {
                    //Node x was spposed to have two children!
                    res = 0;
                } else {
                    res = rec(children[0], x, index*2 + 1);
                }
            } else { // no children (base case)
                if (index*2 + 1 >= n) { //supposed to be empty
                    res = 1; //one way to do it
                } else {
                    res = 0; // no way to do it
                }
            }
       }
       return res;
    }
    
    long long countWays(vector <int> knob1, vector <int> knob2)
    {
        this->knob1 = knob1;
        this->knob2 = knob2;
        
        n = knob1.size() + 1;
        
        long long res = 0;
        for (int root=1; root <= n; root++) {
            //how many ways to do it if we use this root?
            //it has at most two children.
            memset(dp, -1, sizeof(dp));
            res += rec(root, root, 0);
        }
        return res;
    }
};