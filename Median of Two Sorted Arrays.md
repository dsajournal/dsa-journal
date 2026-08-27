# Median of Two Sorted Arrays

## Problem

Given two sorted arrays `nums1` and `nums2`, return the median of the two sorted arrays.

**Required Time Complexity:** `O(log(min(m, n)))`

---

## Key Idea

The important observation is:

> We don't actually need to merge the two arrays.

We only need to find a **partition** such that:

```text
Left Half | Right Half
```

contains exactly half of the total elements, and every element on the left is smaller than or equal to every element on the right.

### Example

```text
nums1 = [1, 3]
nums2 = [2, 4, 5]

Combined:

[1, 2, 3] | [4, 5]
```

The partition is correct because:

```text
max(left) <= min(right)
```

---

## Why Binary Search?

We can choose how many elements to take from `nums1`.

Once we decide that, the number of elements we need from `nums2` is automatically determined.

```text
partition2 = half - partition1
```

So instead of searching through both arrays, we binary search only one array.

To make this easier, always binary search on the **smaller array**.

```cpp
if (nums1.size() > nums2.size())
    return findMedianSortedArrays(nums2, nums1);
```

---

## Partition Logic

Suppose:

```text
nums1 = [1, 3]
nums2 = [2, 4, 5]
```

Total elements:

```text
5
```

Left half should contain:

```text
(5 + 1) / 2 = 3
```

elements.

If we take `2` elements from `nums1`:

```text
nums1: [1, 3] | 
nums2: [2] | [4, 5]
```

So:

```text
partition1 = 2
partition2 = 1
```

Now define four values:

```text
left1  = nums1[partition1 - 1]
right1 = nums1[partition1]

left2  = nums2[partition2 - 1]
right2 = nums2[partition2]
```

For the partition to be valid:

```text
left1 <= right2
AND
left2 <= right1
```

---

## How to Move Binary Search

### Case 1: `left1 > right2`

We took too many elements from `nums1`.

So move left:

```text
high = partition1 - 1
```

### Case 2: `left2 > right1`

We took too few elements from `nums1`.

So move right:

```text
low = partition1 + 1
```

### Case 3: Correct Partition

```text
left1 <= right2
AND
left2 <= right1
```

Now we have found the median.

---

## Finding the Median

### Odd Number of Elements

The median is the largest element on the left:

```text
median = max(left1, left2)
```

### Even Number of Elements

The median is:

```text
(max(left1, left2) + min(right1, right2)) / 2
```

---

## Handling Boundary Cases

If the partition is at the beginning or end of an array, one side doesn't have an element.

Use:

```cpp
INT_MIN
```

for the missing left element.

Use:

```cpp
INT_MAX
```

for the missing right element.

This allows us to use the same partition logic without special cases.

---

## Code

```cpp
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    // Always perform binary search on the smaller array
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }

    int n1 = nums1.size();
    int n2 = nums2.size();

    // Total number of elements in the left half
    int half = (n1 + n2 + 1) / 2;

    int low = 0;
    int high = n1;

    while (low <= high) {

        // Partition nums1
        int partition1 = (low + high) / 2;

        // Remaining elements required from nums2
        int partition2 = half - partition1;

        // Elements just before and after the partition
        int left1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        int right1 = (partition1 == n1) ? INT_MAX : nums1[partition1];

        int left2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        int right2 = (partition2 == n2) ? INT_MAX : nums2[partition2];

        // Correct partition found
        if (left1 <= right2 && left2 <= right1) {

            // Odd total length
            if ((n1 + n2) % 2 == 1) {
                return max(left1, left2);
            }

            // Even total length
            return (max(left1, left2) + min(right1, right2)) / 2.0;
        }

        // Too many elements taken from nums1
        if (left1 > right2) {
            high = partition1 - 1;
        }

        // Too few elements taken from nums1
        else {
            low = partition1 + 1;
        }
    }

    return 0.0;
}
```

---

## Complexity

```text
Time:  O(log(min(m, n)))
Space: O(1)
```

---

## Pattern to Remember

This problem is essentially:

```text
Binary Search on Partition
```

The most important thing to remember is:

```text
left1 <= right2
AND
left2 <= right1
```

Once this condition is true, the partition is correct and the median can be calculated from the four boundary values.

---

## Interview Thought Process

When you see:

```text
Two sorted arrays
+
Need median
+
O(log(m + n))
```

Think:

```text
Don't merge.

Find a partition.

Binary search the smaller array.

Make sure:

max(left) <= min(right)
```

That is the core idea behind the entire solution.
