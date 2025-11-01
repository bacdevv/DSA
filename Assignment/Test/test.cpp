#include <iostream>
#include <cstdlib> // For malloc

// --- Structure Definitions ---
struct Node
{
    int data;       
    Node* pNext;    
};

struct List    
{
    Node* pHead;
    Node* pTail;    
};

// --- Helper Function ---

/**
 * @brief Creates a new Node with the given data.
 * @param x The integer data for the new node.
 * @return A pointer to the newly created Node.
 */
Node *makeNode(int x) {
    // In C++, it's generally better to use 'new' instead of 'malloc' for 
    // type safety and constructor calls, but since you used malloc, I'll stick 
    // to it for consistency.
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Handle memory allocation failure
        std::cerr << "Memory allocation failed!" << std::endl;
        exit(1); 
    }
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}

// ----------------------------------------------------------------------

// 1. Init function to initialize an empty list
/**
 * @brief Initializes the linked list to an empty state.
 * @param list A reference to the List structure.
 */
void Init(List &list) {
    list.pHead = list.pTail = NULL;
}

// ----------------------------------------------------------------------

// 2. InsertFirst function to insert an element x at the beginning of a linked list
/**
 * @brief Inserts a new element at the beginning (head) of the list.
 * @param list A reference to the List structure.
 * @param x The integer data to insert.
 */
void InsertFirst(List &list, int x) {
    Node *newNode = makeNode(x);
    
    if (list.pHead == NULL) {
        // Case 1: The list is currently empty.
        list.pHead = newNode;
        list.pTail = newNode; // The new node is both the head and the tail.
    } else {
        // Case 2: The list is not empty.
        newNode->pNext = list.pHead; // Link the new node to the current head.
        list.pHead = newNode;         // Update the head pointer.
        // pTail remains unchanged.
    }
}

// *Correction Note for your original implementation:*
// Your original implementation for InsertFirst:
// if (list.pHead == NULL) { list.pHead = newNode; } // Only updates pHead.
// newNode->pNext = list.pHead; // This links newNode to ITSELF if list was empty!
// list.pHead = newNode; // The list is now: Head -> ... -> Head (circular if empty).
// The correction above properly handles the pTail update for an empty list and 
// correctly links the new node *before* the existing head.

// ----------------------------------------------------------------------

// 3. SearchKey function to find a value x in a linked list. 
/**
 * @brief Searches for a specific value in the list.
 * @param list A reference to the List structure.
 * @param x The integer value to search for.
 * @return 1 if the value is found, otherwise -1.
 */
int SearchKey(List &list, int x) {
    // Start traversal from the head of the list.
    Node *current = list.pHead; 
    
    // Loop until the current pointer is NULL (end of the list).
    while (current != NULL) {
        if (current->data == x) {
            // Found the key!
            return 1;
        }
        // Move to the next node in the list.
        current = current->pNext;
    }
    
    // Traversed the entire list and didn't find the key.
    return -1;
}

// ----------------------------------------------------------------------

int main() {
    List myList;
    Init(myList);

    std::cout << "List initialized. Is 10 present? " 
              << SearchKey(myList, 10) << " (-1 expected)\n"; // Output: -1

    InsertFirst(myList, 10); // List: 10
    InsertFirst(myList, 20); // List: 20 -> 10
    InsertFirst(myList, 30); // List: 30 -> 20 -> 10

    std::cout << "After inserts, is 20 present? " 
              << SearchKey(myList, 20) << " (1 expected)\n"; // Output: 1
              
    std::cout << "After inserts, is 5 present? " 
              << SearchKey(myList, 5) << " (-1 expected)\n"; // Output: -1

    // For educational purposes, checking pTail after insertions:
    if (myList.pTail != NULL) {
        std::cout << "Tail data: " << myList.pTail->data << " (10 expected)\n";
    }

    // You would need a proper Deallocate function here to free memory.
    
    return 0;
}