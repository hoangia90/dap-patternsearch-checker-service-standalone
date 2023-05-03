#include <sys/time.h>
#include "add.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  if(argc != 3)
    cout << "[ERROR] please enter 2 ciphertext files" << endl;
  else {
    timeval t0, t1;
    unsigned long dt = 0;
    struct evaluator_t eval;

    init_operator(8192, 4294967296, eval);

    Ciphertext ct1, ct2, ct3;
    cout << "[INFO] loading ciphertext 1" << endl;
    load_ciphertext(eval, ct1, "ct1.ct");

    cout << "[INFO] loading ciphertext 2" << endl;
    load_ciphertext(eval, ct2, "ct2.ct");

    cout << "[INFO] adding ciphertext 1 to ciphertext 2" << endl;
    gettimeofday(&t0, NULL);
    add_ciphertext(eval, ct1, ct2, ct3);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] homomorphic addition time in seconds: " << ((float)dt)/1000000 << endl;

    cout << "[INFO] saving ciphertext addition to a new ciphertext file" << endl;
    save_ciphertext(ct3, "ct3.ct");

    delete_operator(eval);

    return 0;
  }
}
