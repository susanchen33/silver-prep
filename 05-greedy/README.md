# 📚 Topic 5: Greedy Algorithms

## Overview

Greedy algorithms make the **locally optimal choice** at each step, hoping to find a global optimum. The challenge is **proving** that the greedy approach actually works for a given problem.

---

## Key Concepts

### 1. When Does Greedy Work?

Greedy works when:
1. **Optimal substructure:** Optimal solution contains optimal solutions to subproblems
2. **Greedy choice property:** A locally optimal choice leads to a globally optimal solution

**How to verify greedy works:**
- **Exchange argument:** Show swapping any non-greedy choice with the greedy choice doesn't make the solution worse
- **Stay ahead argument:** Show greedy solution is always at least as good at each step

### 2. Classic Greedy Problems

#### Activity Selection (Interval Scheduling)

Select maximum non-overlapping intervals.

**Greedy strategy:** Always pick the interval that **ends earliest**.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start, end;
};

int maxNonOverlapping(vector<Interval>& intervals) {
    // Sort by end time
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a.end < b.end;
    });
    
    int count = 0;
    int lastEnd = -1;
    
    for (auto& interval : intervals) {
        if (interval.start >= lastEnd) {  // Can take this interval
            count++;
            lastEnd = interval.end;
        }
    }
    
    return count;
}
```

#### Interval Covering

Cover all points with minimum intervals.

**Greedy strategy:** For each uncovered point, pick the interval that starts before it and extends furthest.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

int minIntervalCover(vector<pair<int,int>>& intervals, int target) {
    sort(intervals.begin(), intervals.end());
    
    int count = 0;
    int covered = 0;  // Current rightmost covered position
    int i = 0;
    
    while (covered < target) {
        int maxReach = covered;
        
        // Find interval starting <= covered that reaches furthest
        while (i < intervals.size() && intervals[i].first <= covered) {
            maxReach = max(maxReach, intervals[i].second);
            i++;
        }
        
        if (maxReach == covered) return -1;  // Can't extend
        
        covered = maxReach;
        count++;
    }
    
    return count;
}
```

#### Fractional Knapsack

Take items with maximum value-to-weight ratio first.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

double fractionalKnapsack(vector<pair<int,int>>& items, int capacity) {
    // items[i] = {value, weight}
    // Sort by value/weight ratio descending
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });
    
    double totalValue = 0;
    int remaining = capacity;
    
    for (auto& [value, weight] : items) {
        if (weight <= remaining) {
            totalValue += value;
            remaining -= weight;
        } else {
            totalValue += (double)value * remaining / weight;
            break;
        }
    }
    
    return totalValue;
}
```

### 3. Exchange Arguments

Prove greedy is optimal by showing any swap to a non-greedy choice doesn't help.

**Example: Job Scheduling with Deadlines**

Given jobs with deadlines and penalties, minimize total penalty for late jobs.

**Greedy:** Process jobs in order of deadline (earliest deadline first).

**Proof:** Suppose optimal solution processes job B before job A, but deadline(A) < deadline(B).
- If both are on time: swapping doesn't change penalty
- If A is late, B is on time: swapping might make A on time, B on time (better or same)
- Both late: swapping doesn't change which are late

Therefore, sorting by deadline is at least as good as any other order.

---

## Common Patterns

### Pattern 1: Minimum Spanning Tree (MST)

**Greedy:** Kruskal's or Prim's algorithm.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find for Kruskal's
struct DSU {
    vector<int> parent, rank_;
    
    DSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

// edges[i] = {weight, u, v}
long long kruskal(int n, vector<tuple<int,int,int>>& edges) {
    sort(edges.begin(), edges.end());  // Sort by weight
    
    DSU dsu(n);
    long long totalWeight = 0;
    int edgeCount = 0;
    
    for (auto& [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            totalWeight += w;
            edgeCount++;
            if (edgeCount == n - 1) break;
        }
    }
    
    return (edgeCount == n - 1) ? totalWeight : -1;  // -1 if disconnected
}
```

### Pattern 2: Huffman Coding

Build optimal prefix code.

**Greedy:** Always merge two lowest frequency nodes.

```cpp
#include <queue>
#include <vector>
using namespace std;

long long huffmanCost(vector<int>& freq) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    
    for (int f : freq) {
        pq.push(f);
    }
    
    long long totalCost = 0;
    
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        totalCost += a + b;
        pq.push(a + b);
    }
    
    return totalCost;
}
```

### Pattern 3: Optimal Task Assignment

Pair items to minimize/maximize something.

**Example:** Pair N workers with N tasks to minimize maximum completion time.

**Greedy:** Sort both, pair smallest worker with smallest task.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

int minMaxCompletion(vector<int>& workers, vector<int>& tasks) {
    sort(workers.begin(), workers.end());
    sort(tasks.begin(), tasks.end());
    
    int maxTime = 0;
    for (int i = 0; i < workers.size(); i++) {
        maxTime = max(maxTime, workers[i] + tasks[i]);
    }
    
    return maxTime;
}
```

### Pattern 4: "Stay Ahead" Argument

Show greedy is always at least as good as optimal at each step.

Used in activity selection proof:
- After selecting k intervals greedily, the last interval ends no later than in optimal solution
- Therefore, we can always match or beat optimal

---

## Time Complexity

| Algorithm | Complexity |
|-----------|------------|
| Activity Selection | O(N log N) |
| Fractional Knapsack | O(N log N) |
| Kruskal's MST | O(E log E) |
| Huffman Coding | O(N log N) |

---

## Common Mistakes

1. **Applying greedy when it doesn't work**
   - 0/1 Knapsack is NOT greedy (requires DP)
   - Always verify with exchange argument or examples

2. **Wrong sorting criteria**
   - Activity selection: sort by END time, not start time
   - Think carefully about what to optimize

3. **Edge cases**
   - Empty input
   - All same values
   - Ties in sorting criteria

4. **Not proving correctness**
   - Test greedy idea on examples before implementing
   - Try to find a counterexample

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Stick Lengths | CSES | [cses.fi](https://cses.fi/problemset/task/1074) |
| Rest Stops | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=810) |
| High Card Low Card | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=573) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Movie Festival | CSES | [cses.fi](https://cses.fi/problemset/task/1629) |
| Coin Piles | CSES | [cses.fi](https://cses.fi/problemset/task/1754) |
| Berry Picking | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=990) |
| Stuck in a Rut | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1061) |
| Why Did the Cow Cross the Road II | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=715) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Cereal | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1039) |
| Split the Attractions | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1062) |
| Tasks and Deadlines | CSES | [cses.fi](https://cses.fi/problemset/task/1630) |

---

## Key Takeaways

1. ✅ Greedy makes locally optimal choices
2. ✅ **Exchange argument:** prove swapping doesn't help
3. ✅ **Stay ahead argument:** prove greedy is always competitive
4. ✅ Common patterns: activity selection, MST, Huffman
5. ✅ Always verify greedy works before implementing!
