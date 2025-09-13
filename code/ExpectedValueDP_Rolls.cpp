/*
  Expected Value DP: expected number of die rolls to reach or exceed N
  - expected_rolls_to_reach(N, faces): E[pos] satisfies
      E[N] = 0, and for 0 <= x < N:
      E[x] = 1 + (1/faces) * sum_{d=1..faces} E[min(x + d, N)]
  Returns E[0].
  Complexity: O(N * faces)
*/

#include <bits/stdc++.h>
using namespace std;

double expected_rolls_to_reach(int N, int faces = 6) {
  vector<double> E(N + 1, 0.0);
  for (int x = N - 1; x >= 0; --x) {
    double sum = 0.0;
    for (int d = 1; d <= faces; ++d) {
      int nx = x + d; if (nx > N) nx = N; // cap at N
      sum += E[nx];
    }
    E[x] = 1.0 + sum / faces;
  }
  return E[0];
}

// Example usage:
// int main(){ cout.setf(std::ios::fixed); cout<<setprecision(6);
//   cout << expected_rolls_to_reach(100) << "\n"; }

