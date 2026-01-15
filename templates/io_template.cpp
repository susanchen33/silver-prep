/*
 * USACO Silver - File I/O Template
 * Use this template for official USACO problems
 * 
 * USACO problems require reading from "problemname.in"
 * and writing to "problemname.out"
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int INF = 1e9;
const ll LINF = 1e18;

void setIO(string name) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

int main() {
    // Change "problemname" to the actual problem name
    setIO("problemname");
    
    // Read input
    int n;
    cin >> n;
    
    // Your solution here
    
    // Output answer
    
    return 0;
}

/*
 * IMPORTANT REMINDERS:
 * 
 * 1. Always check the problem name for file I/O
 *    - Problem "Lifeguards" → setIO("lifeguards")
 *    - Problem "Cow Dance Show" → setIO("cowdance")
 * 
 * 2. Integer overflow:
 *    - Use 'long long' when numbers can exceed 2×10^9
 *    - Especially for products, sums of large numbers
 * 
 * 3. Array bounds:
 *    - USACO typically has N ≤ 10^5 or N ≤ 2×10^5
 *    - Declare arrays with extra space to be safe
 * 
 * 4. Edge cases:
 *    - N = 1 (single element)
 *    - All same values
 *    - Sorted/reverse sorted input
 *    - Maximum values
 * 
 * 5. Complexity targets for Silver:
 *    - O(N log N) or O(N) for N = 10^5
 *    - O(N²) is usually too slow
 */
