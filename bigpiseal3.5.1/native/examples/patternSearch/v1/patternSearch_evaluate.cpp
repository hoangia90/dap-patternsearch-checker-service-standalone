#include "seal_api.h"
#include "util.h"

#include <iostream>
// #include <algorithm>
// #include <iterator>
// #include <vector>
// #include <filesystem>


using namespace seal;

std::string relink_key_path;

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void multiply_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void isContain(std::vector<std::vector<std::string>> &v_v, std::string &result_name, std::string &result_dir, std::string &relink_key_path);

bool is_number(const std::string &s);

void printStrVector(const std::vector<std::string> &v);

std::vector<std::vector<std::string>> split_ends(const std::vector<std::string> &source, const std::vector<int> &ends);

void multiply_ciphertexts(struct evaluator_t &op_st, std::vector<Ciphertext> &cts, Ciphertext &ct_out);

void relinearize_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void rescale_to_next_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void multiply_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void relinearize(struct evaluator_t &op_st, Ciphertext &ct,  Ciphertext &ct_out);

void sub_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void negate_inplace__ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

void add_plain_inplace_ciphertext(struct evaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain);

void multiply_plain_inplace(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void add_many_ciphertext(struct evaluator_t &op_st, std::vector<Ciphertext> &cts, Ciphertext &ct_out);

void exponentiate_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, uint64_t &exponent);

void sub_plain_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void mod_switch_to_next_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

// void sub_vector(std::string &ciphertext_name2, std::string &ciphertext_dir2, std::string &result_name, std::string &result_dir);

// void sub_vectors(std::string &parent_dir, std::string &result_name, std::string &result_dir);

int main(int argc, char **argv)
{
    // if (argc != 7)
    // std::cout << "[ERROR] please enter prefix_file_to_decrypt_1 /full/path/to/storage_1 "
    //              "/full/path/to/parent prefix_result_file /full/path/to/result_storage full/path/to/relink/key"
    //           << std::endl;
    // cout << "[ERROR] please enter prefix_file_to_decrypt_1 /full/path/to/storage_1 prefix_file_to_decrypt_2 "
    //         "/full/path/to/storage_2 prefix_result_file /full/path/to/result_storage full/path/to/relink/key"
    //      << endl;
    // cout << "[ERROR] please enter name and directory of 1st ciphertexts, name and directory of 2nd ciphertexts, name
    // and directory of result ciphertexts, and relink key path" << endl;
    // else

    std::string ciphertext_name1 = argv[1];
    // ciphertext_dir1 = argv[2];

    std::string result_name = argv[argc - 3];
    std::string result_dir = argv[argc - 2];

    relink_key_path = argv[argc - 1];

    std::vector<std::string> source;
    // std::vector<int> ends;
    std::vector<std::vector<std::string>> v_v;

    for (int i = 2; i < argc - 3; i++)
    {
        if (is_number(argv[i]))
        {
            // ends.push_back(std::stoi( argv[i]) );
            int len = std::stoi( argv[i]);
            std::vector<std::string> source;
            for (int i2 = 1; i2 <= len; i2++)
            {
                source.push_back(argv[i + i2]);
            }

            v_v.push_back(source);

        }
        // else 
        // {
        //     source.push_back(argv[i]);
        //     std::cout << "[ERROR]" << argv[i] << std::endl;
        // }
    }


    // auto splitted = split_ends(source, ends);
    // for (const auto& v: v_v) {
    //     printStrVector(v);
    //     // std::cout << '\n';
    // }


    isContain(v_v, result_name, result_dir, relink_key_path);

    std::cout << "done" << std::endl;

    return 1;
}

void isContain(std::vector<std::vector<std::string>> &v_v, std::string &result_name, std::string &result_dir, std::string &relink_key_path)
{

    struct evaluator_t eval;
    // init_operator(8192, 4294967296, eval, relink_key_path);
    init_operator(eval, relink_key_path);

    Ciphertext result;

    std::vector<Ciphertext> cts;

    // std::cout << v_v.size() -1 << std::endl;
    
    for (int index = 1; index < v_v.size(); index++)
    {
        Ciphertext ct3;
        int noFiles1 = v_v.at(0).size();
        int noFiles2 = v_v.at(index).size();
        // std::cout << noFiles1 -1 << std::endl;
        if (noFiles1 == noFiles2)
        {   
            std::vector<Ciphertext> cts2;
            for (int index2 = 0; index2 < noFiles1; index2++)
            {
                Ciphertext ct1, ct2;
                Ciphertext temp;
                // std::cout << "[INFO] loading ciphertext 1" << std::endl;
                load_ciphertext(eval, ct1, v_v.at(0).at(index2));
                // std::cout << "[INFO] loading ciphertext 2" << std::endl;
                load_ciphertext(eval, ct2, v_v.at(index).at(index2));
                // std::cout << "[INFO] subtracting ciphertext 2 from ciphertext 1" << std::endl;
                sub_ciphertext(eval, ct1, ct2, temp);

                // u_int64_t x = 2;
                // exponentiate_inplace_ciphertext(eval, temp, x);

                cts2.push_back(temp);
                
                
            }

            add_many_ciphertext(eval, cts2, ct3);
            relinearize_inplace(eval, ct3);
            
        }
        else
        {
            // number of files is different in 2 directories
        }

        cts.push_back(ct3);

        // if(index == 1)
        // {
        //     result = ct3;
        // }
        // else
        // {
        //     multiply_inplace_ciphertext(eval, result, ct3);
        //     relinearize_inplace(eval, result);
        //     mod_switch_to_next_inplace_ciphertext(eval, result);
        // }
    }

    multiply_ciphertexts(eval, cts, result);
    // mod_switch_to_next_inplace_ciphertext(eval, result);
    

    save_ciphertext(result, result_dir + "/" + result_name + ".ct");
    delete_operator(eval);
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

void add_many_ciphertext(struct evaluator_t &op_st, std::vector<Ciphertext> &cts, Ciphertext &ct_out)
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

void multiply_ciphertexts(struct evaluator_t &op_st, std::vector<Ciphertext> &cts, Ciphertext &ct_out)
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

void relinearize(struct evaluator_t &op_st, Ciphertext &ct,  Ciphertext &ct_out)
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




// // void isContain(std::string &parent_dir, std::string &result_name, std::string &result_dir)
// void isContain(std::string *dirs, int &len, std::string &result_name, std::string &result_dir)
// {
//     struct evaluator_t eval;

//     // init_operator(2048, 256, eval, relink_key_path);
//     init_operator(8192, 4294967296, eval, relink_key_path);

//     Ciphertext ct1, ct2, ct3, result;

//     // std::cout << "[ERROR]" << std::endl;
//     for (int index = 0; index < len; index++)
//     {
//         // std::cout << "[ERROR]" << dirs[index] << std::endl;

//         std::string ciphertext_dir2 = dirs[index];

//         // std::cout << ciphertext_dir2 << std::endl;

//         int noFiles1 = findNumberOfFilesInDirectory(ciphertext_dir1);
//         int noFiles2 = findNumberOfFilesInDirectory(ciphertext_dir2);

//         if (noFiles1 == noFiles2)
//         {
//             for (int index2 = 0; index2 < noFiles1; index2++)
//             {
//                 // std::cout << "[INFO] loading ciphertext 1" << std::endl;
//                 // load_ciphertext(eval, ct1, ciphertext_dir1 + "/" + ciphertext_name1 + "_" + std::to_string(index) +
//                 // ".ct");
//                 load_ciphertext(eval, ct1, ciphertext_dir1 + ciphertext_name1 + "_" + std::to_string(index2) + ".ct");
//                 // std::cout << "[INFO] loading ciphertext 2" << std::endl;
//                 // load_ciphertext(eval, ct2, ciphertext_dir2 + "/" + ciphertext_name1 + "_" + std::to_string(index) +
//                 // ".ct");
//                 load_ciphertext(eval, ct2, ciphertext_dir2 + ciphertext_name1 + "_" + std::to_string(index2) + ".ct");
//                 // std::cout << "[INFO] subtracting ciphertext 2 from ciphertext 1" << std::endl;
//                 sub_ciphertext(eval, ct1, ct2, ct1);

//                 if (index2 == 0)
//                 {
//                     ct3 = ct1;
//                 }
//                 else
//                 {
//                     add_ciphertext(eval, ct3, ct1, ct3);
//                 }
//             }
//         }
//         else
//         {
//             // number of files is different in 2 directories
//         }

//         if (index == 0)
//         {
//             result = ct3;
//         }
//         else
//         {
//             multiply_ciphertext(eval, result, ct3, ct3);
//         }
//     }

//     save_ciphertext(ct3, result_dir + "/" + result_name + ".ct");

//     delete_operator(eval);
// }

// // Used for dynamic search
// void sub_vectors(std::string &ciphertext_name1, std::string &ciphertext_dir1, std::string &parent_dir, std::string &result_name, std::string &result_dir, std::string &relink_key_path)
// {
//     std::vector<std::string> directories = get_directories(parent_dir);

//     // for (const auto &entry : std::filesystem::directory_iterator(path))
//     for (const auto &entry : directories)
//     {
//         // std::cout << entry << std::endl;

//         std::string ciphertext_dir2 = entry + "/";

//         std::string result_dir2 = result_dir + ciphertext_dir2;

//         // std::cout << result_dir2 << std::endl;

//         // std::cout << ciphertext_dir2 << std::endl;

//         std::filesystem::create_directories(result_dir2);

//         sub_vector(ciphertext_name1, ciphertext_dir2, result_name, result_dir2);

//         // file reduction
//         // std::cout << "[INFO] file reduction!!!" << std::endl;
//         struct evaluator_t eval;
//         init_operator(2048, 256, eval, relink_key_path);
//         Ciphertext ct1, ct2, ct3;
//         int noFiles = findNumberOfFilesInDirectory(result_dir2);
//         for (int index = 1; index < noFiles; index++)
//         {
//             // std::cout << "[INFO] loading ciphertext 1" << std::endl;
//             load_ciphertext(eval, ct1, result_dir2 + result_name + "_" + "0" + ".ct");
//             // std::cout << "[INFO] loading ciphertext 2" << std::endl;
//             load_ciphertext(eval, ct2, result_dir2 + result_name + "_" + std::to_string(index) + ".ct");
//             // std::cout << "[INFO] addition ciphertext 1 with ciphertext 2" << std::endl;
//             add_ciphertext(eval, ct1, ct2, ct1);
//             // std::cout << "[INFO] saving ciphertext addition to a new ciphertext file" << std::endl;
//             save_ciphertext(ct1, result_dir2 + result_name + "_" + "0" + ".ct");
//             std::filesystem::remove(result_dir2 + result_name + "_" + std::to_string(index) + ".ct");
//         }
//     }
// }

// // Used for dynamic search
// void sub_vector(std::string &ciphertext_name1, std::string &ciphertext_dir1, std::string &ciphertext_name2, std::string &ciphertext_dir2, std::string &result_name, std::string &result_dir, std::string &relink_key_path)
// {
//     struct evaluator_t eval;

//     int noFiles1 = findNumberOfFilesInDirectory(ciphertext_dir1);
//     int noFiles2 = findNumberOfFilesInDirectory(ciphertext_dir2);

//     // init_operator(2048, 256, eval);
//     init_operator(2048, 256, eval, relink_key_path);

//     Ciphertext ct1, ct2, ct3;

//     if (noFiles1 == noFiles2)
//     {
//         for (int index = 0; index < noFiles1; index++)
//         {
//             // std::cout << "[INFO] loading ciphertext 1" << std::endl;
//             load_ciphertext(eval, ct1, ciphertext_dir1 + "/" + ciphertext_name1 + "_" + std::to_string(index) + ".ct");
//             // std::cout << "[INFO] loading ciphertext 2" << std::endl;
//             load_ciphertext(eval, ct2, ciphertext_dir2 + "/" + ciphertext_name2 + "_" + std::to_string(index) + ".ct");
//             // std::cout << "[INFO] subtracting ciphertext 2 from ciphertext 1" << std::endl;
//             sub_ciphertext(eval, ct1, ct2, ct3);
//             // std::cout << "[INFO] saving ciphertext subtraction to a new ciphertext file" << std::endl;
//             save_ciphertext(ct3, result_dir + "/" + result_name + "_" + std::to_string(index) + ".ct");
//         }
//     }
//     else
//     {}
//     delete_operator(eval);
// }


// Input processing

bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// C++11 
// bool is_number(const std::string& s)
// {
//     return !s.empty() && std::find_if(s.begin(), 
//         s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
// }

// std::vector<std::vector<std::string>> split_ends(const std::vector<std::string> &source, const std::vector<int> &ends) 
// {
//     std::vector<std::vector<std::string>> result;
//     result.reserve(ends.size());
//     auto anchor_front = source.begin();
//     for (auto one_end: ends) 
//     {
//         auto anchor_end = std::next(source.begin(), one_end + 1);
//         result.emplace_back(anchor_front, anchor_end);
//         anchor_front = anchor_end;
//     }
//     return result;
// }

// void printStrVector(const std::vector<std::string>& v)
// {
//     for (auto x: v) 
//     {
//         std::cout << x << ' ';
//     }
// }