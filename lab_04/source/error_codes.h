#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

/*
#define SUCCES 0           // Succes

#define INPUT_ERROR 1      // Error in process of input values
#define CALCULATE_ERROR 2  // Error in process of calculation
#define CREATE_ERROR 3     // Error impossibility of create data
#define MEMORY_ERROR 4     // Error in using memory
#define RESIZE_ERROR 5     // Error in realloc
#define LOGIC_ERROR 6      // Error in alghoritm
#define INCORRECT_INPUT 7  // Error incorrect input data in function
*/

enum error_codes
{
	SUCCES,
	INPUT_ERROR,
	OUTPUT_ERROR,
	CALCULATE_ERROR,
	CREATE_ERROR,
	MEMORY_ERROR,
	RESIZE_ERROR,
	LOGIC_ERROR,
	INCORRECT_INPUT,
	END_OF_INPUT,
	EOL_UNREACHED,
};

#endif