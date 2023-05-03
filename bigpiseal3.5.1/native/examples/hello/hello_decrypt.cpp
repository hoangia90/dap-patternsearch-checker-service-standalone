#include <sys/time.h>
#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  if(argc != 2)
    cout << "[ERROR] please enter a ciphertext file" << endl;
  else {
    timeval t0, t1;
    unsigned long dt = 0;
    struct decryptor_t decr;

    init_operator(8192, 4294967296, decr);

    Ciphertext ct;

    gettimeofday(&t0, NULL);
    load_ciphertext(decr, ct, argv[1]);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] ciphertext loading time in seconds: " << ((float)dt)/1000000 << endl;

    gettimeofday(&t0, NULL);
    decrypt_ciphertext(decr, ct);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] ciphertext decryption time in seconds: " << ((float)dt)/1000000 << endl;

    delete_operator(decr);

    return 0;
  }
}
