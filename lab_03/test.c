#include "sparse_matrix.h"
#include "error_codes.h"

int main()
{
    sparse_matrix smatrix;

    
    create_smatrix(&smatrix);
    change_size_smatrix(&smatrix, 10, 10, 5);
    input_smatrix(&smatrix, stdin);
    print_smatrix_source(&smatrix);
    print_smatrix_pretty(&smatrix);
    delete_smatrix_content(&smatrix);

    getchar();getchar();
    return SUCCES;
}