#include "request.h"
#include "error_codes.h"

int create_request(request_t *request, double data)
{
    int error_code = INCORRECT_INPUT;
    if (request)
    {
        error_code = SUCCES;
        request->data = data;
        request->count_of_cycle = 0;
    }

    return error_code;
}

int increase_cycle_request(request_t *request)
{
    int error_code = INCORRECT_INPUT;
    if (request)
    {
        error_code = SUCCES;
        request->count_of_cycle += 1;
    }

    return error_code;
}
int copy_request(request_t *request_dest, request_t *request_source)
{
    int error_code = INCORRECT_INPUT;
    if (request_dest && request_source)
    {
        error_code = SUCCES;
        request_dest->data = request_source->data;
        request_dest->count_of_cycle = request_source->count_of_cycle;
    }

    return error_code;
}

int is_request_full_handled(request_t *request)
{
    return request->count_of_cycle >= 5;
}