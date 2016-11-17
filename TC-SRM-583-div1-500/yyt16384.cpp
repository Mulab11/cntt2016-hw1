#include <string>
#include <vector>

class TurnOnLamps {
  public:
    int minimize(std::vector<int> roads, std::string initState, std::string isImportant);
};

int TurnOnLamps::minimize(std::vector<int> roads, std::string initState, std::string isImportant)
{
    // Assume that all paths have root as the top node
    int n = roads.size() + 1;
    std::vector<char> tot(n);
    int ans = 0;
    for (int i = n - 1; i >= 1; i--) {
        if (isImportant[i - 1] == '1') {
            // Parity of number of paths ending in this subtree required
            bool req = initState[i - 1] == '0';
            if (req != tot[i]) {
                // Add another path ending at node i
                ans++;
            }
            tot[roads[i - 1]] ^= req;
        } else {
            // No requirements
            tot[roads[i - 1]] ^= tot[i];
        }
    }
    // Two top-down paths can be merge into one operation
    return (ans + 1) / 2;
}
