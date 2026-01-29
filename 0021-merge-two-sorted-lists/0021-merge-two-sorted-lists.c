/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 != NULL || list2 != NULL){
        struct ListNode *new = malloc(sizeof(struct ListNode));
        if (list1 == NULL || (list2 != NULL && list2->val <= list1->val)) {
            new->val = list2->val;
            new->next = list1 == NULL ? mergeTwoLists(NULL, list2->next) : mergeTwoLists(list1, list2->next);
        } else if (list2 == NULL || list1->val < list2->val) {
            new->val = list1->val;
            new->next = list2 == NULL ? mergeTwoLists(list1->next, NULL) : mergeTwoLists(list1->next, list2);
        }
        return new;
    } else {
        return NULL;
    }
}
