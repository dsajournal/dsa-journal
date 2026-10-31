/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:

    // Function to reverse the linked list
    ListNode* reverseLinkedList(ListNode* head)
    {
        // Initialize 'currentNode' at
        // head of linked list
        ListNode* currentNode = head;

        // Initialize pointer 'previousNode' to NULL,
        // representing the previous node
        ListNode* previousNode = NULL;

        // Traverse the list, continue till
        // 'currentNode' reaches the end (NULL)
        while(currentNode != NULL){

            // Store the next node in
            // 'nextNode' to preserve the reference
            ListNode* nextNode = currentNode->next;

            // Reverse the direction of the
            // current node's 'next' pointer
            // to point to 'previousNode'
            currentNode->next = previousNode;

            // Move 'previousNode' to the current
            // node for the next iteration
            previousNode = currentNode;

            // Move 'currentNode' to the 'nextNode'
            // advancing the traversal
            currentNode = nextNode;
        }

        // Return the new head of
        // the reversed linked list
        return previousNode;
    }


    // Function to get the Kth node from
    // a given position in the linked list
    ListNode* getKthNode(ListNode* currentGroupStart, int k){

        // Decrement K as we already
        // start from the 1st node
        k -= 1;

        // Decrement K until it reaches
        // the desired position
        while(currentGroupStart != NULL && k > 0){

            // Decrement k as currentGroupStart progresses
            k--;

            // Move to the next node
            currentGroupStart = currentGroupStart->next;
        }

        // Return the Kth node
        return currentGroupStart;
    }


    // Function to reverse nodes in groups of K
    ListNode* reverseKGroup(ListNode* head, int k){

        // Initialize a pointer to traverse
        // from the beginning of the current group
        ListNode* currentGroupStart = head;

        // Initialize a pointer to track the
        // last node of the previous group
        ListNode* previousGroupLast = NULL;

        // Traverse through the linked list
        while(currentGroupStart != NULL){

            // Get the Kth node of the current group
            ListNode* kthNode = getKthNode(currentGroupStart, k);

            // If the Kth node is NULL
            // (not a complete group)
            if(kthNode == NULL){

                // If there was a previous group,
                // link the last node to the current node
                if(previousGroupLast){
                    previousGroupLast->next = currentGroupStart;
                }

                // Exit the loop
                break;
            }

            // Store the next node
            // after the Kth node
            ListNode* nextGroupStart = kthNode->next;

            // Disconnect the Kth node
            // to prepare for reversal
            kthNode->next = NULL;

            // Reverse the nodes from
            // currentGroupStart to the Kth node
            reverseLinkedList(currentGroupStart);

            // Adjust the head if the reversal
            // starts from the head
            if(currentGroupStart == head){
                head = kthNode;
            }
            else{
                // Link the last node of the previous
                // group to the reversed group
                previousGroupLast->next = kthNode;
            }

            // Update the pointer to the
            // last node of the previous group
            previousGroupLast = currentGroupStart;

            // Move to the next group
            currentGroupStart = nextGroupStart;
        }

        // Return the head of the
        // modified linked list
        return head;
    }
};