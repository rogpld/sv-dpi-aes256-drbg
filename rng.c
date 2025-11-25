#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include "rng.h"

typedef struct {
  unsigned char Key[32];
  unsigned char V[16];
  int reseed_counter;
} AES256_CTR_DRBG_struct;

static AES256_CTR_DRBG_struct DRBG_ctx;

static void AES256_ECB(unsigned char *key, unsigned char *ctr, unsigned char *buffer) {
  AES_KEY aes_key;
  AES_set_encrypt_key(key, 256, &aes_key);
  AES_encrypt(ctr, buffer, &aes_key);
}

static void AES256_CTR_DRBG_Update(unsigned char *provided_data,
                                   unsigned char *Key,
                                   unsigned char *V) {
  unsigned char temp[48];
  int i, j;

  for (i = 0; i < 3; i++) {
    for (j = 15; j >= 0; j--) {
      if (V[j] == 0xff)
        V[j] = 0x00;
      else {
        V[j]++;
        break;
      }
    }
    AES256_ECB(Key, V, temp + 16 * i);
  }

  if (provided_data != NULL)
    for (i = 0; i < 48; i++)
      temp[i] ^= provided_data[i];

  memcpy(Key, temp, 32);
  memcpy(V, temp + 32, 16);
}

void randombytes_init(unsigned char *entropy_input,
                      unsigned char *personalization_string,
                      int security_strength) {
  unsigned char seed_material[48];

  memcpy(DRBG_ctx.Key, entropy_input, 32);
  memset(DRBG_ctx.Key, 0x00, 32);
  memset(DRBG_ctx.V, 0x00, 16);
  DRBG_ctx.reseed_counter = 1;

  for (int i = 0; i < 48; i++) {
    seed_material[i] = entropy_input[i];
    if (personalization_string)
      seed_material[i] ^= personalization_string[i];
  }

  AES256_CTR_DRBG_Update(seed_material, DRBG_ctx.Key, DRBG_ctx.V);
}


int randombytes(unsigned char *x, unsigned long long xlen) {
  unsigned char block[16];
  int i = 0;
  int loop_count;

  while (xlen > 0) {
    for (int j = 15; j >= 0; j--) {
      if (DRBG_ctx.V[j] == 0xff)
        DRBG_ctx.V[j] = 0x00;
      else {
        DRBG_ctx.V[j]++;
        break;
      }
    }

    AES256_ECB(DRBG_ctx.Key, DRBG_ctx.V, block);

    if (xlen > 15) {
      memcpy(x + i, block, 16);
      i += 16;
      xlen -= 16;
    } else {
      memcpy(x + i, block, xlen);
      xlen = 0;
    }
  }

  AES256_CTR_DRBG_Update(NULL, DRBG_ctx.Key, DRBG_ctx.V);
  DRBG_ctx.reseed_counter++;

  return 0;
}
