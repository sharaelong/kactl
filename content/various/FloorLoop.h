/**
 * Author:
 * Description:
 */
#pragma once

// floor(n / 1), floor(n / 2), ... has at most 2 * sqrt(n) different values
for (int l = 1; l <= n; ) {
  int q = n / l;
  int r = n / q;
  // floor(n / x) = q for x in [l, r]
  l = r + 1;
}
