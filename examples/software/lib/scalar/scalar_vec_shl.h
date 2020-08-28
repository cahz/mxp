#ifndef SCALAR_VEC_SHL_H
#define SCALAR_VEC_SHL_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void scalar_vec_shl_over_byte(int8_t *output, int8_t *input, const int32_t N);
void scalar_vec_shl_half(int16_t *output, int16_t *input, const int32_t N);
void scalar_vec_shl_word(int32_t *output, int32_t *input, const int32_t N);
void scalar_vec_shl_ubyte(uint8_t *output, uint8_t *input, const int32_t N);
void scalar_vec_shl_uhalf(uint16_t *output, uint16_t *input, const int32_t N);
void scalar_vec_shl_uword(uint32_t *output, uint32_t *input, const int32_t N);

#ifdef __cplusplus
}
#endif
#endif //VBW_VEC_ADD_H