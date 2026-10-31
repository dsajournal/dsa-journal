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
4. Disconnect the group by setting `kThNode->next = NULL`.
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

- `temp`: first node of the current group. After reversal, it becomes the last node of that group.
- `prevLast`: last node of the previously reversed group. It connects to the new head of the current group.

The Kth node becomes the new head of the reversed group.

## Algorithm

### 1. Find the Kth node

The helper function `getKthNode(temp, k)` starts at the first node of the group.

Since the current node is already the first node, decrement `k` once. Move forward until either:

- `k` reaches zero, so we found the Kth node.
- `temp` becomes `NULL`, so a complete group does not exist.

### 2. Save the next group's starting node

Before reversing, save:

```cpp
Node* nextNode = kThNode->next;
```

This is important because reversing the current group changes its links. Saving this pointer ensures we do not lose access to the remaining list.

### 3. Disconnect and reverse the group

```cpp
kThNode->next = NULL;
reverseLinkedList(temp);
```

Disconnecting the group makes the normal linked list reversal function operate only on these `k` nodes.

After reversal, `kThNode` is the new head of this group, while `temp` is its tail.

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
prevLast = temp;
```

### 5. Move to the next group

Continue from the node saved earlier:

```cpp
temp = nextNode;
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

The following is the complete implementation using the `Node` structure and the `kReverse` function. All explanatory comments are retained.

```cpp
Node* reverseLinkedList(Node *head)
{
    // Initialize 'temp' at
    // head of linked list
    Node* temp = head;

    // Initialize pointer 'prev' to NULL,
    // representing the previous node
    Node* prev = NULL;

    // Traverse the list, continue till
    // 'temp' reaches the end (NULL)
    while(temp != NULL){

        // Store the next node in
        // 'front' to preserve the reference
        Node* front = temp->next;

        // Reverse the direction of the
        // current node's 'next' pointer
        // to point to 'prev'
        temp->next = prev;

        // Move 'prev' to the current
        // node for the next iteration
        prev = temp;

        // Move 'temp' to the 'front' node
        // advancing the traversal
        temp = front;
    }

    // Return the new head of
    // the reversed linked list
    return prev;
}


// Function to get the Kth node from
// a given position in the linked list
Node* getKthNode(Node* temp, int k){

    // Decrement K as we already
    // start from the 1st node
    k -= 1;

    // Decrement K until it reaches
    // the desired position
    while(temp != NULL && k > 0){

        // Decrement k as temp progresses
        k--;

        // Move to the next node
        temp = temp -> next;
    }

    // Return the Kth node
    return temp;
}


// Function to reverse nodes in groups of K
Node* kReverse(Node* head, int k){

    // Initialize a temporary
    // node to traverse the list
    Node* temp = head;

    // Initialize a pointer to track the
    // last node of the previous group
    Node* prevLast = NULL;

    // Traverse through the linked list
    while(temp != NULL){

        // Get the Kth node of the current group
        Node* kThNode = getKthNode(temp, k);

        // If the Kth node is NULL
        // (not a complete group)
        if(kThNode == NULL){

            // If there was a previous group,
            // link the last node to the current node
            if(prevLast){
                prevLast -> next = temp;
            }

            // Exit the loop
            break;
        }

        // Store the next node
        // after the Kth node
        Node* nextNode = kThNode -> next;

        // Disconnect the Kth node
        // to prepare for reversal
        kThNode -> next = NULL;

        // Reverse the nodes from
        // temp to the Kth node
        reverseLinkedList(temp);

        // Adjust the head if the reversal
        // starts from the head
        if(temp == head){
            head = kThNode;
        }else{
            // Link the last node of the previous
            // group to the reversed group
            prevLast -> next = kThNode;
        }

        // Update the pointer to the
        // last node of the previous group
        prevLast = temp;

        // Move to the next group
        temp = nextNode;
    }

    // Return the head of the
    // modified linked list
    return head;
}
```

## Tricky Parts

**1. Why save `nextNode` before reversing?**

Reversing changes the links inside the current group. We must preserve the pointer to the first node of the next group before changing those links.

**2. Why disconnect the Kth node?**

Setting `kThNode->next = NULL` isolates exactly `k` nodes. Otherwise, the reversal function would reverse the rest of the list too.

**3. Why does `temp` become `prevLast`?**

After reversing a group, its original first node moves to the end. So `temp` is now the tail that will connect to the next reversed group.

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
