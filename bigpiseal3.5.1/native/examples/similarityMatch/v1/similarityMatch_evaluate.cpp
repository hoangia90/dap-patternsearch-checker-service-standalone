// #include <algorithm>
// #include <iterator>
// #include <vector>
// #include <filesystem>
#include <iostream>
#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void multiply_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

bool is_number(const string &s);

void printStrVector(const vector<string> &v);

void multiply_ciphertexts(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void relinearize_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void rescale_to_next_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void multiply_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void relinearize(struct evaluator_t &op_st, Ciphertext &ct, Ciphertext &ct_out);

void sub_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void negate_inplace__ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

void add_plain_inplace_ciphertext(struct evaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain);

void multiply_plain_inplace(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void add_many_ciphertext(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void exponentiate_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, uint64_t &exponent);

void sub_plain_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void mod_switch_to_next_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

int computeSimilarity(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir);

int checkSq(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir);

// string relink_key_path;
// string galois_key_path;
// string public_key_path;
string key_dir = "";

vector<vector<string>> split_ends(const vector<string> &data, const vector<int> &ends);

Ciphertext check(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir,
    struct encryptor_t &encr, struct evaluator_t &eval);

int main(int argc, char **argv)
{
    // input processing - begin
    // string result_name = argv[argc - 6];
    // string result_dir = argv[argc - 5];
    // int sample_size = atoi(argv[argc - 4]);
    // relink_key_path = argv[argc - 3];
    // galois_key_path = argv[argc - 2];
    // public_key_path = argv[argc - 1];
    string source = argv[1];

    string result_name = argv[argc - 4];
    string result_dir = argv[argc - 3];
    int sample_size = atoi(argv[argc - 2]);
    key_dir = argv[argc - 1];

    vector<string> data;
    for (int i = 2; i < argc - 4; i++)
    {
        data.push_back(argv[i]);
    }

    // if (source == "" || data.size() == 0 || result_name == "" || result_dir == "" || sample_size == 0 ||
    //     relink_key_path == "" || galois_key_path == "" || public_key_path == "")
    if (source == "" || data.size() == 0 || result_name == "" || result_dir == "" || sample_size == 0 || key_dir == "")
    {
        // error handling
        cout << "[ERROR] please enter a source path, data paths, output ciphertext file name or prefix, output "
                "ciphertext directory, sample size, linking key path, galois key path and public key path"
             << endl;
        return -1;
    }
    // input processing - end

    int result = computeSimilarity(source, data, result_name, result_dir, sample_size, key_dir);
    // int result = checkSq(source, data, result_name, result_dir, sample_size, key_dir);
    // checkSq(source, data, result_name, result_dir, sample_size, relink_key_path, galois_key_path, public_key_path);

    // error handling
    if (result == -1)
    {
        fprintf(stderr, "error!\n");
    }
    else
    {
        cout << "done";
    }

    return result;
}

int computeSimilarity(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir)
{
    // cout << "\n[INFO] Start Similarity Search Algorithm!" << endl;

    // cout << "\n[INFO] Start Initializing Evaluator!" << endl;
    struct evaluator_t eval;
    init_operator_batching(eval, key_dir);
    // cout << "[INFO] End Initializing Evaluator!" << endl;

    // cout << "\n[INFO] Start Initializing Encryptor!" << endl;
    struct encryptor_t encr;
    init_operator_batching(encr, key_dir);
    // cout << "[INFO] End Initializing Encryptor!" << endl;

    // cout << "\n[INFO] Input Parameters:" << endl;
    // cout << " Sample Size: " << sample_size << endl;
    // cout << " Required Slots (Sample Size x Data Size): " << sample_size * data.size() << endl;
    // cout << " Provided Slots: " << encr.bcode->slot_count() << endl;

    if (sample_size * data.size() > encr.bcode->slot_count() || sample_size > encr.bcode->slot_count() / 2)
    {
        // Error handling
        delete_operator_batching(encr);
        delete_operator_batching(eval);
        return -1;
    }
    else
    {
        Ciphertext encrypted_result_matrix;
        vector<int64_t> result_matrix;
        init_ciphermatrix(encr, result_matrix, encrypted_result_matrix);

        vector<int64_t> dummy_matrix;
        for (size_t i = 0; i < sample_size; i++)
        {
            dummy_matrix.push_back(1);
        }

        Ciphertext encrypted_dummy_matrix;
        init_ciphermatrix(encr, dummy_matrix, encrypted_dummy_matrix);

        // Normalizing data input if the number ciphertext is odd
        int normalized_data_size;
        if (data.size() % 2 == 0)
        {
            normalized_data_size = data.size();
        }
        else
        {
            normalized_data_size = data.size() + 1;
        }

        // cout << "[INFO] normalized_data_size: " << normalized_data_size << endl;

        int normalized_required_slots = normalized_data_size * sample_size;
        int half_normalized_required_slots = normalized_required_slots / 2;
        // int required_range_row = normalized_required_slots / 2;

        // Create padding matrix
        int padding_slots = (encr.bcode->slot_count() / 2) - half_normalized_required_slots;

        // cout << "[INFO] padding_slots: " << padding_slots << endl;

        vector<int64_t> padding_matrix(encr.bcode->slot_count(), 0ULL);
        for (size_t i = 0; i < padding_slots; i++)
        {
            padding_matrix[half_normalized_required_slots + i] = 1;
            padding_matrix[encr.bcode->slot_count() - 1 - i] = 1;
        }
        Ciphertext encrypted_padding_matrix;
        init_ciphermatrix(encr, padding_matrix, encrypted_padding_matrix);

        if (half_normalized_required_slots > 0 && half_normalized_required_slots <= encr.bcode->slot_count())
        {
            for (int index = 0; index < normalized_data_size / 2; index++)
            {
                Ciphertext ct1, ct2, ct3;
                Ciphertext temp1, temp2;

                // cout << "[INFO] loading ciphertext 1" << endl;
                load_ciphertext(eval, ct1, source);

                // cout << "[INFO] loading ciphertext 2" << endl;
                load_ciphertext(eval, ct2, data.at(index));

                sub_ciphertext(eval, ct1, ct2, temp1);

                if ((normalized_data_size / 2) + index < data.size())
                {
                    // cout << "[INFO] loading ciphertext 3" << endl;
                    load_ciphertext(eval, ct3, data.at((normalized_data_size / 2) + index));
                    sub_ciphertext(eval, ct1, ct3, temp2);
                }
                else
                {
                    // Add dummy vector for oddy data

                    temp2 = encrypted_dummy_matrix;
                }
                // Switching column
                eval.eval->rotate_columns_inplace(temp2, eval.gk);
                add_ciphertext(eval, temp1, temp2, temp1);
                add_ciphertext(eval, temp1, encrypted_result_matrix, encrypted_result_matrix);
                // Shifting slots
                // cout << "[INFO] index: " << index << endl;
                // eval.eval->rotate_rows_inplace(encrypted_result_matrix, +sample_size, eval.gk);
                // avoid the last shift
                if (index + 1 != (normalized_data_size / 2))
                {
                    eval.eval->rotate_rows_inplace(encrypted_result_matrix, -sample_size, eval.gk);
                }
            }
            add_ciphertext(eval, encrypted_result_matrix, encrypted_padding_matrix, encrypted_result_matrix);
            // Shifting the remaining slots
            // eval.eval->rotate_rows_inplace(encrypted_result_matrix, +((encr.bcode->slot_count() - sample_size *
            // data.size()) / 2), eval.gk); eval.eval->rotate_rows_inplace(encrypted_result_matrix,
            // +((encr.bcode->slot_count()%sample_size))/2, eval.gk);
        }

        save_ciphertext(encrypted_result_matrix, result_dir + "/" + result_name + ".ct");
        delete_operator_batching(encr);
        delete_operator_batching(eval);

        // cout << "\n[INFO] End Similarity Search Algorithm!" << endl;

        return 0;
    }
}






// This is advance algorithm - Testing
// int checkSq(
//     string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size,
//     string &relink_key_path, string &galois_key_path, string &public_key_path)
int checkSq(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir)
{
    struct evaluator_t eval;
    // init_operator_batching(2048, 4294967296, eval, relink_key_path, galois_key_path);
    // init_operator_batching(4096, 4294967296, eval, relink_key_path, galois_key_path);
    // init_operator_batching(8192, 4294967296, eval, relink_key_path, galois_key_path);
    // init_operator_batching(16384, 4294967296, eval, relink_key_path, galois_key_path);
    // init_operator_batching(32768, 4294967296, eval, relink_key_path, galois_key_path);
    init_operator_batching(eval, key_dir);

    struct encryptor_t encr;
    // init_operator_batching(4096, 4294967296, encr, public_key_path);
    // init_operator_batching(8192, 4294967296, encr, public_key_path);
    // init_operator_batching(16384, 4294967296, encr, public_key_path);
    // init_operator_batching(32768, 4294967296, encr, public_key_path);
    init_operator_batching(encr, key_dir);

    // if (sample_size*data.size() > encr.bcode->slot_count() || sample_size > encr.bcode->slot_count()/2)
    if (sample_size > encr.bcode->slot_count() / 2)
    {
        // error handling
        delete_operator_batching(encr);
        delete_operator_batching(eval);
        return -1;
    }
    else
    {
        // struct evaluator_t eval;
        // // init_operator_batching(2048, 4294967296, eval, relink_key_path, galois_key_path);
        // // init_operator_batching(4096, 4294967296, eval, relink_key_path, galois_key_path);
        // init_operator_batching(8192, 4294967296, eval, relink_key_path, galois_key_path);
        // // init_operator_batching(16384, 4294967296, eval, relink_key_path, galois_key_path);
        // // init_operator_batching(32768, 4294967296, eval, relink_key_path, galois_key_path);

        // struct encryptor_t encr;
        // // init_operator_batching(4096, 4294967296, encr, public_key_path);
        // init_operator_batching(8192, 4294967296, encr, public_key_path);
        // // init_operator_batching(16384, 4294967296, encr, public_key_path);
        // // init_operator_batching(32768, 4294967296, encr, public_key_path);

        int capacity = (encr.bcode->slot_count()) / sample_size;
        // cout << capacity << endl;

        // vector<string> v_temp;
        // vector<string> v_v_temp;
        // Ciphertext result;
        vector<Ciphertext> v_result;
        int nSq = data.size() / capacity;
        for (size_t i = 0; i < nSq; i++)
        {
            Ciphertext result;
            // cout << "sq : " << i << endl;
            vector<string> v_temp;
            for (size_t j = 0; j < capacity; j++)
            {
                string str = data.back();
                v_temp.push_back(str);
                data.pop_back();
            }
            if (i == 0)
            {
                // cout << "sq : init" << endl;
                // result = check(
                //     source, v_temp, result_name, result_dir, sample_size, relink_key_path, galois_key_path,
                //     public_key_path, encr, eval);
                result = check(source, v_temp, result_name, result_dir, sample_size, key_dir, encr, eval);
                v_result.push_back(result);
            }
            else
            {
                // cout << "sq : other" << endl;
                // Ciphertext result2 = check(
                //     source, v_temp, result_name, result_dir, sample_size, relink_key_path, galois_key_path,
                //     public_key_path, encr, eval);
                // multiply_ciphertext(eval, result2, result, result);
                // relinearize_inplace(eval, result);
                // result = check(
                //     source, v_temp, result_name, result_dir, sample_size, relink_key_path, galois_key_path,
                //     public_key_path, encr, eval);
                result = check(source, v_temp, result_name, result_dir, sample_size, key_dir, encr, eval);
                v_result.push_back(result);
            }
        }

        if (data.size() % capacity != 0)
        {
            // cout << "oddy!!! " << endl;
            // Ciphertext result = check(
            //     source, data, result_name, result_dir, sample_size, relink_key_path, galois_key_path,
            //     public_key_path, encr, eval);
            Ciphertext result = check(source, data, result_name, result_dir, sample_size, key_dir, encr, eval);
            // multiply_ciphertext(eval, result2, result, result);
            // relinearize_inplace(eval, result);
            v_result.push_back(result);
        }

        Ciphertext result;
        multiply_ciphertexts(eval, v_result, result);
        relinearize_inplace(eval, result);

        save_ciphertext(result, result_dir + "/" + result_name + ".ct");
        delete_operator_batching(encr);
        delete_operator_batching(eval);

        return 0;
    }
}

// Ciphertext check(
//     string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size,
//     string &relink_key_path, string &galois_key_path, string &public_key_path, struct encryptor_t &encr,
//     struct evaluator_t &eval)
Ciphertext check(
    string &source, vector<string> &data, string &result_name, string &result_dir, int &sample_size, string &key_dir,
    struct encryptor_t &encr, struct evaluator_t &eval)
{
    // if (source == "" || data.size() == 0 || result_name == "" || result_dir == "" || sample_size == 0)
    // {
    //     // error handling
    //     // return -1;

    // }
    // else
    // {

    Ciphertext encrypted_result_matrix;
    vector<int64_t> result_matrix;
    init_ciphermatrix(encr, result_matrix, encrypted_result_matrix);

    vector<int64_t> dummy_matrix;
    for (size_t i = 0; i < sample_size; i++)
    {
        dummy_matrix.push_back(1);
    }
    Ciphertext encrypted_dummy_matrix;
    init_ciphermatrix(encr, dummy_matrix, encrypted_dummy_matrix);

    // normalize input data if its size is odd
    int normalized_data_size;
    if (data.size() % 2 == 0)
    {
        normalized_data_size = data.size();
    }
    else
    {
        normalized_data_size = data.size() + 1;
    }

    int required_range = normalized_data_size * sample_size;
    int required_no_row_elements = required_range / 2;
    int required_range_row = required_range / 2;

    // create padding matrix
    int padding_slots = (encr.bcode->slot_count() / 2) - required_range_row;
    vector<int64_t> padding_matrix(encr.bcode->slot_count(), 0ULL);
    for (size_t i = 0; i < padding_slots; i++)
    {
        padding_matrix[required_no_row_elements + i] = 1;
        padding_matrix[encr.bcode->slot_count() - i] = 1;
    }
    Ciphertext encrypted_padding_matrix;
    init_ciphermatrix(encr, padding_matrix, encrypted_padding_matrix);

    if (required_range_row <= encr.bcode->slot_count() && required_range_row > 0)
    {
        for (int index = 0; index < normalized_data_size / 2; index++)
        {
            Ciphertext ct1, ct2, ct3;
            Ciphertext temp1, temp2;
            // cout << "[INFO] loading ciphertext 1" << endl;
            load_ciphertext(eval, ct1, source);
            // cout << "[INFO] loading ciphertext 2" << endl;
            load_ciphertext(eval, ct2, data.at(index));
            sub_ciphertext(eval, ct1, ct2, temp1);

            if ((normalized_data_size / 2) + index < data.size())
            {
                // cout << "[INFO] loading ciphertext 3" << endl;
                load_ciphertext(eval, ct3, data.at((normalized_data_size / 2) + index));
                sub_ciphertext(eval, ct1, ct3, temp2);
            }
            else
            {
                // add dummy vector for oddy data
                temp2 = encrypted_dummy_matrix;
            }

            eval.eval->rotate_columns_inplace(temp2, eval.gk);
            add_ciphertext(eval, temp1, temp2, temp1);

            add_ciphertext(eval, temp1, encrypted_result_matrix, encrypted_result_matrix);

            // avoid the last shift
            if (index + 1 != (normalized_data_size / 2))
            {
                eval.eval->rotate_rows_inplace(encrypted_result_matrix, -sample_size, eval.gk);
            }
        }
        // add renmaining padding slots
        add_ciphertext(eval, encrypted_result_matrix, encrypted_padding_matrix, encrypted_result_matrix);
    }

    // // save_ciphertext(encrypted_result_matrix, result_dir + "/" + result_name + ".ct");
    // delete_operator_batching(eval);

    return encrypted_result_matrix;
    // }
}

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->sub(ct1, ct2, ct_out);
}

void sub_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2)
{
    op_st.eval->sub_inplace(ct1, ct2);
}

void sub_plain_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain)
{
    op_st.eval->sub_plain_inplace(ct, plain);
}

void negate_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct)
{
    op_st.eval->negate_inplace(ct);
}

void add_plain_inplace_ciphertext(struct evaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain)
{
    op_st.eval->add_plain_inplace(ct, plain);
}

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->add(ct1, ct2, ct_out);
}

void add_many_ciphertext(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
{
    op_st.eval->add_many(cts, ct_out);
}

void multiply_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->multiply(ct1, ct2, ct_out);
}

void multiply_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2)
{
    op_st.eval->multiply_inplace(ct1, ct2);
}

void multiply_ciphertexts(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
{
    op_st.eval->multiply_many(cts, op_st.lk, ct_out);
}

void multiply_plain_inplace(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain)
{
    op_st.eval->multiply_plain_inplace(ct, plain);
}

void relinearize_inplace(struct evaluator_t &op_st, Ciphertext &ct)
{
    op_st.eval->relinearize_inplace(ct, op_st.lk);
}

void relinearize(struct evaluator_t &op_st, Ciphertext &ct, Ciphertext &ct_out)
{
    op_st.eval->relinearize(ct, op_st.lk, ct_out);
}

void rescale_to_next_inplace(struct evaluator_t &op_st, Ciphertext &ct)
{
    op_st.eval->rescale_to_next_inplace(ct);
}

void exponentiate_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, uint64_t &exponent)
{
    op_st.eval->exponentiate_inplace(ct, exponent, op_st.lk);
}

void mod_switch_to_next_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct)
{
    op_st.eval->mod_switch_to_next_inplace(ct);
}
