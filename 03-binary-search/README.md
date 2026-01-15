# 📚 Topic 3: Binary Search

## Overview

Binary search is one of the **most important techniques** for USACO Silver. It allows you to find elements in **O(log N)** time and, more importantly, to "binary search on the answer" for optimization problems.

---

## Key Concepts

### 1. Basic Binary Search

Find an element in a **sorted** array.

```cpp
#include <vector>
using namespace std;

// Returns index of target, or -1 if not found
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Not found
}
```

### 2. Lower Bound and Upper Bound

**Lower bound:** First position where element >= target  
**Upper bound:** First position where element > target

```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 4, 4, 4, 6, 8};
    
    // lower_bound: first element >= 4
    auto lb = lower_bound(arr.begin(), arr.end(), 4);
    int lb_idx = lb - arr.begin();  // Index 2
    
    // upper_bound: first element > 4
    auto ub = upper_bound(arr.begin(), arr.end(), 4);
    int ub_idx = ub - arr.begin();  // Index 5
    
    // Count of 4's = upper_bound - lower_bound = 5 - 2 = 3
    
    // Find first element >= 5 (doesn't exist, returns 6's position)
    auto it = lower_bound(arr.begin(), arr.end(), 5);
    // *it = 6, index = 5
    
    return 0;
}
```

### 3. Binary Search on the Answer

**The most powerful application!** When the answer has a monotonic property, binary search for it.

**Pattern:**
1. Define the search space: `[lo, hi]` = possible answer range
2. Define a `check(x)` function: returns true if `x` is achievable
3. Binary search to find the optimal `x`

```cpp
#include <vector>
using namespace std;

// Example: Find minimum maximum load when dividing array into K parts

bool canDivide(vector<int>& arr, int maxLoad, int k) {
    int parts = 1;
    int currentSum = 0;
    
    for (int x : arr) {
        if (x > maxLoad) return false;  // Single element too large
        if (currentSum + x > maxLoad) {
            parts++;
            currentSum = x;
        } else {
            currentSum += x;
        }
    }
    
    return parts <= k;
}

int minMaxLoad(vector<int>& arr, int k) {
    int lo = *max_element(arr.begin(), arr.end());  // At least max element
    int hi = accumulate(arr.begin(), arr.end(), 0); // At most total sum
    
    int answer = hi;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (canDivide(arr, mid, k)) {
            answer = mid;     // mid works, try smaller
            hi = mid - 1;
        } else {
            lo = mid + 1;     // mid doesn't work, try larger
        }
    }
    
    return answer;
}
```

### 4. Binary Search on Floating Point

For continuous answers, use a fixed number of iterations.

```cpp
double binarySearchFloat(double lo, double hi) {
    // 100 iterations gives precision of (hi-lo) / 2^100 ≈ 0
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        
        if (check(mid)) {
            hi = mid;  // or lo = mid depending on problem
        } else {
            lo = mid;
        }
    }
    
    return lo;  // or hi, they're essentially equal now
}
```

---

## Common Patterns

### Pattern 1: Maximize Minimum

"Maximize the minimum distance/value/etc."

**Structure:**
- Binary search on the minimum value
- Check function: can we achieve at least this minimum?

```cpp
// Example: Place K cows in N stalls to maximize minimum distance
bool canPlace(vector<int>& stalls, int minDist, int k) {
    int count = 1;
    int lastPos = stalls[0];
    
    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - lastPos >= minDist) {
            count++;
            lastPos = stalls[i];
        }
    }
    
    return count >= k;
}

int maxMinDistance(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end());
    
    int lo = 1;
    int hi = stalls.back() - stalls.front();
    int answer = 0;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (canPlace(stalls, mid, k)) {
            answer = mid;
            lo = mid + 1;  // Try larger minimum
        } else {
            hi = mid - 1;
        }
    }
    
    return answer;
}
```

### Pattern 2: Minimize Maximum

"Minimize the maximum load/time/etc."

**Structure:**
- Binary search on the maximum value
- Check function: can we achieve with at most this maximum?

```cpp
// Example: Assign N tasks to K workers to minimize maximum time
bool canAssign(vector<int>& tasks, int maxTime, int k) {
    int workers = 1;
    int currentTime = 0;
    
    for (int t : tasks) {
        if (t > maxTime) return false;
        if (currentTime + t > maxTime) {
            workers++;
            currentTime = t;
        } else {
            currentTime += t;
        }
    }
    
    return workers <= k;
}
```

### Pattern 3: Count Elements

Count elements satisfying a condition using binary search.

```cpp
// Count pairs (i, j) where arr[i] + arr[j] <= target
long long countPairs(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    long long count = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        // Find largest j where arr[i] + arr[j] <= target
        int maxVal = target - arr[i];
        auto it = upper_bound(arr.begin(), arr.end(), maxVal);
        int j = it - arr.begin() - 1;
        
        // Count valid pairs, excluding (i, i)
        if (j > i) {
            count += j - i;
        }
    }
    
    return count;
}
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Binary search | O(log N) |
| Binary search on answer | O(log(range) × check) |
| `lower_bound` / `upper_bound` | O(log N) |

---

## Common Mistakes

1. **Infinite loops**
   - Ensure `lo` and `hi` converge
   - Be careful with `mid = (lo + hi) / 2` vs `mid = (lo + hi + 1) / 2`

2. **Off-by-one errors**
   - Should it be `lo <= hi` or `lo < hi`?
   - Update with `lo = mid` or `lo = mid + 1`?

3. **Integer overflow**
   - Use `mid = lo + (hi - lo) / 2` instead of `(lo + hi) / 2`

4. **Wrong search bounds**
   - Ensure the answer is within `[lo, hi]`
   - Check boundary conditions

5. **Wrong monotonicity**
   - Verify the check function is monotonic
   - If `check(x)` is true, does that tell us about `check(x+1)`?

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Binary Search (concept) | Various | Practice implementing from scratch |
| Number of Pairs | CSES | [cses.fi](https://cses.fi/problemset/task/1077) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Cow Dance Show | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=690) |
| Convention | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=858) |
| Social Distancing | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1038) |
| Angry Cows | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=594) |
| Factory Machines | CSES | [cses.fi](https://cses.fi/problemset/task/1620) |
| Array Division | CSES | [cses.fi](https://cses.fi/problemset/task/1085) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Wormhole Sort | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=992) |
| Loan Repayment | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=991) |
| Planet Queries I | CSES | [cses.fi](https://cses.fi/problemset/task/1750) |

---

## Key Takeaways

1. ✅ **Binary search on answer** is the most important pattern for Silver
2. ✅ Always verify **monotonicity** before applying binary search
3. ✅ Use `lower_bound` / `upper_bound` for sorted array queries
4. ✅ Be careful with **loop termination** conditions
5. ✅ Practice identifying when a problem can be solved with binary search
