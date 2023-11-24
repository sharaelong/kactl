/**
 * Author:
 * Description:
 */
#pragma once

int __builtin_clz(int x); // Number of leading zeros 0010 = 2
int __builtin_ctz(int x); // Number of trailing zeros 0010 = 1
int __builtin_popcount(int x); // Number of 1-bits in x 01011 = 3

int lsb(int n) { return n & -n; } // Smallest bit
int remove_lsb(int n) { return n & (n - 1); } // n - lsb(n)

// Subset iteration, used in O(3^n) dp
for (int i = x; ; i = (i - 1) & x) {
    // i is a subset of x, decreasing in terms of integer value
  if (i == 0) break;
}
