# 🧠 Pattern Recognition Guide

> **The #1 skill for competitive programming:** Recognizing which algorithm to use.

This guide focuses on building the **intuition** to connect problems to solutions.

---

## The Pattern Recognition Framework

When you read a problem, ask these questions **in order:**

### Step 1: What are the constraints?

| N (input size) | Target Complexity | Likely Algorithms |
|----------------|-------------------|-------------------|
| N ≤ 10 | O(N!) | Brute force, permutations |
| N ≤ 20 | O(2^N) | Bitmask DP, subset enumeration |
| N ≤ 500 | O(N³) | Floyd-Warshall, 3 nested loops |
| N ≤ 5,000 | O(N²) | Simple DP, brute force pairs |
| N ≤ 100,000 | O(N log N) | **Sorting, Binary Search, Two Pointers** |
| N ≤ 1,000,000 | O(N) | Prefix sums, linear scan, hashing |

**This is your first filter!** If N = 100,000, you CANNOT use O(N²).

### Step 2: What is the question asking?

| Question Type | Think About... |
|---------------|----------------|
| "Find minimum X such that..." | **Binary Search on Answer** |
| "Find maximum X such that..." | **Binary Search on Answer** |
| "Count pairs/subarrays with property" | Prefix Sums, Two Pointers, Hashing |
| "Find connected regions" | Flood Fill, DFS/BFS |
| "Shortest path" | BFS (unweighted), Dijkstra (weighted) |
| "Is it possible to..." | Often Greedy or Binary Search |
| "Process events in order" | Sorting + Sweep Line |

### Step 3: What structure does the data have?

| Data Structure | Think About... |
|----------------|----------------|
| Linear array | Prefix sums, Two pointers, DP |
| 2D grid | Flood fill, 2D prefix sums |
| Graph (nodes + edges) | DFS, BFS, Union-Find |
| Tree | DFS, subtree properties |
| Intervals | Sorting by endpoint, Sweep line |
| Pairs/coordinates | Sorting, Binary search |

---

## 🎯 Binary Search Pattern Recognition

### The Golden Rule

> **Binary Search on Answer works when:**
> 1. You're asked to find MIN or MAX of something
> 2. The answer has a **monotonic** property (if X works, then X+1 also works, OR vice versa)

### Trigger Phrases for Binary Search

When you see these phrases, **think binary search:**

| Phrase | Why Binary Search? |
|--------|-------------------|
| "Minimize the maximum..." | Binary search on the maximum value |
| "Maximize the minimum..." | Binary search on the minimum value |
| "Find the smallest X such that..." | Binary search on X |
| "Find the largest X such that..." | Binary search on X |
| "Is it possible to achieve X?" | If you can check this, binary search on X |
| "At least K" / "At most K" | Often binary search on the threshold |

### Binary Search Mental Checklist

When you suspect binary search, verify:

```
□ Can I define a clear search range [lo, hi]?
□ Can I write a check(mid) function?
□ Is check(mid) monotonic? 
  - If check(mid) is true, what about check(mid+1)?
  - If check(mid) is false, what about check(mid-1)?
□ What's the time complexity of check(mid)?
  - Must be efficient enough: O(N) or O(N log N) usually
```

### Example Pattern Matching

**Problem:** "Place K cows in N stalls to maximize the minimum distance between any two cows."

**Analysis:**
1. ✅ "Maximize the minimum" → BINARY SEARCH TRIGGER
2. ✅ Search range: [1, max_stall - min_stall]
3. ✅ check(D) = "Can we place K cows with min distance ≥ D?"
4. ✅ Monotonic: If we can achieve distance D, we can achieve D-1 (easier)
5. ✅ check(D) is O(N) with greedy placement

**Verdict:** Binary search on the answer!

---

## 🔄 Pattern Recognition Exercises

### Exercise 1: Classify These Problems (Don't Solve, Just Identify)

For each problem, identify which algorithm category it likely belongs to:

1. "Given N intervals, find the maximum number of non-overlapping intervals."
   - Hint: What are we maximizing? What's the structure?
   
2. "Given an array, find the longest subarray with sum ≤ K."
   - Hint: What's the constraint type? Linear array...
   
3. "Given N points, find if we can cover all with K circles of radius R."
   - Hint: "Is it possible to..." with a parameter R...
   
4. "Count the number of connected regions in a grid."
   - Hint: What's the structure? What are we counting?
   
5. "Find the minimum time to complete all tasks if we have K workers."
   - Hint: "Minimize" + "is it possible in time T?"

<details>
<summary>Answers</summary>

1. **Greedy** (Activity Selection - sort by end time)
2. **Two Pointers / Sliding Window** (subarray with constraint)
3. **Binary Search on Answer** (binary search on R, check if possible)
4. **Flood Fill / DFS** (connected components on grid)
5. **Binary Search on Answer** (binary search on time T)

</details>

### Exercise 2: Find the Binary Search

For each problem, determine:
- Is this binary search on answer?
- If yes, what is the search range?
- What would check(mid) verify?

1. "Divide array into K subarrays to minimize the maximum subarray sum."

2. "Find the minimum speed to travel from A to B in time T."

3. "Place N trees such that the minimum distance between any two is maximized."

4. "Find the K-th smallest element in a sorted matrix."

<details>
<summary>Answers</summary>

1. ✅ Binary search on max sum. Range: [max_element, total_sum]. check(S) = can divide into ≤K parts with each ≤S?

2. ✅ Binary search on speed. Range: [0, max_needed]. check(V) = can reach in time ≤T at speed V?

3. ✅ Binary search on min distance. Range: [0, max_gap]. check(D) = can place N trees with gap ≥D?

4. ✅ Binary search on value. Range: [min, max]. check(X) = are there ≥K elements ≤X?

</details>

---

## 🏋️ Deliberate Practice Plan

### Week 1-2: Pattern Classification Drill

**Goal:** Read problems WITHOUT solving. Just classify.

1. Go to [USACO Problems](http://usaco.org/index.php?page=contests)
2. Read 5 Silver problems per day
3. For each, write down:
   - Suspected algorithm
   - Why you think so
   - Key constraint (N size)
4. Check editorials to verify your guess
5. Track accuracy: aim for 70%+ by end of week 2

### Week 3-4: Targeted Binary Search Practice

**Goal:** Build binary search intuition specifically.

| Day | Focus | Problems |
|-----|-------|----------|
| 1-2 | "Minimize maximum" problems | Array Division (CSES), Convention (USACO) |
| 3-4 | "Maximize minimum" problems | Aggressive Cows (SPOJ), Social Distancing (USACO) |
| 5-6 | "Is it possible?" problems | Factory Machines (CSES), Cow Dance Show (USACO) |
| 7 | Mixed practice | Random Silver problems |

**After each problem:**
- Write down what made you recognize it as binary search
- Note the check function pattern

### Week 5-6: Mixed Algorithm Recognition

**Goal:** Random problems, identify algorithm first.

1. Pick random Silver problem
2. Spend 5 minutes ONLY on classification (no coding)
3. Write your guess
4. Read editorial first line to check
5. Then solve if correct, or study if wrong

---

## 📝 Pattern Journal Template

Keep a journal of patterns you discover:

```markdown
## Problem: [Name]
**Source:** [USACO/CSES/etc.]
**My Initial Guess:** [Algorithm]
**Correct Algorithm:** [Algorithm]
**Key Insight:** [What should have triggered recognition?]
**Pattern to Remember:** [General rule for future]

Example:
## Problem: Convention
**Source:** USACO Silver Dec 2018
**My Initial Guess:** Greedy
**Correct Algorithm:** Binary Search + Greedy Check
**Key Insight:** "Minimize the maximum waiting time" = binary search on answer
**Pattern to Remember:** "Minimize maximum" almost always = binary search
```

---

## 🎯 Recognition Cheat Sheet

Print this and review before contests:

### Binary Search Triggers
- "Minimize the maximum"
- "Maximize the minimum"  
- "Smallest/largest X such that"
- "Is it possible to achieve X"

### Two Pointers Triggers
- "Longest subarray with..."
- "Count subarrays/pairs with..."
- "Two elements that sum to..."
- Sorted array + pair condition

### Prefix Sum Triggers
- "Sum of range [L, R]"
- "Count of X in range"
- "Subarray sum equals K"
- Multiple range queries

### Graph/Flood Fill Triggers
- "Connected" / "Reachable"
- "Regions" / "Components"
- Grid with obstacles
- Nodes and edges explicitly given

### Greedy Triggers
- "Maximum number of non-overlapping"
- "Minimum number to cover all"
- Exchange argument seems to work
- Local choice doesn't affect future options
