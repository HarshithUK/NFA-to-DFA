#include<stdlib.h>
typedef struct lnode
{
    int data;
    struct lnode* next;
}LNode;
typedef struct set
{
    LNode* head;
}Set;
void add(Set* s, int d)
{
    LNode* curr = s->head;
    LNode* prev = NULL;
    LNode* temp = (LNode*)malloc(sizeof(LNode));
    temp->data = d;
    temp->next = NULL;
    while(curr!=NULL && curr->data<d)
    {
        prev = curr;
        curr = curr->next;
    }
    if(curr==NULL)
    {
        if(prev==NULL)
        {
            s->head = temp;
        }
        else
        {
            prev->next = temp;
        }
    }
    else if(curr->data>d)
    {
        if(prev==NULL)
        {
            s->head = temp;
        }
        else
        {
            prev->next = temp;
        }
         temp->next = curr;
    }
}
Set* sunion(Set* s1, Set* s2)
{
    Set* s = (Set*)malloc(sizeof(Set));
    s->head = NULL;
    LNode* curr1 = s1->head;
    LNode* curr2 = s2->head;
    while(curr1!=NULL)
    {
        add(s,curr1->data);
        curr1 = curr1->next;
    }
    while(curr2!=NULL)
    {
        add(s,curr2->data);
        curr2 = curr2->next;
    }
    return s;
}
int is_equal(Set* s1, Set* s2)
{
    LNode* curr1 = s1->head;
    LNode* curr2 = s2->head;
    while(curr1!=NULL && curr2!=NULL)
    {
        if(curr1->data==curr2->data)
        {
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        else
        {
            return 0;
        }
    }
    if(curr1==NULL && curr2==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
