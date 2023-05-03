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

        struct cencryptor_t encr;
        init_operator_ckks(encr, key_dir);

        stringstream ss;
        ss << plaintext;
        vector<double> pod_matrix;
        double x = 0;

        while (ss >> x)
        {
            pod_matrix.push_back(x);
        }

        if (pod_matrix.size() <= encr.ccode->slot_count() && pod_matrix.size() >= sample_size)
        {
            Ciphertext encrypted_matrix;
            init_ciphertext_ckks(encr, pod_matrix, encrypted_matrix);
            save_ciphertext(encrypted_matrix, ciphertext_dir + "/" + ciphertext_name + ".ct");
            delete_operator_ckks(encr);
            return 0;
        }
        else
        {
            delete_operator_ckks(encr);
            return -1;
        }
        delete_operator_ckks(encr);
        return 0;
    }
}
