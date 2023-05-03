#include "add.h"

using namespace std;
using namespace seal;

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, Plaintext &pt, Ciphertext &ct_out)
{
    op_st.eval->add_plain(ct, pt, ct_out);
}

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
  op_st.eval->add(ct1, ct2, ct_out);
}
