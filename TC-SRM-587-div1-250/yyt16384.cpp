#include <cmath>

class JumpFurther {
  public:
    int furthest(int N, int badStep);
};

int JumpFurther::furthest(int N, int badStep)
{
    int d = 8 * badStep + 1;
    int k = (std::sqrt(d) - 1) / 2 + 0.5;
    if (k * (k + 1) / 2 == badStep && k <= N) {
        // The broken step will be hit on kth action, so skip the first
        // action to avoid this
        return N * (N + 1) / 2 - 1;
    } else {
        // The broken step will not be hit
        return N * (N + 1) / 2;
    }
}
