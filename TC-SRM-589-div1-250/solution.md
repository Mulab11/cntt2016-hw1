# GooseTattarrattatDiv1

作者：尤艺霖

关键词：并查集 字符串

## 题目简述

输入一个仅包含小写英文字符的字符串，支持以下一种操作：

1.选择一个字符，然后选定该字符串中所有相同的字符，并用另一种小写英文字符字符替换它们，代价为被替换的字符的个数。

要求只用这种操作，使得该字符串变为**回文串**，同时使得代价之和最小。

输出最小代价。

保证输入的字符串的长度小于等于50，并且保证其中只包含小写英文字符。

## 算法

考虑对称位置上的字符，若它们不相同，则在修改后，它们所对应的字符必须相同。

由此建立一个26个点的图，每个点代表着一个小写英文字符，两个点之间有一条无向边当且仅当这两个点对应的字符在原串种出现在某个对称位置。

可以发现每个联通块中的字符必须在最终的字符串中相同，所以每个联通块的代价是其中字符的总量减去其中出现次数最多的字符的出现次数。

将所有联通块的答案相加就是最终答案。

在建图的过程中，可以使用并查集维护联通块。

实现的细节可以参见代码：

```c++
struct GooseTattarrattatDiv1
{
    int fat[120],cnt[120],mx[120];
    inline int fnd(int x)// find root for DSU
    {
        if(fat[x]==x)return x;
        return fat[x]=fnd(fat[x]);
    }
    inline int getmin(string S)
    {
        int l=S.length();
        S=" "+S;
        for (int i=1;i<=l;i++)// count the number of each letter
        {
            cnt[S[i]-'a'+1]++;
        }
        for (int i=1;i<=26;i++)// initialize DSU
        {
            mx[i]=cnt[i];
            fat[i]=i;
        }
        for (int i=1;i<=l/2;i++)// join the letters
        {
            fat[fnd(S[i]-'a'+1)]=fnd(S[l+1-i]-'a'+1);
        }
        for (int i=1;i<=26;i++)// calculate the sum and the max value for each conponent
        {
            if(fnd(i)!=i)
            {
                cnt[fnd(i)]+=cnt[i];
                mx[fnd(i)]=max(mx[fnd(i)],mx[i]);
            }
        }
        int ans=0;
        for (int i=1;i<=26;i++)// calculate the answer
        {
            if(fnd(i)==i)ans+=cnt[i]-mx[i];
        }
        return ans;
    }
};
```



