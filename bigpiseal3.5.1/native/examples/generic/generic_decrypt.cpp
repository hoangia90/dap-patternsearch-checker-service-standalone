#include <sys/time.h>
#include "seal_api.h"

using namespace std;
using namespace seal;

int main(int argc, char **argv)
{
  if(argc != 4)
    cout << "[ERROR] please enter prefix_file_to_decrypt full/path/key /full/path/to/storage" << endl;
//  ./_decrypt prefix_name ct3  /home/bigpi/ storage/
  else {
    timeval t0, t1;
    unsigned long dt = 0;
    struct decryptor_t decr;
    string pathK = argv[2];
    string Ctfile = argv[1];
    string prefix("");
    if (suffix_exist(pathK, "/")) 
    { 
       prefix.append(pathK);   
    }
    else
    { 
      prefix.append(pathK);    
      prefix.append("/");
    }

    //cout << "[INFO] Keypathname sk: " << prefix << endl;
    init_operator(8192, 4294967296, decr,prefix);


    // path to storage argv[3]
    string pathStorage = argv[3];   
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

    //cout << "[INFO] Ctx de " << prefix << endl;


    Ciphertext ct;
    
    if (Ctfile.at(0) ==  '/')
	load_ciphertext(decr, ct, Ctfile);
    else {
       prefix.append(Ctfile);
	load_ciphertext(decr, ct, prefix);
    }
    gettimeofday(&t0, NULL);
    load_ciphertext(decr, ct, prefix);


    gettimeofday(&t0, NULL);
    decrypt_ciphertext(decr, ct);
    gettimeofday(&t1, NULL);
    dt = 1000000 * (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec);
    cout << "[INFO] ciphertext decryption time in seconds: " << ((float)dt)/1000000 << endl;

    delete_operator(decr);

    return 0;
  }
}
