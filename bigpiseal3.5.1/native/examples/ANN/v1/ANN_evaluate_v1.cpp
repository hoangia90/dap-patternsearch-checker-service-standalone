#include <iostream>
#include "csv_api.h"
#include "print_api.h"
#include "seal_api.h"
#include "util.h"

using namespace seal;
using namespace std;

void sub_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void add_ciphertext_ckks(struct cevaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void multiply_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

void multiply_ciphertext_ckks(struct cevaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out);

bool is_number(const string &s);

void printStrVector(const vector<string> &v);

vector<vector<string>> split_ends(const vector<string> &data, const vector<int> &ends);

void multiply_ciphertexts(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void multiply_ciphertexts_ckks(struct cevaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void relinearize_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void relinearize_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct);

void rescale_to_next_inplace(struct evaluator_t &op_st, Ciphertext &ct);

void rescale_to_next_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct);

void multiply_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void relinearize(struct evaluator_t &op_st, Ciphertext &ct, Ciphertext &ct_out);

void sub_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2);

void negate_inplace__ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

void add_plain_inplace_ciphertext(struct evaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain);

void add_plain_inplace_ciphertext_ckks(struct cevaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain);

void add_plain_ckks(struct cevaluator_t &op_st, Ciphertext &ct, Plaintext &plain, Ciphertext &ct_out);

void multiply_plain_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void multiply_plain_ckks(struct cevaluator_t &op_st, Ciphertext &ct, const Plaintext &plain, Ciphertext &out);

void add_many_ciphertext(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void add_many_ciphertext_ckks(struct cevaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out);

void exponentiate_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, uint64_t &exponent);

void sub_plain_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain);

void mod_switch_to_next_inplace_ciphertext(struct evaluator_t &op_st, Ciphertext &ct);

void mod_switch_to_next_inplace_ciphertext_ckks(struct cevaluator_t &op_st, Plaintext &plain);

void mod_switch_to_inplace_ckks(struct cevaluator_t &op_st, Plaintext &plain, parms_id_type &parms_id);

void mod_switch_to_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct, parms_id_type &parms_id);

int ANNProcess(
    vector<string> &wFilePaths, string &xCT, vector<string> &bFilePaths, string &result_name, string &result_dir,
    int &sample_size, string &key_dir);

int main(int argc, char **argv)
{
    string wFilePath = argv[1];
    string wFilePath2 = argv[2];
    string wFilePath3 = argv[3];
    string wFilePath4 = argv[4];

    string xCT = argv[5];

    string bFilePath = argv[6];
    string bFilePath2 = argv[7];
    string bFilePath3 = argv[8];
    string bFilePath4 = argv[9];

    string result_name = argv[argc - 4];
    string result_dir = argv[argc - 3];
    int sample_size = atoi(argv[argc - 2]);
    string key_dir = argv[argc - 1];

    // Midify and improve later
    vector<string> wFilePaths;
    wFilePaths.push_back(wFilePath);
    wFilePaths.push_back(wFilePath2);
    wFilePaths.push_back(wFilePath3);
    wFilePaths.push_back(wFilePath4);
    // Midify and improve later
    vector<string> bFilePaths;
    bFilePaths.push_back(bFilePath);
    bFilePaths.push_back(bFilePath2);
    bFilePaths.push_back(bFilePath3);
    bFilePaths.push_back(bFilePath4);

    if (xCT == "" || result_name == "" || result_dir == "" || sample_size == 0 || key_dir == "")
    {
        // error handling
        cout << "[ERROR] please enter a source path, data paths, output ciphertext file name or prefix, output "
                "ciphertext directory, sample size, linking key path, galois key path and public key path"
             << endl;
        return -1;
    }

    int result = 0;
    result = ANNProcess(wFilePaths, xCT, bFilePaths, result_name, result_dir, sample_size, key_dir);

    // error handling
    if (result == -1)
    {
        fprintf(stderr, "error!\n");
    }
    else
    {
        std::cout << "done";
    }

    return result;
}

void rotate_2d_matrix_clockwise_impl(
    vector<vector<double>> const &matrix, vector<vector<double>> &rotated_matrix, int const M, int const N)
{
    for (int x = 0; x < N; ++x)
    {
        for (int y = 0; y < M; ++y)
        {
            // cout << "[ANN Engine] ..... "  << matrix[x][y] << endl;
            // Source : https://stackoverflow.com/questions/4780119/2d-euclidean-vector-rotations
            rotated_matrix[y][-x - 1 + N] = matrix[x][y];
        }
    }
}

auto rotate_2d_matrix_clockwise(vector<vector<double>> const &original_matrix) -> vector<vector<double>>
{
    int const M = original_matrix[0].size();
    int const N = original_matrix.size();
    vector<vector<double>> rotated_matrix;
    rotated_matrix.resize(M);
    for (auto x = 0; x < M; ++x)
    {
        rotated_matrix[x].resize(N);
    }
    rotate_2d_matrix_clockwise_impl(original_matrix, rotated_matrix, M, N);
    return rotated_matrix;
}

vector<vector<double>> load_matrix_and_rotate_clockwise(string &original_matrix, int n)
{
    // cout << "[ANN Engine] loading matrix w " << original_matrix << "..... " << endl;
    vector<vector<double>> w;
    load_csv_file(original_matrix, w, 0);
    // cout << "[ANN Engine] loading matrix w ..... end \n" << endl;

    // cout << "[ANN Engine] rotating matrix w ..... " << endl;
    for (int i = 0; i < n; i++)
    {
        w = rotate_2d_matrix_clockwise(w);
    }
    // cout << "[ANN Engine] rotating matrix w ..... end \n" << endl;

    // cout << "[ANN Engine] printing rotated matrix w ..... " << endl;
    // print_matrix(w);
    // cout << "[ANN Engine] printing rotated matrix w ..... end \n" << endl;

    return w;
}

Ciphertext getIndexVector(cencryptor_t &encr, cevaluator_t &eval, Ciphertext vector_ct, int slot_count, int index)
{
    // std::cout << "[ANN Engine] Error 1 ..... \n" << endl;
    vector<double> index_vector(encr.ccode->slot_count(), 0ULL);
    index_vector[index - 1] = 1ULL;

    Plaintext index_vector_pt;
    init_plaintext_ckks(encr, index_vector, index_vector_pt);

    // std::cout << "[ANN Engine] Error 2 ..... \n" << endl;

    Ciphertext v_ct = vector_ct;

    // std::cout << "[ANN Engine] Error 3 ..... \n" << endl;

    parms_id_type last_parms_id2 = v_ct.parms_id();
    mod_switch_to_inplace_ckks(eval, index_vector_pt, last_parms_id2);

    // std::cout << "[ANN Engine] Computing v_ct (add_ciphertext_ckks)..... " << endl;
    // cout << "    + Scale of v_ct: " << log2(v_ct.scale()) << " bits" << endl;
    // cout << "    + Modulus chain index for v_ct: " << eval.context->get_context_data(v_ct.parms_id())->chain_index()
    //      << endl;

    // cout << "    + Scale of index_vector_pt: " << log2(index_vector_pt.scale()) << " bits" << endl;
    // cout << "    + Modulus chain index for index_vector_pt: "
    //      << eval.context->get_context_data(index_vector_pt.parms_id())->chain_index() << endl;

    multiply_plain_inplace_ckks(eval, v_ct, index_vector_pt);
    relinearize_inplace_ckks(eval, v_ct);
    rescale_to_next_inplace_ckks(eval, v_ct);

    eval.eval->rotate_vector(v_ct, -(slot_count - index), eval.gk, v_ct);

    Ciphertext result = v_ct;

    // std::cout << "[ANN Engine] Error 4 ..... \n" << endl;

    for (size_t i = 0; i < slot_count; i++)
    {
        // std::cout << "[ANN Engine] Error 5 ..... \n" << endl;

        eval.eval->rotate_vector_inplace(result, 1, eval.gk);
        // eval.eval->rotate_vector(result, 1, eval.gk, result);

        // std::cout << "[ANN Engine] Error 6 ..... \n" << endl;

        // std::cout << "[ANN Engine] Computing v_ct (add_ciphertext_ckks)..... " << endl;
        // cout << "    + Scale of v_ct: " << log2(v_ct.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for v_ct: " <<
        // eval.context->get_context_data(v_ct.parms_id())->chain_index()
        //      << endl;

        // cout << "    + Scale of result: " << log2(result.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for result: "
        //      << eval.context->get_context_data(result.parms_id())->chain_index() << endl;

        add_ciphertext_ckks(eval, v_ct, result, result);

        // std::cout << "[ANN Engine] Error 7 ..... \n" << endl;
    }
    return result;
}

Ciphertext action_compute(
    cencryptor_t &encr, cevaluator_t &eval, string &wFilePath, Ciphertext &x, string &bFilePath, int sample_size)
{
    vector<vector<double>> cw;
    cw = load_matrix_and_rotate_clockwise(wFilePath, 3);

    // Transform into vector<Plaintext>
    // std::cout << "[ANN Engine] Transform into vector<Plaintext> cw_pt ..... \n" << endl;
    vector<Plaintext> cw_pt;
    for (int i = 0; i < cw.size(); i++)
    {
        Plaintext temp_pt;
        init_plaintext_ckks(encr, cw[i], temp_pt);
        cw_pt.push_back(temp_pt);
    }
    // std::cout << "[ANN Engine] Transform into vector<Plaintext> cw_pt ..... end \n" << endl;

    // cout << "[ANN Engine] loading vector b " << bFilePath << "..... " << endl;
    vector<vector<double>> b;
    load_csv_file(bFilePath, b, 0);

    Plaintext b_pt;

    init_plaintext_ckks(encr, b[0], b_pt);

    // cout << "[ANN Engine] loading vector b ..... end \n" << endl;

    std::cout << "[ANN Engine] Computing wxb_ct ..... " << endl;
    vector<Ciphertext> wxb_ct;

    Ciphertext index_vector;

    // std::cout << "[ANN Engine] Computing wxb_ct (multiply_plain_inplace_ckks)..... " << endl;
    for (int i = 0; i < cw_pt.size(); i++)
    {
        Ciphertext x_ct = x;
        Plaintext pt;

        // std::cout << "[ANN Engine] Computing wxb_ct (add_ciphertext_ckks)..... " << endl;
        // cout << "    + Scale of x_ct: " << log2(x_ct.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for x_ct: " <<
        // eval.context->get_context_data(x_ct.parms_id())->chain_index()
        //      << endl;

        // cout << "    + Scale of cw_pt[i]: " << log2(cw_pt[i].scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for cw_pt[i]: "
        //      << eval.context->get_context_data(cw_pt[i].parms_id())->chain_index() << endl;

        // std::cout << "[ANN Engine] Error 1..... " << endl;
        parms_id_type last_parms_id2 = x_ct.parms_id();
        mod_switch_to_inplace_ckks(eval, cw_pt[i], last_parms_id2);

        // index_vector = getIndexVector(encr, eval, x_ct, 3, 1);
        index_vector = getIndexVector(encr, eval, x_ct, sample_size, sample_size - i);

        // std::cout << "[ANN Engine] Error 1.1..... " << endl;

        parms_id_type last_parms_id3 = x_ct.parms_id();
        mod_switch_to_inplace_ckks(eval, cw_pt[i], last_parms_id3);

        // Ciphertext b = getIndexVector(encr, eval, a, 3, 1);
        // std::cout << "[ANN Engine] Error 2..... " << endl;

        // std::cout << "[ANN Engine] Computing wxb_ct (add_ciphertext_ckks)..... " << endl;
        // cout << "    + Scale of x_ct: " << log2(x_ct.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for x_ct: " <<
        // eval.context->get_context_data(x_ct.parms_id())->chain_index()
        //      << endl;

        // cout << "    + Scale of cw_pt[i]: " << log2(cw_pt[i].scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for cw_pt[i]: "
        //      << eval.context->get_context_data(cw_pt[i].parms_id())->chain_index() << endl;

        // x_ct = getIndexVector(encr, eval, x_ct, 3, 1);

        // multiply_plain_inplace_ckks(eval, x_ct, cw_pt[i]);
        // std::cout << "[ANN Engine] Error 3..... " << endl;
        // std::cout << "[ANN Engine] Error 2..... " << endl;

        // std::cout << "[ANN Engine] Computing wxb_ct (add_ciphertext_ckks)..... " << endl;
        // cout << "    + Scale of index_vector: " << log2(index_vector.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for index_vector: "
        //      << eval.context->get_context_data(index_vector.parms_id())->chain_index() << endl;

        // cout << "    + Scale of cw_pt[i]: " << log2(cw_pt[i].scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for cw_pt[i]: "
        //      << eval.context->get_context_data(cw_pt[i].parms_id())->chain_index() << endl;

        parms_id_type last_parms_id4 = index_vector.parms_id();
        mod_switch_to_inplace_ckks(eval, cw_pt[i], last_parms_id4);
        // cw_pt[i].scale() = pow(2.0, 40);
        // index_vector.scale() = pow(2.0, 40);

        multiply_plain_ckks(eval, index_vector, cw_pt[i], x_ct);

        // std::cout << "[ANN Engine] Computing wxb_ct (add_ciphertext_ckks)..... " << endl;
        // cout << "    + Scale of x_ct: " << log2(x_ct.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for x_ct: " <<
        // eval.context->get_context_data(x_ct.parms_id())->chain_index()
        //      << endl;

        // cout << "    + Scale of b_pt: " << log2(b_pt.scale()) << " bits" << endl;
        // cout << "    + Modulus chain index for b_pt: " <<
        // eval.context->get_context_data(b_pt.parms_id())->chain_index()
        //      << endl;

        relinearize_inplace_ckks(eval, x_ct);
        rescale_to_next_inplace_ckks(eval, x_ct);
        // rescale b_pt
        parms_id_type last_parms_id = x_ct.parms_id();
        mod_switch_to_inplace_ckks(eval, b_pt, last_parms_id);
        // more solution
        // cout << "    + Exact scale 1 in x_ct: " << x_ct.scale() << endl;
        // cout << "    + Exact scale 1 in b_pt: " << b_pt.scale() << endl;
        // cout << "    + Exact scale 1 in b_ct: " << b_ct.scale() << endl;
        x_ct.scale() = pow(2.0, 40);
        b_pt.scale() = pow(2.0, 40);
        // cout << "    + Exact scale 2 in x_ct: " << x_ct.scale() << endl;
        // cout << "    + Exact scale 2 in b_pt: " << b_pt.scale() << endl;

        wxb_ct.push_back(x_ct);
    }
    Ciphertext a;
    // std::cout << "[ANN Engine] Computing wxb_ct (add_many_ciphertext_ckks)..... " << endl;
    add_many_ciphertext_ckks(eval, wxb_ct, a);

    add_plain_inplace_ciphertext_ckks(eval, a, b_pt);
    //  add_ciphertext_ckks(eval, ct, b_ct, ct);
    // rescale_to_next_inplace_ckks(eval, ct);

    std::cout << "[ANN Engine] Computing wxb_ct ..... end" << endl;
    return a;
}

int ANNProcess(
    vector<string> &wFilePaths, string &xCT, vector<string> &bFilePaths, string &result_name, string &result_dir,
    int &sample_size, string &key_dir)
{
    // This should be revised and improved!
    struct cevaluator_t eval;
    init_operator_ckks(eval, key_dir);
    struct cencryptor_t encr;
    init_operator_ckks(encr, key_dir);

    int slot_count = encr.ccode->slot_count();
    std::cout << slot_count << endl;

    // cout << "[ANN Engine] loading vector x " << xCT << "..... " << endl;
    Ciphertext a; // x
    load_ciphertext_ckks(eval, a, xCT);
    // cout << "[ANN Engine] loading vector x ..... end \n" << endl;

    // for (size_t i = 0; i < wFilePaths.size(); i++)
    for (size_t i = 0; i < 3; i++)
    {
        /* code */
        cout << "[ANN Engine] compute a" << i + 1 << " ....." << endl;
        a = action_compute(encr, eval, wFilePaths[i], a, bFilePaths[i], sample_size);
        cout << "[ANN Engine] compute a" << i + 1 << " ..... end \n" << endl;
    }

    // getIndexVector(encr, eval, a, slot_count, 3);

    // Ciphertext b = getIndexVector(encr, eval, a, 3, 1);
    // index_vector = getIndexVector(encr, eval, x_ct, 3, 3);

    save_ciphertext(a, result_dir + "/" + result_name + ".ct");
    delete_operator_ckks(encr);
    delete_operator_ckks(eval);

    return 0;
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

void add_plain_inplace_ciphertext_ckks(struct cevaluator_t &op_st, struct Ciphertext &ct, const Plaintext &plain)
{
    op_st.eval->add_plain_inplace(ct, plain);
}

void add_plain_ckks(struct cevaluator_t &op_st, Ciphertext &ct, Plaintext &plain, Ciphertext &ct_out)
{
    op_st.eval->add_plain(ct, plain, ct_out);
}

void add_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->add(ct1, ct2, ct_out);
}

void add_ciphertext_ckks(struct cevaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->add(ct1, ct2, ct_out);
}

void add_many_ciphertext_ckks(struct cevaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
{
    op_st.eval->add_many(cts, ct_out);
}

void add_many_ciphertext(struct evaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
{
    op_st.eval->add_many(cts, ct_out);
}

// void add_many_ciphertext_ckks(struct cevaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
// {
//     op_st.eval->add_many(cts, ct_out);
// }

void multiply_ciphertext(struct evaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
{
    op_st.eval->multiply(ct1, ct2, ct_out);
}

void multiply_ciphertext_ckks(struct cevaluator_t &op_st, Ciphertext &ct1, Ciphertext &ct2, Ciphertext &ct_out)
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

void multiply_ciphertexts_ckks(struct cevaluator_t &op_st, vector<Ciphertext> &cts, Ciphertext &ct_out)
{
    op_st.eval->multiply_many(cts, op_st.lk, ct_out);
}

void multiply_plain_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct, const Plaintext &plain)
{
    op_st.eval->multiply_plain_inplace(ct, plain);
}

void multiply_plain_ckks(struct cevaluator_t &op_st, Ciphertext &ct, const Plaintext &plain, Ciphertext &out)
{
    op_st.eval->multiply_plain(ct, plain, out);
}

// void multiply_plain_inplace_ckks(struct evaluator_t &op_st, Ciphertext &ct, const Plaintext &plain)
// {
//     op_st.eval->multiply_plain_inplace(ct, plain);
// }

void relinearize_inplace(struct evaluator_t &op_st, Ciphertext &ct)
{
    op_st.eval->relinearize_inplace(ct, op_st.lk);
}

void relinearize_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct)
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

void rescale_to_next_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct)
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

void mod_switch_to_inplace_ckks(struct cevaluator_t &op_st, Plaintext &plain, parms_id_type &parms_id)
{
    op_st.eval->mod_switch_to_inplace(plain, parms_id);
}

void mod_switch_to_inplace_ckks(struct cevaluator_t &op_st, Ciphertext &ct, parms_id_type &parms_id)
{
    op_st.eval->mod_switch_to_inplace(ct, parms_id);
}

void mod_switch_to_next_inplace_ciphertext_ckks(struct cevaluator_t &op_st, Plaintext &plain)
{
    op_st.eval->mod_switch_to_next_inplace(plain);
}

// mod_switch_drop_to_next