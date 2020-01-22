/*
 * Memcopy test 
 *
 * Copyright (C) 2020 EBOTS Inc
 * Author: Hung Lam
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <time.h>

#define MEM_TEST_SIZE 		0x100000	// 1MB

#define NANO_PER_SECOND		1000000000

//#define PRINT_OUT

// global variables definition
uint32_t *pSRC;
uint32_t *pDST;
uint32_t test_size; 
struct timespec tv1, tv2, tvdif; 
float speedrate; 

int user_input; 

uint32_t PAT_GEN(uint32_t nIndex)
{
	uint32_t Data;
	Data = nIndex & 0xFFFFFFFF;
	return Data;
}

int main(void){
	
	std::cout << " Test copy 1MB data using memcpy!" << std::endl; 
	test_size = MEM_TEST_SIZE;
	std::cout << " Test_size: " << test_size << std::endl;

	pSRC = (uint32_t *)malloc(test_size); 
	pDST = (uint32_t *)malloc(test_size); 
	if (( pSRC == NULL) || ( pDST == NULL)){
		std::cout << " Failed to allocate memory!"	<< std::endl; 
		return -1;
	}

	// init test pattern
	for (uint32_t i = 0; i < (test_size>>2); i++)
	{
		*(pSRC + i) = PAT_GEN(i);
	}
	// mem copy
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tv1);
	memcpy((void *)pDST, (void *)pSRC, test_size);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tv2);

	// print out the result if require
#ifdef PRINT_OUT
	for (uint32_t i = 0; i < (test_size>>2); i++){
		uint32_t data_1 = *(pDST + i);
		uint32_t data_2 = *(pSRC + i);
		std::cout << " pDST[" << i << "]" << ":= 0x" << std::hex << data_1 << std::dec << " pSRC[" << i << "]" << ":= 0x" << std::hex << data_2 << std::dec << std::endl;
	}	
#endif	
	// print out timing result
	std::cout << " Time 1: " << tv1.tv_sec << "s" << " " << tv1.tv_nsec << "ns" << std::endl; 
	std::cout << " Time 2: " << tv2.tv_sec << "s" << " " << tv2.tv_nsec << "ns" << std::endl; 

	// speed rate calculation
	tvdif.tv_sec = tv2.tv_sec - tv1.tv_sec; 
	tvdif.tv_nsec = tv2.tv_nsec - tv1.tv_nsec;
	tvdif.tv_nsec = tvdif.tv_sec*NANO_PER_SECOND + tvdif.tv_nsec; 

	speedrate = NANO_PER_SECOND/tvdif.tv_nsec;
	std::cout << "1MB: " << tvdif.tv_nsec << "nsec" << std::endl;  
	std::cout << "Speed rate: " << speedrate << "MB/s" << std::endl; 

	// free memory
	if(pSRC)
		free(pSRC); 
	if(pDST)
		free(pDST);

}