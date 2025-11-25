#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rng.h"

#ifdef __cplusplus
extern "C" {
#endif

void dpi_rng_init() {
  unsigned char entropy_input[48];
  unsigned char personalization_string[48];
  for(int i=0; i<48; i++) {
    entropy_input[i] = (unsigned char)i;
    personalization_string[i] = (unsigned char)(48-i);
  }
  printf("[C-DPI] Initializing NIST RNG...\n");
  randombytes_init(entropy_input, personalization_string, 256);
}

int dpi_get_random_u32(uint32_t *out_val) {
  unsigned char buffer[4];
  int status = randombytes(buffer, 4);

  *out_val = (uint32_t)buffer[0] |
    ((uint32_t)buffer[1] << 8) |
    ((uint32_t)buffer[2] << 16) |
    ((uint32_t)buffer[3] << 24);

  return status;
}

#ifdef __cplusplus
}
#endif
