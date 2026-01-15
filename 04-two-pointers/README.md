# 📚 Topic 4: Two Pointers & Sliding Window

## Overview

Two pointers is a technique where two pointers iterate through an array in a coordinated way. Combined with the sliding window pattern, it solves many problems in **O(N)** time that would otherwise require **O(N²)**.

---

## Key Concepts

### 1. Two Pointers - Opposite Direction

Two pointers start at opposite ends and move toward each other.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// Example: Find if there exist two numbers that sum to target
bool twoSum(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return true;
        } else if (sum < target) {
            left++;   // Need larger sum
        } else {
            right--;  // Need smaller sum
        }
    }
    
    return false;
}
```

### 2. Two Pointers - Same Direction

Both pointers move in the same direction, forming a "window."

```cpp
#include <vector>
using namespace std;

// Example: Find longest subarray with sum <= target
int longestSubarray(vector<int>& arr, int target) {
    int left = 0;
    long long sum = 0;
    int maxLen = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];
        
        // Shrink window until sum <= target
        while (sum > target && left <= right) {
            sum -= arr[left];
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

### 3. Sliding Window - Fixed Size

Window has a fixed size K.

```cpp
#include <vector>
using namespace std;

// Example: Maximum sum of K consecutive elements
long long maxSumK(vector<int>& arr, int k) {
    // Calculate sum of first window
    long long windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    
    long long maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < arr.size(); i++) {
        windowSum += arr[i] - arr[i - k];  // Add new, remove old
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

### 4. Sliding Window - Variable Size

Window size changes based on conditions.

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

// Example: Longest substring with at most K distinct characters
int longestKDistinct(string& s, int k) {
    unordered_map<char, int> count;
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        count[s[right]]++;
        
        // Shrink until we have at most K distinct
        while (count.size() > k) {
            count[s[left]]--;
            if (count[s[left]] == 0) {
                count.erase(s[left]);
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

---

## Common Patterns

### Pattern 1: Closest Pair in Sorted Array

Find pair with difference closest to target.

```cpp
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

pair<int,int> closestPair(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    
    int left = 0, right = arr.size() - 1;
    int bestDiff = INT_MAX;
    pair<int,int> result;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        int diff = abs(sum - target);
        
        if (diff < bestDiff) {
            bestDiff = diff;
            result = {arr[left], arr[right]};
        }
        
        if (sum < target) {
            left++;
        } else if (sum > target) {
            right--;
        } else {
            break;  // Exact match
        }
    }
    
    return result;
}
```

### Pattern 2: Count Pairs

Count pairs satisfying a condition.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// Count pairs where difference <= D
long long countPairs(vector<int>& arr, int D) {
    sort(arr.begin(), arr.end());
    
    long long count = 0;
    int right = 0;
    
    for (int left = 0; left < arr.size(); left++) {
        // Move right to first position where arr[right] - arr[left] > D
        while (right < arr.size() && arr[right] - arr[left] <= D) {
            right++;
        }
        // All elements from left+1 to right-1 form valid pairs with left
        count += right - left - 1;
    }
    
    return count;
}
```

### Pattern 3: Minimum Window Containing Target

Find smallest window containing all required elements.

```cpp
#include <string>
#include <unordered_map>
using namespace std;

string minWindow(string s, string t) {
    unordered_map<char, int> need, have;
    for (char c : t) need[c]++;
    
    int required = need.size();
    int formed = 0;
    
    int left = 0;
    int minLen = INT_MAX;
    int minStart = 0;
    
    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        have[c]++;
        
        if (need.count(c) && have[c] == need[c]) {
            formed++;
        }
        
        // Try to shrink
        while (formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            char leftChar = s[left];
            have[leftChar]--;
            if (need.count(leftChar) && have[leftChar] < need[leftChar]) {
                formed--;
            }
            left++;
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}
```

### Pattern 4: At Most K (USACO Common!)

Count subarrays with at most K of something.

```cpp
// Number of subarrays with at most K distinct elements
// Trick: atMost(K) - atMost(K-1) = exactly K

long long atMostK(vector<int>& arr, int k) {
    if (k < 0) return 0;
    
    unordered_map<int, int> count;
    long long result = 0;
    int left = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        count[arr[right]]++;
        
        while (count.size() > k) {
            count[arr[left]]--;
            if (count[arr[left]] == 0) {
                count.erase(arr[left]);
            }
            left++;
        }
        
        // All subarrays ending at right with start in [left, right]
        result += right - left + 1;
    }
    
    return result;
}

long long exactlyK(vector<int>& arr, int k) {
    return atMostK(arr, k) - atMostK(arr, k - 1);
}
```

---

## Time Complexity

| Pattern | Complexity |
|---------|------------|
| Two pointers (opposite) | O(N) |
| Two pointers (same direction) | O(N) |
| Fixed sliding window | O(N) |
| Variable sliding window | O(N) |

All patterns are O(N) because each element is visited at most twice (once by each pointer).

---

## Common Mistakes

1. **Not sorting when required**
   - Many two-pointer techniques require sorted input

2. **Incorrect window boundaries**
   - Off-by-one in window size calculations
   - `right - left + 1` for inclusive window

3. **Forgetting edge cases**
   - Empty array
   - Window larger than array
   - All elements same

4. **Wrong shrinking condition**
   - Shrink with `while`, not `if` (might need multiple shrinks)

5. **Integer overflow in sums**
   - Use `long long` when summing many elements

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Sum of Two Values | CSES | [cses.fi](https://cses.fi/problemset/task/1640) |
| Diamond Collector | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=643) |
| Subarray Sums I | CSES | [cses.fi](https://cses.fi/problemset/task/1660) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Books | Codeforces | [codeforces.com](https://codeforces.com/problemset/problem/279/B) |
| Sum of Three Values | CSES | [cses.fi](https://cses.fi/problemset/task/1641) |
| Paired Up | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=738) |
| Sleepy Cow Herding | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=918) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Maximum Subarray Sum II | CSES | [cses.fi](https://cses.fi/problemset/task/1644) |
| Triangles | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1015) |
| Cellphone Typing | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1231) |

---

## Key Takeaways

1. ✅ Two pointers converts O(N²) to O(N) for many problems
2. ✅ **Opposite direction:** sorted arrays, find pairs
3. ✅ **Same direction:** subarrays, sliding windows
4. ✅ "At most K" - "at most K-1" = "exactly K" trick
5. ✅ Each element is processed at most twice → O(N)
