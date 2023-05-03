#include <cstdint>
#include <sys/time.h>
#include <boost/lexical_cast.hpp>
#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  if(argc != 3)
    cout << "[ERROR] please enter 2 plaintext values" << endl;
  else {
    timeval t0, t1;
    unsigned long dt = 0;
    struct encryptor_t encr;

    init_operator(8192, 4294967296, encr);

    Ciphertext ct;

    int64_t plain = boost::lexical_cast<int64_t>(argv[1]);
    gettimeofday(&t0, NULL);
    init_ciphertext(encr, plain, ct);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] plaintext encryption time in seconds: " << ((float)dt)/1000000 << endl;
    save_ciphertext(ct, "ct1.ct");

    plain = boost::lexical_cast<int64_t>(argv[2]);
    init_ciphertext(encr, plain, ct);
    save_ciphertext(ct, "ct2.ct");

    delete_operator(encr);

    return 0;
  }
}
