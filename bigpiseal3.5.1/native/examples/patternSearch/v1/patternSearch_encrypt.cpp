#include "seal_api.h"

using namespace seal;
using namespace std;

int main(int argc, char **argv)
{
  if(argc != 5)
    // cout << "[ERROR] please enter 1 plaintext values,  prefix  pathstorage(exists) " << endl;
    // cout << "[ERROR] please enter plaintext value (eg. 75 67 8 23 076 2 23), public key path, ciphertext output directory and ciphertext output file name" << endl;
    cout << "[ERROR] please enter plaintext vector value (eg. 75 67 8 23 076 2 23), output ciphertext file name or prefix, public key path and ciphertext output file directory" << endl;
  else {
    string plaintext = argv[1];
    string ciphertext_name = argv[2];

    string public_key_path = argv[3];
    string ciphertext_dir = argv[4];

    // cout << plaintext << endl;

    struct encryptor_t encr;
    // init_operator(2048, 256, encr, public_key_path);
    init_operator(encr, public_key_path);

    stringstream ss;
    ss << plaintext;

    int64_t x = 0;
    int index = 0;
    Ciphertext ct;
    while (ss >> x)
    {
      /* Encrypt */
      init_ciphertext(encr, x, ct);
      save_ciphertext(ct, ciphertext_dir + "/" + ciphertext_name + "_" + to_string(index) + ".ct");
      index++;
    }

    delete_operator(encr);

    return 0;
  }
}
