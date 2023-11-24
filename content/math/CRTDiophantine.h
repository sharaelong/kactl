/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

typedef long long lint;
typedef pair<lint, lint> pint;
// return: [g, x, y], g = gcd(a, b), solution of ax+by=g.
std::array<ll, 3> exgcd(ll a, ll b) {
  if (b == 0) {
    return {a, 1, 0};
  }
  auto [g, x, y] = exgcd(b, a % b);
  return {g, y, x - a / b * y};
}
// returns (x0, y0) where x0 >= 0, x0 = -1 if solution does not exist
pii solve(ll a, ll b, ll c) {
  ll g = __gcd(a, b);
  if (c % g != 0) return pii(-1, 0);
  c /= g; a /= g; b /= g;

  vector<ll> V; 
  while (b != 0) {
    ll q = a / b, r = a % b;
    V.push_back(q);
    a = b; b = r;
  }
  ll x = c, y = 0;
  while (!V.empty()) {
    ll q = V.back(); V.pop_back();
    b += q * a; swap(a, b);
    x -= q * y; swap(x, y);      
  }
  ll r = (x - (b + x % b) % b) / b;
  x -= b * r; y += a * r;

  return pii(x, y);
}
// returns (x, period of x), x = -1 if solution doesn't exist
pii CRT(ll a1, ll m1, ll a2, ll m2) {
  auto sol = solve(m1, m2, a2 - a1);
  if (sol.va == -1) return pii(-1, 0);
  ll g = __gcd(m1, m2); m2 /= g;
  return pii((m1 * sol.va + a1) % (m1 * m2), m1 * m2);
}
