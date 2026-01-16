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

---

## 🧠 Pattern Recognition: When to Use Binary Search

### Trigger Phrases (MEMORIZE THESE!)

When you see these in a problem, **think binary search on answer:**

| Trigger Phrase | Binary Search On... |
|----------------|---------------------|
| "**Minimize the maximum**..." | The maximum value |
| "**Maximize the minimum**..." | The minimum value |
| "**Find the smallest X such that**..." | X |
| "**Find the largest X such that**..." | X |
| "**Is it possible to achieve X?**" | X (if you can check efficiently) |
| "**At least K**" / "**At most K**" | The threshold value |
| "**Minimum time/cost to...**" | Time or cost |
| "**K-th smallest/largest**" | The value itself |

### Problem Characteristics

**Binary search on answer is likely needed when:**

1. ✅ You're asked to **optimize** (minimize/maximize) something
2. ✅ The answer has a **monotonic property**:
   - If X works, then X+1 also works (or vice versa)
3. ✅ You can write a **check(X)** function efficiently
4. ✅ The search space is **large** but **ordered**
5. ✅ Direct computation is hard, but **verification is easy**

### The Monotonicity Test

Before using binary search, verify:

```
If check(mid) = TRUE:
  → What about check(mid + 1)? Should be TRUE or FALSE consistently
  → What about check(mid - 1)? Should be FALSE or TRUE consistently

The function must be monotonic (all TRUE then all FALSE, or vice versa)
```

**Example:**
- "Can we place K cows with minimum distance ≥ D?"
- If TRUE for D=5, then TRUE for D=4, D=3, D=2... (easier constraints)
- If FALSE for D=10, then FALSE for D=11, D=12... (harder constraints)
- ✅ Monotonic! Binary search works.

### Binary Search vs Other Techniques

| Problem Type | Binary Search? | Why/Alternative |
|--------------|----------------|-----------------|
| Find element in sorted array | **Yes** | Classic binary search |
| Minimize maximum partition sum | **Yes** | Binary search on max sum |
| Find longest subarray with sum ≤ K | **No** | Use two pointers |
| Minimize total cost | **Maybe** | Check if monotonic; might be DP |
| Find K-th smallest element | **Yes** | Binary search on value, count ≤ X |
| Shortest path | **No** | Use BFS/Dijkstra |

### Pattern Recognition Exercises

**Exercise 1:** Is it binary search on answer?

| Problem | Binary Search? | What to search on? |
|---------|----------------|-------------------|
| "Minimize time to produce N items with K machines" | | |
| "Find two numbers that sum to target" | | |
| "Maximum minimum distance between K points" | | |
| "Longest increasing subsequence" | | |
| "Minimum radius to cover all points with one circle" | | |
| "Count pairs with difference ≤ D" | | |

<details>
<summary>Answers</summary>

1. **Yes** - Binary search on time T, check if can produce N items in time T
2. **No** - Use hash set or two pointers
3. **Yes** - Binary search on distance D, check if can place K points
4. **No** - Use DP (though binary search helps optimize to O(N log N))
5. **Yes** - Binary search on radius R, check if one circle covers all
6. **Partially** - Can use binary search per element, or two pointers

</details>

**Exercise 2:** Define the check function

For each problem, write what `check(mid)` should verify:

1. "Divide array into K parts to minimize maximum part sum"
   - check(S) = ________________________

2. "Place N cows in stalls to maximize minimum distance"  
   - check(D) = ________________________

3. "Find minimum speed to travel distance in time T"
   - check(V) = ________________________

<details>
<summary>Answers</summary>

1. check(S) = "Can we divide array into ≤ K parts, each with sum ≤ S?"
2. check(D) = "Can we place N cows such that minimum distance ≥ D?"
3. check(V) = "Can we travel the required distance in time ≤ T at speed V?"

</details>

**Exercise 3:** Find the search bounds

| Problem | lo | hi |
|---------|----|----|
| Minimize max partition sum | | |
| Maximize min distance (stalls from 0 to 10^9) | | |
| Find K-th smallest in array with values 1 to 10^6 | | |

<details>
<summary>Answers</summary>

1. lo = max element (one element per partition), hi = total sum (one partition)
2. lo = 0 (or 1), hi = 10^9 (max possible distance)
3. lo = 1, hi = 10^6 (value range)

</details>

### Quick Decision Flowchart

```
Is the problem asking to OPTIMIZE something (min/max)?
  │
  ├─ NO → Probably not binary search on answer
  │
  └─ YES → Can you write check(X) efficiently?
              │
              ├─ NO → Try another approach
              │
              └─ YES → Is check(X) MONOTONIC?
                         │
                         ├─ NO → Not binary search
                         │
                         └─ YES → ✅ USE BINARY SEARCH!
```

---

## Key Takeaways

1. ✅ **Binary search on answer** is the most important pattern for Silver
2. ✅ Always verify **monotonicity** before applying binary search
3. ✅ Use `lower_bound` / `upper_bound` for sorted array queries
4. ✅ Be careful with **loop termination** conditions
5. ✅ Practice identifying when a problem can be solved with binary search
6. ✅ **Recognition:** "Minimize maximum" / "Maximize minimum" → Binary search!