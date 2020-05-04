


#include "packer.h"


void    front_back_split(t_format *source, t_format **front_ref,
        t_format **back_ref)
{
    t_format *fast;
    t_format  *slow;

    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL;
}

t_format    *sorted_merge(t_format *a, t_format *b)
{
    t_format *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->start_index <= b->start_index)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return (result);
}

void    merge_sort(t_format **segment)
{
    t_format *head = *segment;
    t_format *a;
    t_format *b;

    if (head == NULL || head->next == NULL)
        return ;
    front_back_split(head, &a, &b);
    merge_sort(&a);
    merge_sort(&b);

    *segment = sorted_merge(a, b);
}
