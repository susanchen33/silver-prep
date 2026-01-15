# 🚀 Quick Start Guide

Welcome to your USACO Silver preparation! This guide will get you started immediately.

---

## Day 1: Setup

### 1. Set Your Target Date
Open `progress.md` and fill in:
- **Start Date:** Today's date
- **Target Contest:** Next USACO contest (check [usaco.org](http://usaco.org))
- **Days Until Contest:** Calculate and write it down

### 2. Test Your Environment
Create a test file to ensure your C++ setup works:

```cpp
// test.cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Setup working!" << endl;
    return 0;
}
```

Compile and run:
```bash
g++ -std=c++17 -O2 -o test test.cpp
./test
```

### 3. Familiarize with File I/O
USACO problems require reading from files:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    
    int n;
    cin >> n;
    cout << n * 2 << endl;
    
    return 0;
}
```

---

## Week 1: Start with Sorting

### Study Plan
1. **Read:** `01-sorting/README.md` thoroughly
2. **Code:** Implement each code example yourself
3. **Practice:** Start with Easy problems, then Medium

### First Problem: Lifeguards
1. Go to [USACO Lifeguards](http://usaco.org/index.php?page=viewproblem2&cpid=786)
2. Read the problem carefully
3. Think for 10-15 minutes before coding
4. Implement your solution
5. Test with sample cases
6. Submit and check results

### Daily Routine (1-2 hours)
| Time | Activity |
|------|----------|
| 0-15 min | Review previous day's concepts |
| 15-60 min | Solve 1-2 problems |
| 60-90 min | Read solutions, understand alternatives |
| 90-120 min | Study next topic's README |

---

## How to Approach a Problem

### Step 1: Read Carefully (5 min)
- What's the input format?
- What's the output format?
- What are the constraints? (This tells you time complexity!)
  - N ≤ 1000 → O(N²) okay
  - N ≤ 100,000 → Need O(N log N) or O(N)
  - N ≤ 1,000,000 → Need O(N) or O(log N)

### Step 2: Think Before Coding (10-15 min)
- What topic does this relate to?
- What's the key insight?
- Write pseudocode or draw diagrams

### Step 3: Implement (20-30 min)
- Use your template
- Start simple, optimize later
- Comment tricky parts

### Step 4: Test (10 min)
- Run sample test cases
- Create edge cases:
  - N = 1 (minimum input)
  - All same values
  - Maximum values
  - Sorted / reverse sorted

### Step 5: Submit & Learn
- If WA (Wrong Answer): Debug with small cases
- If TLE (Time Limit Exceeded): Optimize algorithm
- If AC (Accepted): Read editorial for alternative approaches

---

## Recommended Order

Follow this order for maximum learning:

```
Week 1-2: Foundations
├── 01-sorting (3-4 days)
└── 02-prefix-sums (4-5 days)

Week 2-3: Search Techniques
├── 03-binary-search (5-6 days)
└── 04-two-pointers (4-5 days)

Week 4: Decision Making
└── 05-greedy (5-6 days)

Week 5: Graph Foundations
├── 06-flood-fill (5-6 days)
└── 07-graphs (6-7 days)

Week 6: Trees & Review
├── 08-trees (5-6 days)
└── Mock contests & review
```

---

## Essential Resources

### Must-Have Bookmarks
1. [USACO Website](http://usaco.org/) - Official problems & contests
2. [USACO Guide](https://usaco.guide/) - Free comprehensive guide
3. [CSES Problem Set](https://cses.fi/problemset/) - Great practice problems
4. [CP Algorithms](https://cp-algorithms.com/) - Algorithm reference

### When You're Stuck
1. Think for at least 20-30 minutes first
2. Draw diagrams, trace through examples
3. Check the USACO Guide for hints
4. Read the editorial (after honest attempt!)
5. Implement the solution yourself (don't copy-paste)

---

## Common Beginner Mistakes

### 1. Integer Overflow
```cpp
// BAD
int a = 100000, b = 100000;
int product = a * b;  // OVERFLOW!

// GOOD
long long a = 100000, b = 100000;
long long product = a * b;  // Safe

// OR
int a = 100000, b = 100000;
long long product = 1LL * a * b;  // Cast to long long
```

### 2. Array Index Out of Bounds
```cpp
// BAD
int arr[100];
arr[100] = 5;  // OUT OF BOUNDS! Valid indices are 0-99

// GOOD
int arr[101];  // Extra space for safety
arr[100] = 5;  // Safe
```

### 3. Forgetting File I/O
```cpp
// For USACO problem "cowdance":
freopen("cowdance.in", "r", stdin);
freopen("cowdance.out", "w", stdout);
```

### 4. Not Testing Edge Cases
Always test:
- Minimum input (N=1)
- Maximum input values
- All same values
- Already sorted / reverse sorted

---

## Your First Week Checklist

- [ ] Set up C++ environment
- [ ] Test with a simple program
- [ ] Read Sorting topic README
- [ ] Solve 2 Easy sorting problems
- [ ] Solve 2 Medium sorting problems
- [ ] Read Prefix Sums topic README
- [ ] Solve 2 Easy prefix sum problems
- [ ] Update progress tracker

---

## Motivation Tips

1. **Track your progress** - Update `progress.md` daily
2. **Celebrate small wins** - Each AC is an achievement!
3. **Don't compare** - Everyone learns at different speeds
4. **Stay consistent** - 1 hour daily beats 7 hours once a week
5. **Take breaks** - Rest is part of learning

---

**You've got this! Start with Topic 1 and build momentum. 🎯**
