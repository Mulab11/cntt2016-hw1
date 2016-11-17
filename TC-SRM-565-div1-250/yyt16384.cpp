#include <queue>
#include <vector>

class MonstersValley {
  public:
    int minimumPrice(std::vector<long long> dread, std::vector<int> price);
};

int MonstersValley::minimumPrice(std::vector<long long> dread, std::vector<int> price)
{
    // Monsters that can be added for cost 1
    std::priority_queue<long long> add1;
    long long cur = 0;
    int ans = 0;
    for (int i = 0; i < (int)dread.size(); i++) {
        if (dread[i] > cur) {
            if (price[i] == 1) {
                // Add this monster
                ans++;
                cur += dread[i];
            } else {
                if (!add1.empty() && cur + add1.top() >= dread[i]) {
                    long long x = add1.top();
                    // Add a monster with cost 1
                    ans++;
                    cur += x;
                    add1.pop();
                    // Add the option to replace x with current monster
                    add1.push(dread[i] - x);
                } else {
                    // Add this monster
                    ans += 2;
                    cur += dread[i];
                }
            }
        } else if (price[i] == 1) {
            // This monster is available for adding
            add1.push(dread[i]);
        }
    }
    return ans;
}
