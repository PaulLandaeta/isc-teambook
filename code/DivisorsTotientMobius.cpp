/*
  Divisors, Euler's Totient, and Mobius function
  - Linear sieve computing primes, phi, and mu up to N in O(N)
  - Smallest Prime Factor (SPF) sieve for factorization and divisor functions
  - Utilities: count_divisors(n), sum_divisors(n)
*/

#include <bits/stdc++.h>
using namespace std;

struct SievePhiMu {
  int n; vector<int> primes, phi, mu; vector<char> comp;
  SievePhiMu(int n=0){ if(n) build(n); }
  void build(int N){
    n=N; comp.assign(n+1,0); phi.assign(n+1,0); mu.assign(n+1,0);
    phi[1]=1; mu[1]=1;
    for(int i=2;i<=n;++i){
      if(!comp[i]){ primes.push_back(i); phi[i]=i-1; mu[i] = -1; }
      for(int p:primes){ long long x=1LL*p*i; if(x>n) break; comp[(int)x]=1; if(i%p==0){ phi[(int)x] = phi[i]*p; mu[(int)x]=0; break; } else { phi[(int)x] = phi[i]*(p-1); mu[(int)x] = -mu[i]; } }
    }
  }
};

struct SPF {
  int n; vector<int> spf; SPF(int n=0){ if(n) build(n); }
  void build(int N){ n=N; spf.assign(n+1,0); for(int i=2;i<=n;++i){ if(!spf[i]){ spf[i]=i; if(1LL*i*i<=n) for(long long j=1LL*i*i;j<=n;j+=i) if(!spf[(int)j]) spf[(int)j]=i; } }
    spf[1]=1; for(int i=2;i<=n;++i) if(!spf[i]) spf[i]=i; }
  vector<pair<long long,int>> factorize(long long x) const {
    vector<pair<long long,int>> f; if(x<=1) return f; while(x>1){ long long p = (x<=n? spf[(int)x] : 0); if(!p){ // x may be prime > n; trial divide by stored primes not available here
        // fallback: poll naive up to sqrt if needed
        long long r = sqrt((long double)x), found=0; for(long long d=2; d<=r; ++d){ if(x%d==0){ p=d; found=1; break; } }
        if(!found){ f.push_back({x,1}); break; }
      }
      if(!p) continue; int c=0; while(x%p==0){ x/=p; ++c; } f.push_back({p,c});
    }
    return f;
  }
};

long long ipow(long long a, int e){ long long r=1; while(e){ if(e&1) r*=a; a*=a; e>>=1; } return r; }

long long count_divisors_with_spf(long long x, const SPF& sv){ auto f=sv.factorize(x); long long res=1; for(auto &pe:f) res *= (pe.second+1); return res; }
long long sum_divisors_with_spf(long long x, const SPF& sv){ auto f=sv.factorize(x); long long res=1; for(auto &pe:f){ long long p=pe.first; int e=pe.second; long long num = ipow(p, e+1)-1; long long den = p-1; res *= (num/den); } return res; }

// Example usage:
// int main(){
//   SievePhiMu s(1000000); // s.phi[i], s.mu[i]
//   SPF spf(1000000);
//   long long x=360;
//   cout << count_divisors_with_spf(x, spf) << " " << sum_divisors_with_spf(x, spf) << "\n";
// }
