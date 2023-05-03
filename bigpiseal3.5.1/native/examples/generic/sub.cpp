#include "sub.h"
 
using namespace std;
using namespace seal;

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, Plaintext &pt, Ciphertext &ct_out)
{
  timeval t0, t1;
  unsigned long dt = 0;

  gettimeofday(&t0, NULL);
  op_st.eval->sub_plain(ct, pt, ct_out);
  gettimeofday(&t1, NULL);
  dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);

  cout << "[INFO] Homomorphic subtraction (pt+ct) time in (us): " << dt << endl;
}

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
  timeval t0, t1;
  unsigned long dt = 0;

  gettimeofday(&t0, NULL);
  op_st.eval->sub(ct1, ct2, ct_out);
  gettimeofday(&t1, NULL);
  dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);

  cout << "[INFO] Homomorphic subtraction (ct+ct) time in (us): " << dt << endl;
}
