# 🏋️ Daily Pattern Recognition Exercises

## How to Use This File

**Every day, spend 15-20 minutes on classification drills BEFORE solving problems.**

This builds the neural pathways for pattern recognition.

---

## Week 1: Algorithm Classification Drill

### Day 1-2: Binary Search vs Greedy

Read each problem statement. Classify as **Binary Search** or **Greedy** (or neither).

| # | Problem | Your Guess | Actual | ✓/✗ |
|---|---------|------------|--------|-----|
| 1 | "Select maximum non-overlapping intervals" | | Greedy | |
| 2 | "Minimize maximum load across K workers" | | Binary Search | |
| 3 | "Find minimum radius to cover all points with K circles" | | Binary Search | |
| 4 | "Pair items to minimize maximum pair sum" | | Greedy | |
| 5 | "Find if possible to finish all tasks before deadline" | | Binary Search | |
| 6 | "Maximum meetings in one room" | | Greedy | |
| 7 | "Minimum buses needed if each holds K people" | | Binary Search (or Greedy) | |
| 8 | "Place K items to maximize minimum gap" | | Binary Search | |

**Reflection:** What phrases helped you identify Binary Search vs Greedy?

---

### Day 3-4: Prefix Sums vs Two Pointers

| # | Problem | Your Guess | Actual | ✓/✗ |
|---|---------|------------|--------|-----|
| 1 | "Sum of elements from index L to R" | | Prefix Sums | |
| 2 | "Longest subarray with sum ≤ K" | | Two Pointers | |
| 3 | "Count subarrays with sum = K" | | Prefix Sums + HashMap | |
| 4 | "Two numbers that sum to target (sorted array)" | | Two Pointers | |
| 5 | "Number of elements in range [L,R] equal to X" | | Prefix Sums | |
| 6 | "Shortest subarray with sum ≥ K" | | Two Pointers | |
| 7 | "Count pairs with difference ≤ D" | | Two Pointers | |
| 8 | "Range XOR query" | | Prefix Sums (XOR) | |

**Reflection:** When do you use Prefix Sums vs Two Pointers?

---

### Day 5-7: Mixed Classification

| # | Problem | Your Guess | Actual |
|---|---------|------------|--------|
| 1 | "Count connected regions in grid" | | Flood Fill |
| 2 | "Minimum spanning tree weight" | | Greedy (Kruskal) |
| 3 | "K-th smallest in sorted matrix" | | Binary Search |
| 4 | "Shortest path in unweighted graph" | | BFS |
| 5 | "Maximum subarray sum" | | DP / Kadane |
| 6 | "Partition array into K parts, minimize max part sum" | | Binary Search |
| 7 | "Find cycle in directed graph" | | DFS |
| 8 | "Count inversions in array" | | Merge Sort / BIT |
| 9 | "Longest path in DAG" | | Topological Sort + DP |
| 10 | "Minimum time for N machines to produce K items" | | Binary Search |

---

## Week 2: Real USACO Problem Classification

Go to each problem link. **Read only. Do NOT solve yet.** Just classify.

### Day 1-2

| Problem | Link | Your Guess | Check Editorial |
|---------|------|------------|-----------------|
| Cow Dance Show | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=690) | | |
| Breed Counting | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=572) | | |
| Moocast | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=668) | | |
| Convention | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=858) | | |

### Day 3-4

| Problem | Link | Your Guess | Check Editorial |
|---------|------|------------|-----------------|
| Counting Rooms | [Link](https://cses.fi/problemset/task/1192) | | |
| Diamond Collector | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=643) | | |
| Social Distancing | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=1038) | | |
| Subsequences Summing to Sevens | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=595) | | |

### Day 5-7

| Problem | Link | Your Guess | Check Editorial |
|---------|------|------------|-----------------|
| Wormhole Sort | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=992) | | |
| Icy Perimeter | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=895) | | |
| Angry Cows | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=594) | | |
| Rest Stops | [Link](http://usaco.org/index.php?page=viewproblem2&cpid=810) | | |

---

## Week 3-4: Deep Dive Binary Search

### The "Why Binary Search?" Journal

For each problem you solve, fill this out:

```
Problem: ________________
Date: ________________

1. What phrase in the problem hinted at binary search?
   _________________________________________________

2. What is the search range [lo, hi]?
   lo = _____________ (why?)
   hi = _____________ (why?)

3. What does check(mid) verify?
   _________________________________________________

4. Why is it monotonic?
   - If check(mid) is TRUE, then check(mid+1) is _______
   - If check(mid) is FALSE, then check(mid-1) is _______

5. Time complexity of check(mid): O(_______)

6. Pattern for future: ________________________________
```

### Binary Search Problem Set (in order)

| # | Problem | Difficulty | Key Pattern |
|---|---------|------------|-------------|
| 1 | Factory Machines (CSES) | ⭐⭐ | Minimize time to produce K items |
| 2 | Array Division (CSES) | ⭐⭐ | Minimize maximum partition sum |
| 3 | Cow Dance Show (USACO) | ⭐⭐ | Minimize max using priority queue check |
| 4 | Convention (USACO) | ⭐⭐⭐ | Minimize max wait time |
| 5 | Social Distancing (USACO) | ⭐⭐⭐ | Maximize minimum distance |
| 6 | Angry Cows (USACO) | ⭐⭐⭐ | Binary search + simulation |
| 7 | Wormhole Sort (USACO) | ⭐⭐⭐⭐ | Binary search + graph connectivity |
| 8 | Loan Repayment (USACO) | ⭐⭐⭐⭐ | Tricky binary search bounds |

---

## Week 5-6: Graph Focus

Since graphs are your weakest, here's a progression:

### Graph Problem Ladder

| # | Problem | Focus | Prerequisite |
|---|---------|-------|--------------|
| 1 | Counting Rooms (CSES) | Basic flood fill | None |
| 2 | Building Roads (CSES) | Connected components | #1 |
| 3 | Message Route (CSES) | BFS shortest path | #1 |
| 4 | Moocast (USACO) | Graph construction + DFS | #2 |
| 5 | Fence Planning (USACO) | Components + bounding box | #2 |
| 6 | Building Teams (CSES) | Bipartite check | #3 |
| 7 | Wormhole Sort (USACO) | Binary search + connectivity | #2, Binary Search |
| 8 | Closing the Farm (USACO) | Reverse thinking + DSU | #2 |

---

## 📊 Progress Tracker

### Classification Accuracy

| Week | Problems Classified | Correct | Accuracy |
|------|--------------------| --------|----------|
| 1 | | | % |
| 2 | | | % |
| 3 | | | % |
| 4 | | | % |

**Goal: 80%+ accuracy by Week 4**

### Binary Search Recognition

| Pattern | Times Seen | Times Recognized | Rate |
|---------|------------|------------------|------|
| "Minimize maximum" | | | % |
| "Maximize minimum" | | | % |
| "Smallest X such that" | | | % |
| "Is it possible" | | | % |

---

## 💡 Key Insights Log

Write down "aha moments" as you discover them:

```
Date: _______
Problem: _______
Insight: _______________________________________________________
_______________________________________________________________
```

Example:
```
Date: Jan 15
Problem: Convention
Insight: When I see "minimize the maximum waiting time", I should 
immediately think binary search. The key is that if waiting time T 
works, then T+1 also works (monotonic!). The check function simulates 
greedily assigning cows to buses.
```
