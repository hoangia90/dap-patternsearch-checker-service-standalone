#include <iomanip>
#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

string ciphertext_name;
string key_dir;

// bool decrypt(size_t poly_d, size_t p_modulus, int &sample_size, string &ciphertext_dir);
bool decrypt(int &sample_size, string &ciphertext_dir);
void binarySimilarityCalculateDecrypt(int &sample_size, string &ciphertext_dir);
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

        binarySimilarityCalculateDecrypt(sample_size, dir);
        // binarySimilarityCalculateDecrypt1st(sample_size, dir);
        // bool result_str = decrypt(sample_size, dir);
        // cout << result_str << endl;

        return 0;
    }
}

bool decrypt(int &sample_size, string &ciphertext_dir)
{
    struct decryptor_t decr;
    init_operator_batching(decr, key_dir);

    bool isContain = false;
    if (sample_size <= decr.bcode->slot_count() / 2)
    {
        Ciphertext cipher_matrix;

        vector<int64_t> pod_matrix;
        load_ciphertext(decr, cipher_matrix, ciphertext_dir);
        pod_matrix = decrypt_ciphermatrix(decr, cipher_matrix);

        // cout << pod_matrix.size() << endl;

        int no_dual_vectors = (decr.bcode->slot_count() / 2) / (sample_size);

        for (size_t i = 0; i < decr.bcode->slot_count(); i++)
        {
            cout << (pod_matrix[i]);
        }

        vector<int64_t> v1, v2;
        for (size_t i = 0; i < no_dual_vectors * sample_size; i++)
        {
            v1.push_back(pod_matrix[i]);
            v2.push_back(pod_matrix[(pod_matrix.size() / 2) + i]);
        }

        int64_t sum = 0;
        if (isContain == false)
        {
            cout << "1 : ";
            for (size_t i = 0; i < v1.size(); i++)
            {
                cout << v1[i];
                if ((i + 1) % sample_size == 0)
                {
                    cout << endl;
                    if (i < v1.size() - 1)
                    {
                        cout << ((i + 1) / 40) + 1 << " : ";
                    }
                }
                else
                {
                    cout << ", ";
                }

                if (v1[i] == 0)
                {
                    sum = sum + 1;
                }
                else
                {
                    sum = 0;
                }
                if (sum == sample_size)
                {
                    isContain = true;
                }
            }
        }
        cout << endl;

        if (isContain == false)
        {
            sum = 0;
            cout << (v2.size() + 1) / 40 + 1 << " : ";
            for (size_t i = 0; i < v2.size(); i++)
            {
                cout << v2[i];
                if ((i + 1) % sample_size == 0)
                {
                    cout << endl;
                    if (i < v2.size() - 1)
                    {
                        cout << ((v2.size() + i + 1) / 40) + 1 << " : ";
                    }
                }
                else
                {
                    cout << ", ";
                }

                if (v2[i] == 0)
                {
                    sum = sum + 1;
                }
                else
                {
                    sum = 0;
                }
                if (sum == sample_size)
                {
                    isContain = true;
                }
            }
        }

        cout << sample_size;
    }
    else
    {
        cout << endl << "Sample size is too large" << endl;
    }

    delete_operator_batching(decr);
    return isContain;
}

void binarySimilarityCalculateDecrypt(int &sample_size, string &ciphertext_dir)
{
    struct decryptor_t decr;
    init_operator_batching(decr, key_dir);

    if (sample_size <= decr.bcode->slot_count() / 2)
    {
        Ciphertext cipher_matrix;

        vector<int64_t> pod_matrix;
        load_ciphertext(decr, cipher_matrix, ciphertext_dir);
        pod_matrix = decrypt_ciphermatrix(decr, cipher_matrix);

        // cout << pod_matrix.size() << endl;

        int no_dual_vectors = (decr.bcode->slot_count() / 2) / (sample_size);

        vector<int64_t> v1, v2;
        for (size_t i = 0; i < no_dual_vectors * sample_size; i++)
        {
            v1.push_back(pod_matrix[i]);
            v2.push_back(pod_matrix[(pod_matrix.size() / 2) + i]);
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

        float sum2 = 0;
        for (size_t i = 0; i < v2.size(); i++)
        {
            if (v2[i] == 0)
            {
                sum2 = sum2 + 1;
            }

            if ((i + 1) % sample_size == 0)
            {
                // cout << ((v2.size() + i + 1) / 40) << " : ";
                cout << ((sum2 / sample_size) * 100);
                sum2 = 0;
                cout << endl;
            }
        }
    }
    else
    {
        cout << endl << "Sample size is too large" << endl;
    }
    delete_operator_batching(decr);
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

        int unMatched = 0;
        int other = 0;
        float sum = 0;
        for (size_t i = 0; i < v1.size(); i++)
        {
            if (v1[i] == 0)
            {
                sum = sum + 1;
            } else if (v1[i] == 1 || v1[i] == -1)
            {
                unMatched = unMatched + 1;
            } else {
                other = other + 1;
            }

            if ((i + 1) % sample_size == 0)
            {
                // cout << ((i + 1) / 40) << " : ";
                cout << (sum / (sample_size - other) * 100);
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