#include "seal_api.h"

using namespace seal;
using namespace std;


int main(int argc, char **argv)
{
    if (argc != 6)
    {
        // cout << "[ERROR] please enter 1 plaintext values,  prefix  pathstorage(exists) " << endl;
        cout << "[ERROR] please enter plaintext vector value (eg. 75 67 8 23 076 2 23), output ciphertext file name or "
                "prefix, ciphertext output file directory, sample size and public key path"
             << endl;
        return -1;
    }
    else
    {
        string plaintext = argv[1];
        string ciphertext_name = argv[2];
        string ciphertext_dir = argv[3];
        int sample_size = atol(argv[4]);
        string key_dir = argv[5];

        struct encryptor_t encr;
        init_operator_batching(encr, key_dir);

        stringstream ss;
        ss << plaintext;
        vector<int64_t> pod_matrix;
        int64_t x = 0;

        while (ss >> x)
        {
            pod_matrix.push_back(x);
        }

        if (pod_matrix.size() <= encr.bcode->slot_count() / 2 && pod_matrix.size() <= sample_size)
        {
            Ciphertext encrypted_matrix;
            init_ciphermatrix(encr, pod_matrix, encrypted_matrix);
            save_ciphertext(encrypted_matrix, ciphertext_dir + "/" + ciphertext_name + ".ct");
            delete_operator_batching(encr);
            return 0;
        }
        else
        {
            delete_operator_batching(encr);
            return -1;
        }
        // delete_operator_batching(encr);
        // return 0;
    }
}
