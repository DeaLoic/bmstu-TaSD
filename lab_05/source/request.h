#ifndef __REQUEST_H__
#define __REQUEST_H__

typedef struct request_t
{
    double data;
    int count_of_cycle;
} request_t;

int create_request(request_t *request, double data);
int increase_cycle_request(request_t *request);
int copy_request(request_t *request_dest, request_t *request_source);

int is_request_full_handled(request_t *request);
#endif