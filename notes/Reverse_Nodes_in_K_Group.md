# Reverse Nodes in K Group

## Problem

Given the head of a singly linked list and an integer `k`, reverse the nodes in groups of `k`.

Only complete groups should be reversed. If fewer than `k` nodes remain, leave those nodes unchanged.

```text
Input:  1 → 2 → 3 → 4 → 5, k = 2
Output: 2 → 1 → 4 → 3 → 5
```

For `k = 3`:

```text
Input:  1 → 2 → 3 → 4 → 5, k = 3
Output: 3 → 2 → 1 → 4 → 5
```

## Core Idea

Process the list one group at a time.

For each group:

1. Find the Kth node from the current group start.
2. If it does not exist, fewer than `k` nodes remain. Leave them unchanged and stop.
3. Save the node immediately after the group.
4. Disconnect the group by setting `kthNode->next = NULL`.
5. Reverse the isolated group using the standard iterative linked list reversal.
6. Connect the reversed group to the previous group.
7. Move to the next group.

The important part is to separate finding, reversing, and reconnecting each group.

## Mental Model

Think of the linked list as three sections:

```text
[ Reversed groups ] → [ Current group ] → [ Remaining nodes ]
```

We use two pointers to connect groups:

- `groupStart`: first node of the current group. After reversal, it becomes the last node of that group.
- `prevLast`: last node of the previously reversed group. It connects to the new head of the current group.

The Kth node becomes the new head of the reversed group.

## Algorithm

### 1. Find the Kth node

The helper function `getKthNode(curr, k)` starts at the first node of the group.

Since the current node is already the first node, decrement `k` once. Move forward until either:

- `k` reaches zero, so we found the Kth node.
- `curr` becomes `NULL`, so a complete group does not exist.

### 2. Save the next group's starting node

Before reversing, save:

```cpp
ListNode* nextNode = kThNode->next;
```

This is important because reversing the current group changes its links. Saving this pointer ensures we do not lose access to the remaining list.

### 3. Disconnect and reverse the group

```cpp
kThNode->next = NULL;
reverseLinkedList(groupStart);
```

Disconnecting the group makes the normal linked list reversal function operate only on these `k` nodes.

After reversal, `kThNode` is the new head of this group, while `groupStart` is its tail.

### 4. Connect the reversed group

For the first group, update the list head:

```cpp
head = kThNode;
```

For every later group, connect the previous group's tail to the current group's new head:

```cpp
prevLast->next = kThNode;
```

Then update the tail pointer:

```cpp
prevLast = groupStart;
```

### 5. Move to the next group

Continue from the node saved earlier:

```cpp
groupStart = nextNode;
```

If the remaining nodes are fewer than `k`, connect them to `prevLast` without reversing them.

## Dry Run

For `1 → 2 → 3 → 4 → 5`, with `k = 2`:

**First group:**

```text
Current group: 1 → 2
Next group:    3 → 4 → 5

Reverse:
2 → 1

Head becomes 2.
prevLast becomes 1.
```

**Second group:**

```text
Current group: 3 → 4
Next group:    5

Reverse:
4 → 3

Connect previous tail:
2 → 1 → 4 → 3

prevLast becomes 3.
```

**Remaining nodes:**

Only node `5` remains, which is fewer than `k = 2`. Do not reverse it.

Final list:

```text
2 → 1 → 4 → 3 → 5 → NULL
```

## Code

```cpp
class Solution {
public:

    // Reverse a linked list and return its new head
    ListNode* reverseLinkedList(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = NULL;

        while (curr != NULL) {
            ListNode* front = curr->next;
            curr->next = prev;
            prev = curr;
            curr = front;
        }

        return prev;
    }

    // Return the Kth node starting from curr
    ListNode* getKthNode(ListNode* curr, int k) {
        k -= 1;

        while (curr != NULL && k > 0) {
            k--;
            curr = curr->next;
        }

        return curr;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* groupStart = head;
        ListNode* prevLast = NULL;

        while (groupStart != NULL) {
            ListNode* kThNode = getKthNode(groupStart, k);

            // Fewer than k nodes remain. Keep them unchanged.
            if (kThNode == NULL) {
                if (prevLast != NULL) {
                    prevLast->next = groupStart;
                }
                break;
            }

            // Save the start of the next group
            ListNode* nextNode = kThNode->next;

            // Isolate and reverse the current group
            kThNode->next = NULL;
            reverseLinkedList(groupStart);

            // Connect the reversed group
            if (groupStart == head) {
                head = kThNode;
            } else {
                prevLast->next = kThNode;
            }

            // groupStart is now the tail of the reversed group
            prevLast = groupStart;

            // Process the next group
            groupStart = nextNode;
        }

        return head;
    }
};
```

## Tricky Parts

**1. Why save `nextNode` before reversing?**

Reversing changes the links inside the current group. We must preserve the pointer to the first node of the next group before changing those links.

**2. Why disconnect the Kth node?**

Setting `kThNode->next = NULL` isolates exactly `k` nodes. Otherwise, the reversal function would reverse the rest of the list too.

**3. Why does `groupStart` become `prevLast`?**

After reversing a group, its original first node moves to the end. So `groupStart` is now the tail that will connect to the next reversed group.

**4. Why do we need to update the head only once?**

The first reversed group determines the new head of the entire linked list. Later groups are connected through `prevLast->next`.

**5. What happens to an incomplete group?**

If `getKthNode` returns `NULL`, the remaining nodes are fewer than `k`. They are left in their original order and attached to the previous group's tail.

## Complexity

Let `n` be the number of nodes.

- **Time: O(n)**. Each node is visited a constant number of times. Finding group boundaries and reversing all complete groups together take linear time.
- **Auxiliary space: O(1)**. The solution uses only a fixed number of pointers and reverses the list in place.

## Remember

The pattern for every group is:

```text
FIND KTH
   ↓
SAVE NEXT GROUP
   ↓
DISCONNECT CURRENT GROUP
   ↓
REVERSE
   ↓
CONNECT TO PREVIOUS GROUP
   ↓
MOVE TO NEXT GROUP
```

**Most important point:** save the next group's starting node before reversing. After reversal, the old group start becomes the group's tail, so use it as `prevLast` to connect the next group.

