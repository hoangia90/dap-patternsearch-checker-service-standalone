#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

string ciphertext_name;
string secret_key_path;

string decrypt(string &ciphertext_dir);
bool decrypt_vector(string &ciphertext_dir);
string decrypt_vectors(string &parent_dir);
bool decrypt_isContain(string &result);

int main(int argc, char **argv)
{
    if (argc != 3)
    // cout << "[ERROR] please enter /full/path/to/file/to/decrypt full/path/key " << endl;
    // cout << "[ERROR] please enter prefix_file_to_decrypt full/path/key /full/path/to/storage" << endl;
    // cout << "[ERROR] please enter a ciphertext name, ciphertext directory and secret key path" << endl;
    cout << "[ERROR] please enter a ciphertext file path and secret key path" << endl;
    else
    {
        string dir = argv[1];
        secret_key_path = argv[2];
        
        string result_str = decrypt(dir);
        // cout << result_str << endl;
        bool result = decrypt_isContain(result_str);
        cout << result << endl;

        return 0;
    }
}

bool decrypt_isContain(string &result)
{
    long result_l = atol(result.c_str());
    if (result_l == 0)
    {
        // cout << "true";
        return true;
    }
    else
    {
        // cout << "false";
        return false;
    }
}

string decrypt(string &ciphertext_dir)
{
    struct decryptor_t decr;
    init_operator(decr, secret_key_path);
    Ciphertext ct;
    string str;
    load_ciphertext(decr, ct, ciphertext_dir);
    str = to_string(decrypt_ciphertext_and_return_value(decr, ct));
    // decrypt_ciphertext(decr, ct);
    delete_operator(decr);
    return str;
}

// Used for dynamic search
// string decrypt_vectors(string &parent_dir)
// {
//     vector<string> directories = get_directories(parent_dir);
//     string path_result = "";
//     bool result;
//     for (const auto &entry : directories)
//     {
//         string ciphertext_dir = entry + "/";
//         cout << ciphertext_dir << endl;
//         result = decrypt_vector(ciphertext_dir);
//         if (result == true)
//         {
//             path_result = ciphertext_dir;
//             break;
//         }
//     }
//     return path_result;
// }

// Used for dynamic search
// bool decrypt_vector(string &ciphertext_dir)
// {
//     int nFiles = findNumberOfFilesInDirectory(ciphertext_dir);

//     struct decryptor_t decr;
//     init_operator(2048, 256, decr, secret_key_path);

//     Ciphertext ct;
//     string plaintext;
//     stringstream ss;
//     for (int index = 0; index <= nFiles - 1; index++)
//     {
//         load_ciphertext(decr, ct, ciphertext_dir + "/" + ciphertext_name + "_" + to_string(index) + ".ct");
//         plaintext = decrypt_ciphertext_and_return_string(decr, ct);

//         if (index == nFiles - 1)
//         {
//             ss << plaintext;
//         }
//         else
//         {
//             ss << plaintext << " ";
//         }
//     }
//     // cout << to_string(ss.str().size());
//     // cout << ss.str() << endl;
//     int x;
//     int index = 0;
//     bool result = false;
//     while (ss >> x)
//     {
//         if (x == 0)
//         {
//             result = true;
//         }
//         else
//         {
//             result = false;
//             break;
//         }
//         index++;
//     }
//     // if (index > 0 && result == true)
//     // {
//     //     cout << "true" << endl;
//     // }
//     delete_operator(decr);
//     return result;
// }
