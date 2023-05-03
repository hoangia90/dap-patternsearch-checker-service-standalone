#include <cstdint>
#include <sys/time.h>
#include <boost/lexical_cast.hpp>
#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  if(argc != 5)
    cerr << "[ERROR] please enter 1 plaintext values,  prefix ,  pathstorage(exists) " << endl;
// ./generic_encrypt 21 ct1 /home/bigpi/  storage/
    
  else {
    timeval t0, t1;
    unsigned long dt = 0;
    struct encryptor_t encr;
    string pathK = argv[3];
    string Prefix = argv[2];
    string pathStorage = argv[4];
    //cout << "[INFO] Prefix . : " << Prefix << endl;
    string prefix("");
    //string postfix1(".ct");
    prefix="";
    if (suffix_exist(pathK, "/")) 
    { 
       prefix.append(pathK);   
    }
    else
    { 
      prefix.append(pathK);    
      prefix.append("/");
    }
    init_operator(8192, 4294967296, encr,prefix);

    Ciphertext ct;

    int64_t plain = boost::lexical_cast<int64_t>(argv[1]);
    gettimeofday(&t0, NULL);
    init_ciphertext(encr, plain, ct);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] plaintext encryption time in seconds: " << ((float)dt)/1000000 << endl;
    prefix="";
    if (suffix_exist(pathStorage, "/")) 
    { 
       prefix.append(pathStorage);   
    }
    else
    { 
      prefix.append(pathStorage);    
      prefix.append("/");
    }
    prefix.append(Prefix);
    prefix.append(".ct");
    //cout << "[INFO] suffix .ct : " << prefix << endl;
    save_ciphertext(ct, prefix);

    //~ plain = boost::lexical_cast<int64_t>(argv[2]);
    //~ init_ciphertext(encr, plain, ct);
    //~ save_ciphertext(ct, "ct2.ct");

    delete_operator(encr);

    return 0;
  }
}
