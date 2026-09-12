## Linked Lists

### Copy List with Random Pointer

Create a copy of every node and store an **`original node -> copied node`** mapping in a Hash Map. Traverse again to connect `next` and `random`; map node addresses, not values.
**Time: O(n), Space: O(n).**

### Add Two Numbers

Traverse both linked lists together, adding corresponding digits plus a **carry**.
Treat missing nodes as `0`, create a new node with `sum % 10`, and update carry using `sum / 10`.
Continue while either list has nodes **or carry is not 0**, using a dummy node to build the result.
**Time: O(max(n,m)), Space: O(max(n,m))** for the output list.

### Linked List Cycle

Use Floyd's algorithm: move `slow` one step and `fast` two steps. If they meet, a cycle exists; if `fast` or `fast->next` is null, it does not.
**Time: O(n), Space: O(1).**

### Merge Two Sorted Lists

Use a dummy node and `tail`. Compare the current nodes, attach the smaller one, advance that list and `tail`, then attach the remaining list.
**Time: O(m + n), Space: O(1).**

### Remove Nth Node From End

Put `left` and `right` at a dummy node, move `right` `n` steps ahead, then move both until `right->next` is null. Remove `left->next`; the dummy handles removing the head.
**Time: O(n), Space: O(1).**

### Reorder List

Split at the middle, reverse the second half, then merge the two halves alternately.
**Remember: middle -> reverse -> merge. Time: O(n), Space: O(1).**

### Reverse Linked List

Iteratively save `current->next`, reverse the link to `previous`, then advance both pointers. Return `previous` as the new head.
**Time: O(n), Space: O(1).**

## Arrays and Binary Search

### Best Time to Buy and Sell Stock

Track the smallest price seen so far and the best profit from selling today: `profit = price - minimumPrice`.
**Time: O(n), Space: O(1).**

### Binary Search Possibilities

Keep inclusive `left`, `mid`, and `right` bounds with `left <= mid <= right`. With `mid = left + (right - left) / 2`, `mid` is left-biased: `left = mid < right`, `left < mid = right` is impossible, and all three can be equal when one element remains. Discard the half that cannot contain the answer.
**Time: O(log n), Space: O(1).**

### Find Minimum in Rotated Sorted Array

Compare `nums[mid]` with `nums[left]` to identify the sorted region. If `nums[mid] >= nums[left]`, the minimum must be to the right of `mid`; otherwise it is `mid` or to its left. If the remaining range is already sorted, its leftmost value is the minimum.
**Time: O(log n), Space: O(1).**

### Koko Eating Bananas

Binary-search the eating speed from `1` to the largest pile. For a candidate speed `k`, calculate hours with `ceil(pile / k)`; if the total fits within `h`, search lower speeds, otherwise search higher speeds.
**Time: O(n log m), Space: O(1)**, where `m` is the largest pile.

### Median of Two Sorted Arrays

Binary-search the smaller array for a partition where `left1 <= right2` and `left2 <= right1`. The left side contains half the elements; calculate the median from the boundary values.
**Time: O(log(min(m, n))), Space: O(1).**

### Sliding Window Maximum

Store indices in a deque whose values decrease from front to back. Remove smaller values from the back, expired indices from the front, and read the front as the window maximum.
**Time: O(n), Space: O(k).**

### Longest Substring Without Repeating Characters

Use a sliding window and a map of each character's latest index. When a duplicate appears inside the window, move `left` past its previous index.
**Time: O(n), Space: O(min(n, alphabet)).**

### Longest Repeating Character Replacement

Maintain character counts, the window's most frequent character, and `windowLength - maxFrequency`. Shrink while that replacement cost exceeds `k`.
**Time: O(n), Space: O(alphabet).**

### Minimum Window Substring

Count required characters, expand `right` until all requirements are met, then shrink `left` while valid. Keep the shortest valid window.
**Time: O(m + n), Space: O(alphabet).**

### Permutation in String / Check Inclusion

Compare fixed-size sliding-window frequency counts for the pattern and text. A matching count means the current window is a permutation.
**Time: O(m + n), Space: O(alphabet).**

### Search in Rotated Sorted Array

At least one half is sorted. Check whether the target lies within that half's value range; search it if so, otherwise discard it and search the other half.
**Time: O(log n), Space: O(1).**

## Recursion and Backtracking

### Permutations Without Repetition

Build a path recursively, choose each unused value, recurse, then remove it from the path to backtrack. Each complete path is one permutation.
**Time: O(n · n!), Space: O(n) excluding output.**

### Print All Possible Strings of Length `k`

At each recursion level, choose one character from the set, append it, recurse until the path length is `k`, then backtrack.
**Time: O(n^k · k), Space: O(k) excluding output.**

### Print All Substrings Starting From Each Index

Fix a starting index and extend the ending index one position at a time, emitting each current range. Repeat for every start index.
**Time: O(n^2) generated substrings, or O(n^3) if copying each substring.**

## Design

### Time-Based Key-Value Store

Store each key's `(timestamp, value)` pairs in timestamp order. For `get(key, timestamp)`, binary-search the rightmost timestamp less than or equal to the requested time.
**Set: O(1), Get: O(log n), Space: O(n).**
>>>>>>> 1e7d948 (Update solved question short notes)
