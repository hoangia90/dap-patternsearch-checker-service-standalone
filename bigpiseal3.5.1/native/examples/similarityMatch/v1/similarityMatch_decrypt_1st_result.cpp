#include <iomanip>
#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

string ciphertext_name;
string key_dir;

void binarySimilarityCalculateDecrypt1st(int &sample_size, string &ciphertext_dir);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        // cout << "[ERROR] please enter /full/path/to/file/to/decrypt full/path/key " << endl;
        // cout << "[ERROR] please enter prefix_file_to_decrypt full/path/key /full/path/to/storage" << endl;
        // cout << "[ERROR] please enter a ciphertext file path, sample size and secret key path" << endl;
        return -1;
    }
    else
    {
        string dir = argv[1];
        int sample_size = atol(argv[2]);
        key_dir = argv[3];

        binarySimilarityCalculateDecrypt1st(sample_size, dir);

        return 0;
    }
}

void binarySimilarityCalculateDecrypt1st(int &sample_size, string &ciphertext_dir)
{
    struct decryptor_t decr;
    init_operator_batching(decr, key_dir);

    if (sample_size <= decr.bcode->slot_count() / 2)
    {
        Ciphertext cipher_matrix;

        vector<int64_t> pod_matrix;
        load_ciphertext(decr, cipher_matrix, ciphertext_dir);
        pod_matrix = decrypt_ciphermatrix(decr, cipher_matrix);

        vector<int64_t> v1;
        for (size_t i = 0; i < sample_size; i++)
        {
            v1.push_back(pod_matrix[i]);
        }

        float sum = 0;
        for (size_t i = 0; i < v1.size(); i++)
        {
            if (v1[i] == 0)
            {
                sum = sum + 1;
            }

            if ((i + 1) % sample_size == 0)
            {
                // cout << ((i + 1) / 40) << " : ";
                cout << ((sum / sample_size) * 100);
                sum = 0;
                cout << endl;
            }
        }
    }
    else
    {
        cout << endl << "Sample size is too large" << endl;
    }

    delete_operator_batching(decr);
    // return isContain;
}