#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 

struct _listNode {
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode* head);
void deleteList(ListNode** ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode* head = NULL, * temp =NULL;
    int i = 0;
    int K = 0;

    scanf("%d", &K);

    while (scanf("%d", &i)) {
        if (head == NULL) {
            head = (ListNode*)malloc(sizeof(ListNode));
            temp = head;
        }
        else {
            temp->next = (ListNode*)malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
    }
    temp->next = NULL;


    reverseKNodes(&head, K);
    printList(head);
    deleteList(&head);
    return 0;
}

void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}
void deleteList(ListNode** ptrHead) {
    ListNode* cur = *ptrHead;
    ListNode* temp;
    while (cur != NULL) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    *ptrHead = NULL;
}
void reverseKNodes(ListNode** head, int K) {
    ListNode* currTrav = *head;
    ListNode* cur = *head;
    ListNode* prev = NULL;
    ListNode* temp = NULL;
    ListNode* segTail =NULL;
    int segCount = 0;
    int segFirst = 0;

    while (currTrav != NULL) {

        //first segment traverse 
        if (segFirst == 0) {
            for (int i = 1; i < (K * 2); i++) {
                if (currTrav != NULL) {
                    currTrav = currTrav->next;
                }
                else {
                    break;
                }
                if (i == K) {
                    segCount = segCount + 1;
                }
            }
            if (currTrav != NULL) {
                segCount = segCount + 1;
            }
        }
        //rest of the segments traverse 
        else {
            for (int i = 0; i < K; i++) {
                if (currTrav != NULL) {
                    currTrav = currTrav->next;
                }
                else {
                    break;
                }
                if (i == K) {
                    segCount = segCount + 1;
                }
            }
        }

        //reverse segment if trav pointer not null 
        if (segCount > 1 && segFirst == 0) {
            segTail = cur;
            for (int i = 0; i < K; i++) {
                temp = cur->next;
                cur->next = prev;
                prev = cur;
                *head = cur;
                cur = temp;
            }
            segTail->next = currTrav;
            segFirst = 1;
            segCount = segCount - 1;

        }
        else if (segCount == 1 && currTrav == NULL) {
            segTail = cur;
            for (int i = 0; i < K; i++) {
                temp = cur->next;
                cur->next = prev;
                prev = cur;
                if (segFirst == 0 && i == K - 1) {
                    *head = cur;
                    segFirst = 1;
                }
                cur = temp;
            }
            segTail->next = cur;
            segCount = segCount - 1;
        }
        else  {
            segTail = cur;
            for (int i = 0; i < K; i++) {
                temp = cur->next;
                cur->next = prev;
                prev = cur;
                cur = temp;
            }
            if (currTrav != NULL) {
                segTail->next = currTrav;
            }
            else {
                segTail->next = cur;
            }
            segCount = segCount - 1;
        }

    }
}
