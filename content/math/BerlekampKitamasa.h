/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

vector<int> berlekamp_massey(vector<int> x){
  vector<int> ls, cur;
  int lf, ld;
  for(int i=0; i<x.size(); i++){
    ll t = 0;
    for(int j=0; j<cur.size(); j++){
      t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
    }
    if((t - x[i]) % mod == 0) continue;
    if(cur.empty()){
      cur.resize(i+1);
      lf = i;
      ld = (t - x[i]) % mod;
      continue;
    }
    ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
    vector<int> c(i-lf-1);
    c.push_back(k);
    for(auto &j : ls) c.push_back(-j * k % mod);
    if(c.size() < cur.size()) c.resize(cur.size());
    for(int j=0; j<cur.size(); j++){
      c[j] = (c[j] + cur[j]) % mod;
    }
    if(i-lf+(int)ls.size()>=(int)cur.size()){
      tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
    }
    cur = c;
  }
  for(auto &i : cur) i = (i % mod + mod) % mod;
  return cur;
}

struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..
vector<int> get_min_poly(int n, vector<elem> M){
  // smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
  vector<int> rnd1, rnd2;
  mt19937 rng(0x14004);
  auto randint = [&rng](int lb, int ub){
    return uniform_int_distribution<int>(lb, ub)(rng);
  };
  for(int i=0; i<n; i++){
    rnd1.push_back(randint(1, mod - 1));
    rnd2.push_back(randint(1, mod - 1));
  }
  vector<int> gobs;
  for(int i=0; i<2*n+2; i++){
    int tmp = 0;
    for(int j=0; j<n; j++){
      tmp += 1ll * rnd2[j] * rnd1[j] % mod;
      if(tmp >= mod) tmp -= mod;
    }
    gobs.push_back(tmp);
    vector<int> nxt(n);
    for(auto &i : M){
      nxt[i.x] += 1ll * i.v * rnd1[i.y] % mod;
      if(nxt[i.x] >= mod) nxt[i.x] -= mod;
    }
    rnd1 = nxt;
  }
  auto sol = berlekamp_massey(gobs);
  reverse(sol.begin(), sol.end());
  return sol;
}
lint det(int n, vector<elem> M){
  vector<int> rnd;
  mt19937 rng(0x14004);
  auto randint = [&rng](int lb, int ub){
    return uniform_int_distribution<int>(lb, ub)(rng);
  };
  for(int i=0; i<n; i++) rnd.push_back(randint(1, mod - 1));
  for(auto &i : M){
    i.v = 1ll * i.v * rnd[i.y] % mod;
  }
  auto sol = get_min_poly(n, M)[0];
  if(n % 2 == 0) sol = mod - sol;
  for(auto &i : rnd) sol = 1ll * sol * ipow(i, mod - 2) % mod;
  return sol;
}

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;

template<int M>
struct MINT{
  int v;
  MINT() : v(0) {}
  MINT(ll val){
    v = (-M <= val && val < M) ? val : val % M;
    if(v < 0) v += M;
  }

  friend istream& operator >> (istream &is, MINT &a) { ll t; is >> t; a = MINT(t); return is; }
  friend ostream& operator << (ostream &os, const MINT &a) { return os << a.v; }
  friend bool operator == (const MINT &a, const MINT &b) { return a.v == b.v; }
  friend bool operator != (const MINT &a, const MINT &b) { return a.v != b.v; }
  friend MINT pw(MINT a, ll b){
    MINT ret= 1;
    while(b){
      if(b & 1) ret *= a;
      b >>= 1; a *= a;
    }
    return ret;
  }
  friend MINT inv(const MINT a) { return pw(a, M-2); }
  MINT operator - () const { return MINT(-v); }
  MINT& operator += (const MINT m) { if((v += m.v) >= M) v -= M; return *this; }
  MINT& operator -= (const MINT m) { if((v -= m.v) < 0) v += M; return *this; }
  MINT& operator *= (const MINT m) { v = (ll)v*m.v%M; return *this; }
  MINT& operator /= (const MINT m) { *this *= inv(m); return *this; }
  friend MINT operator + (MINT a, MINT b) { a += b; return a; }
  friend MINT operator - (MINT a, MINT b) { a -= b; return a; }
  friend MINT operator * (MINT a, MINT b) { a *= b; return a; }
  friend MINT operator / (MINT a, MINT b) { a /= b; return a; }
  operator int32_t() const { return v; }
  operator int64_t() const { return v; }
};

namespace fft{
  template<int W, int M>
  static void NTT(vector<MINT<M>> &f, bool inv_fft = false){
    using T = MINT<M>;
    int N = f.size();
    vector<T> root(N >> 1);
    for(int i=1, j=0; i<N; i++){
      int bit = N >> 1;
      while(j >= bit) j -= bit, bit >>= 1;
      j += bit;
      if(i < j) swap(f[i], f[j]);
    }
    T ang = pw(T(W), (M-1)/N); if(inv_fft) ang = inv(ang);
    root[0] = 1; for(int i=1; i<N>>1; i++) root[i] = root[i-1] * ang;
    for(int i=2; i<=N; i<<=1){
      int step = N / i;
      for(int j=0; j<N; j+=i){
        for(int k=0; k<i/2; k++){
          T u = f[j+k], v = f[j+k+(i>>1)] * root[k*step];
          f[j+k] = u + v;
          f[j+k+(i>>1)] = u - v;
        }
      }
    }
    if(inv_fft){
      T rev = inv(T(N));
      for(int i=0; i<N; i++) f[i] *= rev;
    }
  }
  template<int W, int M>
  vector<MINT<M>> multiply_ntt(vector<MINT<M>> a, vector<MINT<M>> b){
    int N = 2; while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    NTT<W, M>(a); NTT<W, M>(b);
    for(int i=0; i<N; i++) a[i] *= b[i];
    NTT<W, M>(a, true);
    return a;
  }
}

template<int W, int M>
struct PolyMod{
  using T = MINT<M>;
  vector<T> a;

  // constructor
  PolyMod(){}
  PolyMod(T a0) : a(1, a0) { normalize(); }
  PolyMod(const vector<T> a) : a(a) { normalize(); }

  // method from vector<T>
  int size() const { return a.size(); }
  int deg() const { return a.size() - 1; }
  void normalize(){ while(a.size() && a.back() == T(0)) a.pop_back(); }
  T operator [] (int idx) const { return a[idx]; }
  typename vector<T>::const_iterator begin() const { return a.begin(); }
  typename vector<T>::const_iterator end() const { return a.end(); }
  void push_back(const T val) { a.push_back(val); }
  void pop_back() { a.pop_back(); }

  // basic manipulation
  PolyMod reversed() const {
    vector<T> b = a;
    reverse(b.begin(), b.end());
    return b;
  }
  PolyMod trim(int n) const {
    return vector<T>(a.begin(), a.begin() + min(n, size()));
  }
  PolyMod inv(int n){
    PolyMod q(T(1) / a[0]);
    for(int i=1; i<n; i<<=1){
      PolyMod p = PolyMod(2) - q * trim(i * 2);
      q = (p * q).trim(i * 2);
    }
    return q.trim(n);
  }

  // operation with scala value
  PolyMod operator *= (const T x){
    for(auto &i : a) i *= x;
    normalize();
    return *this;
  }
  PolyMod operator /= (const T x){
    return *this *= (T(1) / T(x));
  }

  // operation with poly
  PolyMod operator += (const PolyMod &b){
    a.resize(max(size(), b.size()));
    for(int i=0; i<b.size(); i++) a[i] += b.a[i];
    normalize();
    return *this;
  }
  PolyMod operator -= (const PolyMod &b){
    a.resize(max(size(), b.size()));
    for(int i=0; i<b.size(); i++) a[i] -= b.a[i];
    normalize();
    return *this;
  }
  PolyMod operator *= (const PolyMod &b){
    *this = fft::multiply_ntt<W, M>(a, b.a);
    normalize();
    return *this;
  }
  PolyMod operator /= (const PolyMod &b){
    if(deg() < b.deg()) return *this = PolyMod();
    int sz = deg() - b.deg() + 1;
    PolyMod ra = reversed().trim(sz), rb = b.reversed().trim(sz).inv(sz);
    *this = (ra * rb).trim(sz);
    for(int i=sz-size(); i; i--) push_back(T(0));
    reverse(all(a));
    normalize();
    return *this;
  }
  PolyMod operator %= (const PolyMod &b){
    if(deg() < b.deg()) return *this;
    PolyMod tmp = *this; tmp /= b; tmp *= b;
    *this -= tmp;
    normalize();
    return *this;
  }

  // operator
  PolyMod operator * (const T x) const { return PolyMod(*this) *= x; }
  PolyMod operator / (const T x) const { return PolyMod(*this) /= x; }
  PolyMod operator + (const PolyMod &b) const { return PolyMod(*this) += b; }
  PolyMod operator - (const PolyMod &b) const { return PolyMod(*this) -= b; }
  PolyMod operator * (const PolyMod &b) const { return PolyMod(*this) *= b; }
  PolyMod operator / (const PolyMod &b) const { return PolyMod(*this) /= b; }
  PolyMod operator % (const PolyMod &b) const { return PolyMod(*this) %= b; }
};

constexpr int W = 3, MOD = 104857601;
using mint = MINT<MOD>;
using poly = PolyMod<W, MOD>;

mint kitamasa(poly c, poly a, ll n){
  poly x = vector<mint>{0,1};
  poly res = vector<mint>{1};
  while (n > 0) {
    if (n & 1) res = res * x % c;
    x = x * x % c;
    n /= 2;
  }

  mint ret(0);
  for (int i=0; i<a.size(); ++i) ret += res[i] * a[i];
  return ret;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int k;
  ll n;
  cin >> k >> n;
  vector<mint> A(k), C(k);
  for (int i=0; i<k; ++i) {
    int x;
    cin >> x;
    A[i] = mint(x);
  }
  for (int i=0; i<k; ++i) {
    int x;
    cin >> x;
    C[i] = mint(x);
  }
    
  reverse(C.begin(), C.end());
  for (int i=0; i<C.size(); ++i) C[i] = -C[i];
  C.push_back(1);
  cout << kitamasa(C, A, n-1);
}
