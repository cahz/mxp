#include "scalar_vec_shl.h"

void scalar_vec_shl_byte(int8_t *output, int8_t *input, const int32_t N){
    int32_t i, j;
    uint8_t m1, m2;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 6;
    	m2 = 1 << 7;

	    for(j = 1; j < 8; j++) {
	    	// If the indices around the shift point are different, an overflow should be triggered
	    	uint8_t bit1 = (input[i] & m1) << 1;
			uint8_t bit2 = (input[i] & m2);
	        if (bit1 ^ bit2) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	        m2 >>= 1;
	    }
	    if (input[i] < 0 && output[i] == 0)	output[i] = 8;
	}
}

void scalar_vec_shl_half(int16_t *output, int16_t *input, const int32_t N){
    int32_t i, j;
    uint16_t m1, m2;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 14;
    	m2 = 1 << 15;
	    for(j = 1; j < 16; j++) {
	    	// If the indices around the shift point are different, an overflow should be triggered
	    	uint16_t bit1 = (input[i] & m1) << 1;
			uint16_t bit2 = (input[i] & m2);
	        if (bit1 ^ bit2) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	        m2 >>= 1;
	    }
	    if (input[i] < 0 && output[i] == 0)	output[i] = 16;
	}
}

void scalar_vec_shl_word(int32_t *output, int32_t *input, const int32_t N){
    int32_t i, j;
    uint32_t m1, m2;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 30;
    	m2 = 1 << 31;
	    for(j = 1; j < 32; j++) {
	    	// If the indices around the shift point are different, an overflow should be triggered
	    	uint32_t bit1 = (input[i] & m1) << 1;
			uint32_t bit2 = (input[i] & m2);
	        if (bit1 ^ bit2) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	        m2 >>= 1;
	    }
	    if (input[i] < 0 && output[i] == 0)	output[i] = 32;
	}
}

// Unsigned we can just check if a bit is set, no need for the bits to flip.
void scalar_vec_shl_ubyte(uint8_t *output, uint8_t *input, const int32_t N){
    int32_t i, j;
    uint8_t m1;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 7;

	    for(j = 1; j <= 8; j++) {
	    	// If the index at the shift point is high, an overflow should be triggered
	    	if (input[i] & m1) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	    }
	}
}

void scalar_vec_shl_uhalf(uint16_t *output, uint16_t *input, const int32_t N){
    int32_t i, j;
    uint16_t m1;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 15;

	    for(j = 1; j <= 16; j++) {
	    	// If the index at the shift point is high, an overflow should be triggered
	    	if (input[i] & m1) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	    }
	}
}

void scalar_vec_shl_uword(uint32_t *output, uint32_t *input, const int32_t N){
    int32_t i, j;
    uint32_t m1;
    for (i = 0; i < N; i++) {
    	m1 = 1 << 31;

	    for(j = 1; j <= 32; j++) {
	    	// If the index at the shift point is high, an overflow should be triggered
	    	if (input[i] & m1) {
	        	output[i] = j;
	        	break;
	        }
	        m1 >>= 1;
	    }
	}
}