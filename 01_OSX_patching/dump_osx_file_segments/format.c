

#include "packer.h"

t_format    *new_segment(size_t start_index, size_t end_index,
    unsigned char *content, char *area_name)
{
    t_format    *segment;

    segment = (t_format *)malloc(sizeof(t_format));
    segment->start_index = start_index;
    segment->end_index = end_index;
    segment->section_contents = (unsigned char *)malloc(
        sizeof(unsigned char) * end_index - start_index + 1);
    memcpy(segment->section_contents, &content[start_index],
        end_index - start_index);
    segment->area_name = strdup(area_name);
    segment->next = NULL;
    return (segment);
}

t_format    *add_segment(t_format *segment_head, size_t start_index, size_t end_index, unsigned char *content, char *area_name)
 {
     t_format   *last_seg;

     last_seg = segment_head;
     while (last_seg->next)
         last_seg = last_seg->next;
     last_seg->next = (t_format *)malloc(sizeof(t_format));
     last_seg->next->start_index = start_index;
     last_seg->next->end_index = end_index;
     last_seg->next->area_name = strdup(area_name);
     last_seg->next->section_contents = (unsigned char *)
         malloc(sizeof(unsigned char) * end_index - start_index + 1);
     memcpy(last_seg->next->section_contents, &content[start_index],
        end_index - start_index);

     last_seg->next->next = NULL;
     return (last_seg);
 }

t_format  *push_segment(t_format *segment_head, size_t start_index, size_t end_index, unsigned char *content, char *area_name)
{
    t_format    *segment;

    segment = segment_head;
    if (segment == NULL)
    {
        segment = new_segment(start_index, end_index,
            content, area_name);
        segment_head =  segment;;
    }
    else
    {
        segment = add_segment(segment, start_index, end_index,
            content,  area_name);
        segment = segment_head;
    }
    return segment;
}


int     seg_length(t_format *list)
{
    t_format *trav;
    int counter;

    counter = 0;
    trav = list;
    while (trav)
    {
        printf("segmgent name is %s\n", trav->area_name);
        printf("\tstart index : %zu\n", trav->start_index);
        printf("\tend index: %zu\n", trav->end_index);
        if (strncmp(trav->area_name, "__cstring", 9) == 0)
        {
            /*
            printf("=======================================\n");
            write(1, trav->section_contents, trav->end_index -
                trav->start_index);
            printf("======================================\n");
            */;
        }

        trav = trav->next;
        counter++;
    }
    return (counter);

}




