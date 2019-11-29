#ifndef __UNIVERSAL_H__
#define __UNIVERSAL_H__

void universal_swap(void *first, void *second, size_t size);
int compare_int64(int64_t *first, int64_t *second);
int fscanf_int64(FILE* source, int64_t *elem);
void fprintf_int64(FILE* source, int64_t *elem);
int fscanf_int(FILE* source, int *elem);
void fprintf_int(FILE* source, int *elem);
uint64_t tick(void);

#endif