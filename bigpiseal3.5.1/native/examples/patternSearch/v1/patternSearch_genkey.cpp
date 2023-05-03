#include <sys/time.h>
#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  timeval t0, t1;
  unsigned long dt = 0;
  gettimeofday(&t0, NULL);

  generate_keys(8192, 4294967296, true);
  
  gettimeofday(&t1, NULL);
  dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);

  cout << "[INFO] keys generation time in seconds: " << ((float)dt)/1000000 << endl;

  return 0;
}
