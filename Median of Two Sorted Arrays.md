Sure. Here is the same note in clean `.md` format, keeping the explanation and structure intact:

````md
# Median of Two Sorted Arrays

We have two sorted arrays and need to find the median of the combined sorted array.

The brute force approach would be to merge both arrays and then find the median. This takes O(m + n) time.

However, the problem requires a solution in O(log(min(m, n))).

The key idea is to find a **partition** in both arrays such that all elements on the left side of the partition are smaller than or equal to all the elements on the right side.

---

## The Main Idea

Suppose we have:

```text
nums1 = [1, 3, 8]
nums2 = [2, 7, 10, 12]
````

We want to divide both arrays like this:

```text
nums1: [1, 3 | 8]
nums2: [2, 7 | 10, 12]
```

The left side contains half of all elements.

If this is the correct partition, then:

```text
largest element on left <= smallest element on right
```

So we need:

```text
left1 <= right2
left2 <= right1
```

Once this condition is satisfied, we have found the correct partition.

---

## Why Binary Search Works

We perform binary search on the **smaller array**.

Suppose we choose a partition `cut1` in `nums1`.

The partition in `nums2` is automatically determined because the left side must contain half of all elements.

```text
cut2 = (m + n + 1) / 2 - cut1
```

So every time we move `cut1`, `cut2` changes automatically.

Now we check whether the partition is correct.

### Case 1: Partition is correct

```text
left1 <= right2
left2 <= right1
```

We have found the correct partition.

### Case 2: Partition in nums1 is too far right

If:

```text
left1 > right2
```

then we have taken too many elements from `nums1` into the left half.

Therefore, move the partition left:

```text
high = cut1 - 1
```

### Case 3: Partition in nums1 is too far left

Otherwise:

```text
left2 > right1
```

This means we need to take more elements from `nums1` into the left half.

Therefore:

```text
low = cut1 + 1
```

---

## Handling Boundaries

Sometimes the partition is at the beginning or end of an array.

For example:

```text
nums1: [ | 1, 3, 8]
```

There is no element on the left.

So we treat the left value as:

```text
INT_MIN
```

Similarly:

```text
nums1: [1, 3, 8 | ]
```

There is no element on the right.

So we treat the right value as:

```text
INT_MAX
```

This allows us to use the same comparison logic for every partition.

---

## Finding the Median

Once we have the correct partition:

### Odd number of elements

The median is the largest element on the left:

```text
median = max(left1, left2)
```

### Even number of elements

The median is the average of:

```text
largest element on the left
smallest element on the right
```

Therefore:

```text
median = (max(left1, left2) + min(right1, right2)) / 2.0
```

---

## Why We Search the Smaller Array

We only need to binary search one array.

To minimize the number of iterations, we always search the smaller array.

Therefore:

```text
Time Complexity = O(log(min(m, n)))
Space Complexity = O(1)
```

---

## Leap of Faith

Binary search, like recursion, has a leap of faith.

The leap of faith is:

If I correctly determine whether the partition in `nums1` is too far left or too far right, I can trust binary search to find the correct partition in the remaining half.

I don't need to worry about what happens inside that half.

The next iteration applies exactly the same logic again.

---

## Code

```cpp
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    // Always perform binary search on the smaller array
    if (nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);

    int m = nums1.size();
    int n = nums2.size();

    // Binary search range for nums1
    int low = 0;
    int high = m;

    while (low <= high) {

        // Partition index for nums1
        int cut1 = low + (high - low) / 2;

        // Partition index for nums2
        // So that the left side contains half of all elements
        int cut2 = (m + n + 1) / 2 - cut1;

        // Elements around the partition in nums1
        int left1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        int right1 = (cut1 == m) ? INT_MAX : nums1[cut1];

        // Elements around the partition in nums2
        int left2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        int right2 = (cut2 == n) ? INT_MAX : nums2[cut2];

        // Check if we found the correct partition
        if (left1 <= right2 && left2 <= right1) {

            // Odd total number of elements
            // Median is the largest element on the left
            if ((m + n) % 2 == 1)
                return max(left1, left2);

            // Even total number of elements
            // Median is the average of the middle two elements
            return (max(left1, left2) + min(right1, right2)) / 2.0;
        }

        // Partition in nums1 is too far to the right
        if (left1 > right2)
            high = cut1 - 1;

        // Partition in nums1 is too far to the left
        else
            low = cut1 + 1;
    }

    // This line should never be reached for valid input
    return 0.0;
}
```

```
```
