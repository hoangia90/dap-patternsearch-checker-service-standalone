#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  string key_dir = argv[1];

  // size_t poly_d = 4096;
  // size_t poly_d = 8192;
  size_t poly_d = 16384;

  // Params option 1
  // int bit_size = 20;
  int bit_size = 0;

  // Params option 2
  // uint64_t plain_modulus = 1032193;
  // vector<int> bit_sizes = { 36, 36, 37 };

  // timeval t0, t1;
  // unsigned long dt = 0;
  // gettimeofday(&t0, NULL);

  generate_keys_ckks(poly_d, bit_size, key_dir, true);
  // batching_generate_keys(poly_d, bit_sizes, plain_modulus, key_dir, true);

  // gettimeofday(&t1, NULL);
  // dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
  // cout << "[INFO] keys generation time in seconds: " << ((float)dt)/1000000 << endl;

  return 0;
}
