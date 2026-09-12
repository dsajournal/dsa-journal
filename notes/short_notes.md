## Linked Lists

### Copy List with Random Pointer

**Example:** `1 -> 2`, with `1.random -> 2`; copy the list with new nodes and the same links.
Create a copy of every node and store an **`original node -> copied node`** mapping in a Hash Map. Traverse again to connect `next` and `random`; map node addresses, not values.
**Time: O(n), Space: O(n).**

### Add Two Numbers

**Example:** `2 -> 4 -> 3` + `5 -> 6 -> 4` = `7 -> 0 -> 8` (342 + 465 = 807).
Traverse both linked lists together, adding corresponding digits plus a **carry**.
Treat missing nodes as `0`, create a new node with `sum % 10`, and update carry using `sum / 10`.
Continue while either list has nodes **or carry is not 0**, using a dummy node to build the result.
**Time: O(max(n,m)), Space: O(max(n,m))** for the output list.

### Linked List Cycle

**Example:** `1 -> 2 -> 3 -> 2` contains a cycle; `1 -> 2 -> 3 -> null` does not.
Use Floyd's algorithm: move `slow` one step and `fast` two steps. If they meet, a cycle exists; if `fast` or `fast->next` is null, it does not.
**Time: O(n), Space: O(1).**

### Merge Two Sorted Lists

**Example:** `1 -> 2 -> 4` and `1 -> 3 -> 4` become `1 -> 1 -> 2 -> 3 -> 4 -> 4`.
Use a dummy node and `tail`. Compare the current nodes, attach the smaller one, advance that list and `tail`, then attach the remaining list.
**Time: O(m + n), Space: O(1).**

### Remove Nth Node From End

**Example:** `1 -> 2 -> 3 -> 4 -> 5`, `n = 2` becomes `1 -> 2 -> 3 -> 5`.
Put `left` and `right` at a dummy node, move `right` `n` steps ahead, then move both until `right->next` is null. Remove `left->next`; the dummy handles removing the head.
**Time: O(n), Space: O(1).**

### Reorder List

**Example:** `1 -> 2 -> 3 -> 4 -> 5` becomes `1 -> 5 -> 2 -> 4 -> 3`.
Split at the middle, reverse the second half, then merge the two halves alternately.
**Remember: middle -> reverse -> merge. Time: O(n), Space: O(1).**

### Reverse Linked List

**Example:** `1 -> 2 -> 3 -> null` becomes `3 -> 2 -> 1 -> null`.
Iteratively save `current->next`, reverse the link to `previous`, then advance both pointers. Return `previous` as the new head.
**Time: O(n), Space: O(1).**

## Arrays and Binary Search

### Best Time to Buy and Sell Stock

**Example:** prices `[7, 1, 5, 3, 6, 4]` produce maximum profit `5` by buying at `1` and selling at `6`.
Track the smallest price seen so far and the best profit from selling today: `profit = price - minimumPrice`.
**Time: O(n), Space: O(1).**

### Binary Search Possibilities

**Example:** Search for `7` in `[1, 3, 5, 7, 9]`; binary search returns index `3`.
Keep inclusive `left`, `mid`, and `right` bounds with `left <= mid <= right`. With `mid = left + (right - left) / 2`, `mid` is left-biased: `left = mid < right`, `left < mid = right` is impossible, and all three can be equal when one element remains. Discard the half that cannot contain the answer.
**Time: O(log n), Space: O(1).**

### Find Minimum in Rotated Sorted Array

**Example:** `[4, 5, 6, 7, 0, 1, 2]` has minimum value `0`.
Compare `nums[mid]` with `nums[left]` to identify the sorted region. If `nums[mid] >= nums[left]`, the minimum must be to the right of `mid`; otherwise it is `mid` or to its left. If the remaining range is already sorted, its leftmost value is the minimum.
**Time: O(log n), Space: O(1).**

### Koko Eating Bananas

**Example:** piles `[3, 6, 7, 11]`, `h = 8` gives minimum speed `4` bananas per hour.
Binary-search the eating speed from `1` to the largest pile. For a candidate speed `k`, calculate hours with `ceil(pile / k)`; if the total fits within `h`, search lower speeds, otherwise search higher speeds.
**Time: O(n log m), Space: O(1)**, where `m` is the largest pile.

### Median of Two Sorted Arrays

**Example:** `[1, 3]` and `[2]` combine to `[1, 2, 3]`, so the median is `2`.
Binary-search the smaller array for a partition where `left1 <= right2` and `left2 <= right1`. The left side contains half the elements; calculate the median from the boundary values.
**Time: O(log(min(m, n))), Space: O(1).**

### Sliding Window Maximum

**Example:** `[1, 3, -1, -3, 5, 3, 6, 7]`, `k = 3` gives `[3, 3, 5, 5, 6, 7]`.
Store indices in a deque whose values decrease from front to back. Remove smaller values from the back, expired indices from the front, and read the front as the window maximum.
**Time: O(n), Space: O(k).**

### Longest Substring Without Repeating Characters

**Example:** `s = "abcabcbb"` has longest non-repeating substring `"abc"`, with length `3`.
Use a sliding window and a map of each character's latest index. When a duplicate appears inside the window, move `left` past its previous index.
**Time: O(n), Space: O(min(n, alphabet)).**

### Longest Repeating Character Replacement

**Example:** `s = "AABABBA"`, `k = 1` gives longest length `4` (`"AABA"` or `"ABBA"`).
Maintain character counts, the window's most frequent character, and `windowLength - maxFrequency`. Shrink while that replacement cost exceeds `k`.
**Time: O(n), Space: O(alphabet).**

### Minimum Window Substring

**Example:** `s = "ADOBECODEBANC"`, `t = "ABC"` gives minimum window `"BANC"`.
Count required characters, expand `right` until all requirements are met, then shrink `left` while valid. Keep the shortest valid window.
**Time: O(m + n), Space: O(alphabet).**

### Permutation in String / Check Inclusion

**Example:** `s1 = "ab"`, `s2 = "eidbaooo"` returns `true` because `"ba"` is a permutation of `"ab"`.
Compare fixed-size sliding-window frequency counts for the pattern and text. A matching count means the current window is a permutation.
**Time: O(m + n), Space: O(alphabet).**

### Search in Rotated Sorted Array

**Example:** `[4, 5, 6, 7, 0, 1, 2]`, target `0` returns index `4`.
At least one half is sorted. Check whether the target lies within that half's value range; search it if so, otherwise discard it and search the other half.
**Time: O(log n), Space: O(1).**

## Recursion and Backtracking

### Permutations Without Repetition

**Example:** `[1, 2, 3]` produces `[1,2,3]`, `[1,3,2]`, `[2,1,3]`, `[2,3,1]`, `[3,1,2]`, `[3,2,1]`.
Build a path recursively, choose each unused value, recurse, then remove it from the path to backtrack. Each complete path is one permutation.
**Time: O(n · n!), Space: O(n) excluding output.**

### Print All Possible Strings of Length `k`

**Example:** characters `{a, b}`, `k = 2` produce `aa`, `ab`, `ba`, and `bb`.
At each recursion level, choose one character from the set, append it, recurse until the path length is `k`, then backtrack.
**Time: O(n^k · k), Space: O(k) excluding output.**

### Print All Substrings Starting From Each Index

**Example:** `abc` has substrings `a`, `ab`, `abc`, `b`, `bc`, and `c`.
Fix a starting index and extend the ending index one position at a time, emitting each current range. Repeat for every start index.
**Time: O(n^2) generated substrings, or O(n^3) if copying each substring.**

## Design

### Time-Based Key-Value Store

**Example:** set `foo = bar` at time `1`, set `foo = bar2` at time `4`; `get(foo, 3)` returns `bar`.
Store each key's `(timestamp, value)` pairs in timestamp order. For `get(key, timestamp)`, binary-search the rightmost timestamp less than or equal to the requested time.
**Set: O(1), Get: O(log n), Space: O(n).**
