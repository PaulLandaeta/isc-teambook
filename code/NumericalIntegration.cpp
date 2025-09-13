/*
  Numerical Integration (Simpson's rule)
  - simpson_composite(f, a, b, n): O(n) composite Simpson over n subintervals
    (no need for n even; uses midpoint per subinterval)
  - simpson_adaptive(f, a, b, eps, max_depth): adaptive Simpson with tolerance
    eps and recursion limit max_depth. Works well for smooth functions.
*/

#include <bits/stdc++.h>
using namespace std;

using F = function<double(double)>;

// Composite Simpson: sum over each subinterval using a midpoint
double simpson_composite(const F& f, double a, double b, int n = 10000) {
  if (n <= 0) return 0.0;
  double h = (b - a) / n;
  double area = 0.0;
  double fa = f(a);
  for (int i = 0; i < n; ++i) {
    double left = a + h * i;
    double right = left + h;
    double mid = (left + right) * 0.5;
    double fb = f(right);
    area += fa + 4.0 * f(mid) + fb;
    fa = fb;
  }
  return area * (h / 6.0);
}

// Helper: Simpson estimate on [a, b]
inline double simpson_interval(const F& f, double a, double b) {
  double c = 0.5 * (a + b);
  return (f(a) + 4.0 * f(c) + f(b)) * (b - a) / 6.0;
}

// Adaptive Simpson recursion
double adaptive_rec(const F& f, double a, double b, double eps, double S,
                           int depth, int max_depth) {
  double c = 0.5 * (a + b);
  double Sleft = simpson_interval(f, a, c);
  double Sright = simpson_interval(f, c, b);
  double delta = Sleft + Sright - S;
  if (depth >= max_depth || fabs(delta) <= 15.0 * eps) {
    // Richardson extrapolation
    return Sleft + Sright + delta / 15.0;
  }
  return adaptive_rec(f, a, c, eps * 0.5, Sleft, depth + 1, max_depth)
       + adaptive_rec(f, c, b, eps * 0.5, Sright, depth + 1, max_depth);
}

double simpson_adaptive(const F& f, double a, double b, double eps = 1e-9, int max_depth = 20) {
  double S = simpson_interval(f, a, b);
  return adaptive_rec(f, a, b, eps, S, 0, max_depth);
}

// Example usage:
// int main(){
//   auto f = [](double x){ return sin(x); };
//   cout.setf(std::ios::fixed); cout<<setprecision(12);
//   cout << simpson_composite(f, 0, M_PI, 10000) << "\n"; // ~2
//   cout << simpson_adaptive(f, 0, M_PI, 1e-10) << "\n";   // ~2
// }

