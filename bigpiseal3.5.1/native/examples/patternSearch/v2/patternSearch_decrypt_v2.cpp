#include <iomanip>
#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

string ciphertext_name;
string key_dir;

// vector<int64_t> decrypt(size_t poly_d, size_t p_modulus, int &sample_size, string &ciphertext_dir);
vector<int64_t> decrypt(int &sample_size, string &ciphertext_dir);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        // cout << "[ERROR] please enter /full/path/to/file/to/decrypt full/path/key " << endl;
        // cout << "[ERROR] please enter prefix_file_to_decrypt full/path/key /full/path/to/storage" << endl;
        cout << "[ERROR] please enter a ciphertext file path, sample size and secret key path" << endl;
        return -1;
    }
    else
    {
        string dir = argv[1];
        int sample_size = atol(argv[2]);
        key_dir = argv[3];

        vector<int64_t> result = decrypt(sample_size, dir);

        for (int i = 0; i < result.size(); ++i)
        {
            std::cout << result[i] << ' ';
        }

        std::cout << endl;

        return 0;
    }
}


vector<int64_t> decrypt(int &sample_size, string &ciphertext_dir)
{
    struct decryptor_t decr;
    init_operator_batching(decr, key_dir);
    // init_operator_batching(2048, 4294967296, decr, key_dir);
    // init_operator_batching(4096, 4294967296, decr, key_dir);
    // init_operator_batching(8192, 4294967296, decr, key_dir);
    // init_operator_batching(16384, 4294967296, decr, key_dir);
    // init_operator_batching(32768, 4294967296, decr, key_dir);

    vector<int64_t> v;
    if (sample_size <= decr.bcode->slot_count()/2)
    {
        Ciphertext cipher_matrix;

        vector<int64_t> pod_matrix;
        load_ciphertext(decr, cipher_matrix, ciphertext_dir);
        pod_matrix = decrypt_ciphermatrix(decr, cipher_matrix);

        for (size_t i = 0; i < sample_size; i++)
        {
            v.push_back(pod_matrix[i]);
        }
    }
    else
    {
        // cout << endl << "Sample size is too large" << endl;
    }
    delete_operator_batching(decr);
    return v;
}
