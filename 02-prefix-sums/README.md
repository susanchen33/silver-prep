# 📚 Topic 2: Prefix Sums

## Overview

Prefix sums allow you to answer **range sum queries** in **O(1)** time after **O(N)** preprocessing. This technique is essential for Silver and appears frequently.

---

## Key Concepts

### 1. One-Dimensional Prefix Sums

**Problem:** Given an array, answer multiple queries for sum of elements from index L to R.

**Naive approach:** O(N) per query → Too slow for many queries

**Prefix sum approach:** O(1) per query after O(N) preprocessing

```cpp
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 3, 5, 2, 7, 6};  // 0-indexed
    int n = arr.size();
    
    // Build prefix sum array
    // prefix[i] = sum of arr[0...i-1]
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    // prefix = {0, 1, 4, 9, 11, 18, 24}
    
    // Query: sum from index L to R (inclusive, 0-indexed)
    // sum(L, R) = prefix[R+1] - prefix[L]
    
    // Example: sum of arr[1...4] = 3 + 5 + 2 + 7 = 17
    int L = 1, R = 4;
    long long sum = prefix[R + 1] - prefix[L];  // = 18 - 1 = 17 ✓
    
    return 0;
}
```

**Visual Explanation:**
```
Array:    [1]  [3]  [5]  [2]  [7]  [6]
Index:     0    1    2    3    4    5

Prefix:  [0]  [1]  [4]  [9] [11] [18] [24]
Index:    0    1    2    3    4    5    6

Sum(1,4) = prefix[5] - prefix[1] = 18 - 1 = 17
```

### 2. Two-Dimensional Prefix Sums

For 2D grids, compute prefix sums using inclusion-exclusion.

```cpp
#include <vector>
using namespace std;

int main() {
    int n = 4, m = 5;  // n rows, m columns
    vector<vector<int>> grid(n, vector<int>(m));
    // ... fill grid with values
    
    // Build 2D prefix sum
    // prefix[i][j] = sum of all cells in rectangle (0,0) to (i-1,j-1)
    vector<vector<long long>> prefix(n + 1, vector<long long>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            prefix[i][j] = grid[i-1][j-1] 
                         + prefix[i-1][j] 
                         + prefix[i][j-1] 
                         - prefix[i-1][j-1];
        }
    }
    
    // Query: sum of rectangle from (r1,c1) to (r2,c2) inclusive (0-indexed)
    auto query = [&](int r1, int c1, int r2, int c2) -> long long {
        return prefix[r2+1][c2+1] 
             - prefix[r1][c2+1] 
             - prefix[r2+1][c1] 
             + prefix[r1][c1];
    };
    
    return 0;
}
```

**Inclusion-Exclusion Principle:**
```
To get sum of shaded rectangle:

+---------------+
|   A   |   B   |
|-------+-------|
|   C   | Query |
+-------+-------+

sum(Query) = prefix(full) - prefix(A+B) - prefix(A+C) + prefix(A)
```

### 3. Difference Arrays

The inverse of prefix sums. Useful for **range updates**.

**Problem:** Add value V to all elements from index L to R.

```cpp
#include <vector>
using namespace std;

int main() {
    int n = 6;
    vector<int> diff(n + 1, 0);  // Difference array
    
    // Range update: add V to indices L through R (0-indexed)
    auto rangeAdd = [&](int L, int R, int V) {
        diff[L] += V;
        diff[R + 1] -= V;
    };
    
    // Add 3 to indices 1-4
    rangeAdd(1, 4, 3);
    // Add 2 to indices 2-5
    rangeAdd(2, 5, 2);
    
    // Convert difference array to actual values
    vector<int> arr(n);
    arr[0] = diff[0];
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i-1] + diff[i];
    }
    // arr = {0, 3, 5, 5, 5, 2}
    
    return 0;
}
```

---

## Common Patterns

### Pattern 1: Subarray Sum Equals K

Count subarrays with sum equal to K.

```cpp
#include <unordered_map>
#include <vector>
using namespace std;

int subarraySumK(vector<int>& arr, int k) {
    unordered_map<long long, int> count;
    count[0] = 1;  // Empty prefix has sum 0
    
    long long prefix = 0;
    int result = 0;
    
    for (int x : arr) {
        prefix += x;
        // If prefix - k exists, we found subarrays summing to k
        if (count.count(prefix - k)) {
            result += count[prefix - k];
        }
        count[prefix]++;
    }
    
    return result;
}
```

### Pattern 2: Maximum Subarray Sum (Kadane's Algorithm)

Find contiguous subarray with largest sum.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

long long maxSubarraySum(vector<int>& arr) {
    long long maxSum = arr[0];
    long long currentSum = arr[0];
    
    for (int i = 1; i < arr.size(); i++) {
        currentSum = max((long long)arr[i], currentSum + arr[i]);
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}
```

### Pattern 3: Subarray Sum Divisible by K

Using modular arithmetic with prefix sums.

```cpp
#include <vector>
using namespace std;

int subarraysDivByK(vector<int>& arr, int k) {
    vector<int> count(k, 0);
    count[0] = 1;
    
    long long prefix = 0;
    int result = 0;
    
    for (int x : arr) {
        prefix += x;
        int mod = ((prefix % k) + k) % k;  // Handle negative mods
        result += count[mod];
        count[mod]++;
    }
    
    return result;
}
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Build 1D prefix sum | O(N) |
| Query 1D range sum | O(1) |
| Build 2D prefix sum | O(N×M) |
| Query 2D rectangle sum | O(1) |
| Range update (difference array) | O(1) |

---

## Common Mistakes

1. **Off-by-one errors**
   - Be very careful with indexing: is it 0-indexed or 1-indexed?
   - Double-check: `prefix[R+1] - prefix[L]` vs `prefix[R] - prefix[L-1]`

2. **Integer overflow**
   - Use `long long` for prefix sums when values can be large
   - N = 10^5 elements, each up to 10^9 → sum up to 10^14

3. **2D inclusion-exclusion**
   - Easy to mess up signs: `+prefix[r2+1][c2+1] - ... - ... + ...`
   - Draw a diagram to verify

4. **Negative numbers in modular problems**
   - In C++, `-7 % 5 = -2`, not `3`
   - Use `((x % k) + k) % k` to get positive remainder

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Static Range Sum Queries | CSES | [cses.fi](https://cses.fi/problemset/task/1646) |
| Breed Counting | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=572) |
| Hoof Paper Scissors | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=691) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Subsequences Summing to Sevens | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=595) |
| Subarray Sums II | CSES | [cses.fi](https://cses.fi/problemset/task/1661) |
| Forest Queries | CSES | [cses.fi](https://cses.fi/problemset/task/1652) |
| Painting the Barn | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=919) |
| Good Subarrays | Codeforces | [codeforces.com](https://codeforces.com/contest/1398/problem/C) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Rectangular Pasture | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1063) |
| Maximum Subarray Sum | CSES | [cses.fi](https://cses.fi/problemset/task/1643) |
| Subarray Divisibility | CSES | [cses.fi](https://cses.fi/problemset/task/1662) |

---

## Key Takeaways

1. ✅ Prefix sums turn O(N) range queries into O(1)
2. ✅ Master both 1D and 2D prefix sums
3. ✅ Learn difference arrays for range updates
4. ✅ Combine with hash maps for "subarray sum = K" problems
5. ✅ Watch out for integer overflow and off-by-one errors
