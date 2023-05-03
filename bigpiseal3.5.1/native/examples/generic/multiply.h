#ifndef _MULT_H_
#define _MULT_H_

#include <sys/time.h>
#include <iostream>
#include <string>
#include "seal/seal.h"
#include "seal_api.h"

void multiply_ciphertext(struct evaluator_t& op_st, seal::Ciphertext &ct, seal::Plaintext &pt, seal::Ciphertext &ct_out);
void multiply_ciphertext(struct evaluator_t& op_st, seal::Ciphertext &ct1, seal::Ciphertext &ct2, seal::Ciphertext &ct_out);

#endif
