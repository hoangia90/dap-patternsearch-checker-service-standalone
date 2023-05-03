#include "seal_api.h"

/* namespaces */
using namespace std;
using namespace seal;

/* functions */
int open_binary_file(ifstream &in_file, const string &filename)
{
    int ret = 1;
    in_file = ifstream(filename, ios::binary);
    if (!in_file)
    {
        // cerr << "[ERRROR] file opening failure" << endl;
        ret = 0;
    }

    return ret;
}

int open_binary_file(ofstream &out_file, const string &filename)
{
    int ret = 1;
    out_file = ofstream(filename, ios::binary);
    if (!out_file)
    {
        // cerr << "[ERRROR] file opening failure" << endl;
        ret = 0;
    }

    return ret;
}

int save_params(EncryptionParameters &params, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        params.save(out_file);
    else
        ret = 0;
    return ret;
}

int load_params(EncryptionParameters &params, const string &filename)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        params.load(in_file);
    else
        ret = 0;
    return ret;
}

void init_context(size_t poly_d, size_t p_modulus, shared_ptr<SEALContext> &context)
{
    EncryptionParameters params(scheme_type::BFV);
    params.set_poly_modulus_degree(poly_d);
    params.set_coeff_modulus(CoeffModulus::BFVDefault(poly_d));
    params.set_plain_modulus(p_modulus);

    save_params(params, "bfv_params.conf");

    context = SEALContext::Create(params);
    print_context(context);
}

void init_context_batching(size_t poly_d, int bit_size, shared_ptr<SEALContext> &context, const std::string &key_dir)
{
    EncryptionParameters params(scheme_type::BFV);
    params.set_poly_modulus_degree(poly_d);
    params.set_coeff_modulus(CoeffModulus::BFVDefault(poly_d));
    params.set_plain_modulus(PlainModulus::Batching(poly_d, bit_size));
    save_params(params, key_dir + "bfv_params.conf");
    context = SEALContext::Create(params);
    print_context(context);
}

// void ckks_init_context_batching(
//     size_t poly_d, int bit_size, shared_ptr<SEALContext> &context, const std::string &key_dir)
// {
//     EncryptionParameters params(scheme_type::CKKS);
//     params.set_poly_modulus_degree(poly_d);
//     params.set_coeff_modulus(CoeffModulus::BFVDefault(poly_d));
//     params.set_plain_modulus(PlainModulus::Batching(poly_d, bit_size));
//     save_params(params, key_dir + "bfv_params.conf");
//     context = SEALContext::Create(params);
//     print_context(context);
// }

void init_context_batching(
    size_t poly_d, vector<int> bit_sizes, std::uint64_t plain_modulus, shared_ptr<SEALContext> &context,
    const std::string &key_dir)
{
    EncryptionParameters params(scheme_type::BFV);
    params.set_poly_modulus_degree(poly_d);
    params.set_coeff_modulus(CoeffModulus::Create(poly_d, { 36, 36, 37 }));
    params.set_plain_modulus(plain_modulus);
    save_params(params, key_dir + "bfv_params.conf");
    context = SEALContext::Create(params);
    print_context(context);
}

// void ckks_init_context_batching(
//     size_t poly_d, vector<int> bit_sizes, std::uint64_t plain_modulus, shared_ptr<SEALContext> &context,
//     const std::string &key_dir)
// {
//     EncryptionParameters params(scheme_type::CKKS);
//     params.set_poly_modulus_degree(poly_d);
//     params.set_coeff_modulus(CoeffModulus::Create(poly_d, { 36, 36, 37 }));
//     params.set_plain_modulus(plain_modulus);
//     save_params(params, key_dir + "ckks_params.conf");
//     context = SEALContext::Create(params);
//     print_context(context);
// }

// void init_context_ckks(size_t poly_d, std::uint64_t plain_modulus, shared_ptr<SEALContext> &context,
//     const std::string &key_dir)
// {
//     int ret = 1;

//     EncryptionParameters params(scheme_type::CKKS);
//     params.set_poly_modulus_degree(poly_d);
//     switch (poly_d)
//     {
//     case 4096:
//         params.set_coeff_modulus(CoeffModulus::Create(poly_d, { 30, 20, 20, 30 }));
//         break;
//     case 8192:
//         params.set_coeff_modulus(CoeffModulus::Create(poly_d, { 60, 40, 40, 60 }));
//         break;
//     default:
//         cout << "[seal-error] enter valid poly degree: 4096 or 8192" << endl;
//         break;
//     }
//     // params.set_plain_modulus(plain_modulus);
//     save_params(params, key_dir + "ckks_params.conf");

//     context = SEALContext::Create(params);
//     print_context(context);

//     // context = SEALContext(params);
//     // if (context.parameter_error_message() == "valid")
//     // {
//     //     clog << "[seal-ckks] parameter validation: valid" << endl;
//     //     save_params(params, "ckks_params.conf");
//     // }
//     // else
//     // {
//     //     clog << "[seal-error] parameter validation: invalid" << endl;
//     //     ret = 0;
//     // }
//     // return ret;
// }

// int init_context_ckks(uint32_t poly_deg, SEALContext& context)
int init_context_ckks(uint32_t poly_deg, shared_ptr<SEALContext> &context, const std::string &key_dir)
{
    int ret = 1;

    EncryptionParameters params(scheme_type::CKKS);
    params.set_poly_modulus_degree(poly_deg);
    switch (poly_deg)
    {
    case 4096:
        params.set_coeff_modulus(CoeffModulus::Create(poly_deg, { 30, 20, 20, 30 }));
        break;
    case 8192:
        params.set_coeff_modulus(CoeffModulus::Create(poly_deg, { 60, 40, 40, 60 }));
        break;
    case 16384:
        params.set_coeff_modulus(CoeffModulus::Create(poly_deg, { 60, 40, 40, 40, 40, 40, 40, 40, 60 }));
        // params.set_coeff_modulus(CoeffModulus::Create(poly_deg, { 40, 40, 40, 40, 40, 40, 40, 40, 40, 40 }));
        // params.set_coeff_modulus(CoeffModulus::Create(poly_deg, { 30, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 30 }));
        break;
    default:
        cout << "[seal-error] enter valid poly degree: 4096 or 8192" << endl;
        break;
    }

    context = SEALContext::Create(params);
    //   if (context.parameter_error_message() == "valid") {
    //     clog << "[seal-ckks] parameter validation: valid" << endl;
    save_params(params, key_dir + "ckks_params.conf");
    //   }
    //   else {
    //     clog << "[seal-error] parameter validation: invalid" << endl;
    //     ret = 0;
    //   }
    print_context(context);
    return ret;
}

void load_context(shared_ptr<SEALContext> &context, const string &filename)
{
    EncryptionParameters params;
    load_params(params, filename);
    context = SEALContext::Create(params);
    print_context(context);
}

/* print paramaeters function from examples.h */
void print_context(shared_ptr<SEALContext> &context)
{
    if (!context)
        throw invalid_argument("[ERROR] context is not set");

    auto &context_data = *context->key_context_data();
    /* which scheme is used */
    string scheme_name;
    switch (context_data.parms().scheme())
    {
    case seal::scheme_type::BFV:
        scheme_name = "BFV";
        break;
    case seal::scheme_type::CKKS:
        scheme_name = "CKKS";
        break;
    default:
        throw invalid_argument("[ERROR] unsupported scheme");
    }

    cout << "[CONTEXT] scheme: " << scheme_name << endl;
    cout << "[CONTEXT] poly_modulus_degree: " << context_data.parms().poly_modulus_degree() << endl;

    // /* Print the size of the true (product) coefficient modulus */
    cout << "[CONTEXT] coeff_modulus size: ";
    cout << context_data.total_coeff_modulus_bit_count() << " (";
    auto coeff_modulus = context_data.parms().coeff_modulus();
    size_t coeff_modulus_size = coeff_modulus.size();
    for (size_t i = 0; i < coeff_modulus_size - 1; i++)
        cout << coeff_modulus[i].bit_count() << " + ";
    cout << coeff_modulus.back().bit_count();
    cout << ") bits" << endl;

    cout << "[CONTEXT] coeff_modulus values: (";
    for (int i = 0; i < (coeff_modulus.size() - 1); ++i)
    {
        cout << coeff_modulus[i].value() << ",\t";
        cout << coeff_modulus[coeff_modulus.size() - 1].value() << ")" << endl;
    }

    /* For the BFV scheme print the plain_modulus parameter */
    if (context_data.parms().scheme() == seal::scheme_type::BFV)
    {
        cout << "[CONTEXT] plain_modulus: " << context_data.parms().plain_modulus().value() << endl;
    }
}

int save_key(PublicKey &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_key(SecretKey &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_key(RelinKeys &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_key(Serializable<RelinKeys> &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_key(GaloisKeys &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_key(Serializable<GaloisKeys> &k, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        k.save(out_file);
    else
        ret = 0;
    return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, PublicKey &k)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        k.load(context, in_file);
    else
        ret = 0;
    return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, SecretKey &k)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        k.load(context, in_file);
    else
        ret = 0;
    return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, RelinKeys &k)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        k.load(context, in_file);
    else
        ret = 0;
    return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, GaloisKeys &k)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        k.load(context, in_file);
    else
        ret = 0;
    return ret;
}

void generate_keys(size_t poly_d, size_t p_modulus, bool serializable)
{
    shared_ptr<SEALContext> context;
    init_context(poly_d, p_modulus, context);

    KeyGenerator keygen(context);
    PublicKey pk = keygen.public_key();
    save_key(pk, "bfv.pk");
    SecretKey sk = keygen.secret_key();
    save_key(sk, "bfv.sk");
    if (serializable)
    {
        Serializable<RelinKeys> lk = keygen.relin_keys();
        save_key(lk, "bfv.lk");
    }
    else
    {
        RelinKeys lk = keygen.relin_keys_local();
        save_key(lk, "bfv.lk");
    }
}

bool suffix_exist(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/*
Helper function: Prints the parameters in a SEALContext.
*/
inline void print_parameters(std::shared_ptr<seal::SEALContext> context)
{
    // Verify parameters
    if (!context)
    {
        throw std::invalid_argument("context is not set");
    }
    auto &context_data = *context->key_context_data();

    /*
    Which scheme are we using?
    */
    std::string scheme_name;
    switch (context_data.parms().scheme())
    {
    case seal::scheme_type::BFV:
        scheme_name = "BFV";
        break;
    case seal::scheme_type::CKKS:
        scheme_name = "CKKS";
        break;
    default:
        throw std::invalid_argument("unsupported scheme");
    }
    // cout << "/" << std::endl;
    // cout << "| Encryption parameters :" << std::endl;
    // cout << "|   scheme: " << scheme_name << std::endl;
    // cout << "|   poly_modulus_degree: " << context_data.parms().poly_modulus_degree() << std::endl;

    /*
    Print the size of the true (product) coefficient modulus.
    */
    // cout << "|   coeff_modulus size: ";
    // cout << context_data.total_coeff_modulus_bit_count() << " (";
    auto coeff_modulus = context_data.parms().coeff_modulus();
    std::size_t coeff_modulus_size = coeff_modulus.size();
    // for (std::size_t i = 0; i < coeff_modulus_size - 1; i++)
    // {
    //     cout << coeff_modulus[i].bit_count() << " + ";
    // }
    // cout << coeff_modulus.back().bit_count();
    // cout << ") bits" << std::endl;

    /*
    For the BFV scheme print the plain_modulus parameter.
    */
    // if (context_data.parms().scheme() == seal::scheme_type::BFV)
    // {
    //     cout << "|   plain_modulus: " << context_data.parms().plain_modulus().value() << std::endl;
    // }

    // cout << "\\" << std::endl;
}

void batching_generate_keys(size_t poly_d, int bit_size, string key_dir, bool serializable)
{
    shared_ptr<SEALContext> context;
    // init_context_batching(poly_d, bit_size, context, key_dir);
    // auto qualifiers = context->first_context_data()->qualifiers();
    // cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

    string keypath("");
    string keypath1("/bfv.pk");
    string keypath2("/bfv.sk");
    string keypath3("/bfv.lk");
    string keypath4("/bfv.gk");
    string bfv_params_path(key_dir + "/");

    if (suffix_exist(key_dir, "/"))
    {
        keypath1 = "bfv.pk";
        keypath2 = "bfv.sk";
        keypath3 = "bfv.lk";
        keypath4 = "bfv.gk";
        bfv_params_path = key_dir;
    }

    init_context_batching(poly_d, bit_size, context, bfv_params_path);
    KeyGenerator keygen(context);
    PublicKey pk = keygen.public_key();
    keypath.append(key_dir);
    keypath.append(keypath1);

    // cout << "[INFO] Keypathname pk: " << keypath << endl;
    save_key(pk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath2);
    SecretKey sk = keygen.secret_key();
    // cout << "[INFO] Keypathname sk: " << keypath << endl;
    save_key(sk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath3);
    // cout << "[INFO] Keypathname lk: " << keypath << endl;
    if (serializable)
    {
        Serializable<RelinKeys> lk = keygen.relin_keys();
        save_key(lk, keypath);
    }
    else
    {
        RelinKeys lk = keygen.relin_keys_local();
        save_key(lk, keypath);
    }

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath4);
    // cout << "[INFO] Keypathname gk: " << keypath << endl;
    if (serializable)
    {
        Serializable<GaloisKeys> gk = keygen.galois_keys();
        save_key(gk, keypath);
    }
    else
    {
        GaloisKeys gk = keygen.galois_keys_local();
        save_key(gk, keypath);
    }
    // print_parameters(context);
}

void generate_keys_ckks(size_t poly_d, int bit_size, string key_dir, bool serializable)
{
    shared_ptr<SEALContext> context;
    // init_context_batching(poly_d, bit_size, context, key_dir);
    // auto qualifiers = context->first_context_data()->qualifiers();
    // cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

    string keypath("");
    string keypath1("/ckks.pk");
    string keypath2("/ckks.sk");
    string keypath3("/ckks.lk");
    string keypath4("/ckks.gk");
    string ckks_params_path(key_dir + "/");

    if (suffix_exist(key_dir, "/"))
    {
        keypath1 = "ckks.pk";
        keypath2 = "ckks.sk";
        keypath3 = "ckks.lk";
        keypath4 = "ckks.gk";
        ckks_params_path = key_dir;
    }

    // ckks_init_context_batching(poly_d, bit_size, context, ckks_params_path);

    // init_context_ckks(poly_d, bit_size, context, ckks_params_path);
    init_context_ckks(poly_d, context, ckks_params_path);
    KeyGenerator keygen(context);
    PublicKey pk = keygen.public_key();
    keypath.append(key_dir);
    keypath.append(keypath1);

    // cout << "[INFO] Keypathname pk: " << keypath << endl;
    save_key(pk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath2);
    SecretKey sk = keygen.secret_key();
    // cout << "[INFO] Keypathname sk: " << keypath << endl;
    save_key(sk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath3);
    // cout << "[INFO] Keypathname lk: " << keypath << endl;
    if (serializable)
    {
        Serializable<RelinKeys> lk = keygen.relin_keys();
        save_key(lk, keypath);
    }
    else
    {
        RelinKeys lk = keygen.relin_keys_local();
        save_key(lk, keypath);
    }

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath4);
    // cout << "[INFO] Keypathname gk: " << keypath << endl;
    if (serializable)
    {
        Serializable<GaloisKeys> gk = keygen.galois_keys();
        save_key(gk, keypath);
    }
    else
    {
        GaloisKeys gk = keygen.galois_keys_local();
        save_key(gk, keypath);
    }
    print_parameters(context);
}

void batching_generate_keys(
    size_t poly_d, vector<int> bit_sizes, std::uint64_t plain_modulus, string key_dir, bool serializable)
{
    shared_ptr<SEALContext> context;
    // init_context_batching(poly_d, bit_sizes, plain_modulus, context, key_dir);
    // auto qualifiers = context->first_context_data()->qualifiers();
    // cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

    string keypath("");
    string keypath1("/bfv.pk");
    string keypath2("/bfv.sk");
    string keypath3("/bfv.lk");
    string keypath4("/bfv.gk");
    string bfv_params_path(key_dir + "/");

    if (suffix_exist(key_dir, "/"))
    {
        keypath1 = "bfv.pk";
        keypath2 = "bfv.sk";
        keypath3 = "bfv.lk";
        keypath4 = "bfv.gk";
        bfv_params_path = key_dir;
    }

    init_context_batching(poly_d, bit_sizes, plain_modulus, context, bfv_params_path);
    KeyGenerator keygen(context);
    PublicKey pk = keygen.public_key();
    keypath.append(key_dir);
    keypath.append(keypath1);

    // cout << "[INFO] Keypathname pk: " << keypath << endl;
    save_key(pk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath2);
    SecretKey sk = keygen.secret_key();
    // cout << "[INFO] Keypathname sk: " << keypath << endl;
    save_key(sk, keypath);

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath3);
    // cout << "[INFO] Keypathname lk: " << keypath << endl;
    if (serializable)
    {
        Serializable<RelinKeys> lk = keygen.relin_keys();
        save_key(lk, keypath);
    }
    else
    {
        RelinKeys lk = keygen.relin_keys_local();
        save_key(lk, keypath);
    }

    keypath = "";
    keypath.append(key_dir);
    keypath.append(keypath4);
    // cout << "[INFO] Keypathname gk: " << keypath << endl;
    if (serializable)
    {
        Serializable<GaloisKeys> gk = keygen.galois_keys();
        save_key(gk, keypath);
    }
    else
    {
        GaloisKeys gk = keygen.galois_keys_local();
        save_key(gk, keypath);
    }
    // print_parameters(context);
}

void init_operator(struct encryptor_t &op_st)
{
    load_context(op_st.context, "bfv_params.conf");
    PublicKey pk;
    load_key(op_st.context, "bfv.pk", pk);
    op_st.encr = new Encryptor(op_st.context, pk);
    op_st.icode = new IntegerEncoder(op_st.context);
}

void init_operator(struct encryptor_t &op_st, const string &key_dir)
{
    string bfv_params_path("");
    string bfv_params_path1("/bfv_params.conf");
    bfv_params_path = "";
    bfv_params_path.append(key_dir);
    bfv_params_path.append(bfv_params_path1);
    // cout << "[INFO] bfvparams: " << bfv_params_path << endl;
    load_context(op_st.context, bfv_params_path);
    PublicKey pk;
    string keypath("");
    string keypath1("bfv.pk");
    keypath.append(key_dir);
    keypath.append(keypath1);
    // cout << "[INFO] Keypath encrypt: " << keypath << endl;
    load_key(op_st.context, keypath, pk);
    op_st.encr = new Encryptor(op_st.context, pk);
    op_st.icode = new IntegerEncoder(op_st.context);
}

// void init_operator_ckks(struct encryptor_t &op_st, const string &key_dir)
void init_operator_ckks(struct cencryptor_t &op_st, const string &key_dir)
{
    string ckks_params_path("");
    string ckks_params_path1("/ckks_params.conf");
    ckks_params_path = "";
    ckks_params_path.append(key_dir);
    ckks_params_path.append(ckks_params_path1);
    // cout << "[INFO] ckksparams: " << ckks_params_path << endl;
    load_context(op_st.context, ckks_params_path);
    PublicKey pk;
    string keypath("");
    string keypath1("ckks.pk");
    keypath.append(key_dir);
    keypath.append(keypath1);
    // cout << "[INFO] Keypath encrypt: " << keypath << endl;
    load_key(op_st.context, keypath, pk);
    op_st.encr = new Encryptor(op_st.context, pk);
    // op_st.icode = new IntegerEncoder(op_st.context);
    op_st.ccode = new CKKSEncoder(op_st.context);
    // auto &context_data = *(op_st.context.key_context_data());
    auto &context_data = *op_st.context->key_context_data();
    int poly_deg = context_data.parms().poly_modulus_degree();
    switch (poly_deg)
    {
    case 4096:
        op_st.scale = pow(2.0, 20);
    case 8192:
        op_st.scale = pow(2.0, 40);
    case 16384:
        op_st.scale = pow(2.0, 40);
        // op_st.scale = pow(2.0, 20);
    }
    // return 1;
}

void init_operator_ckks(struct cdecryptor_t &op_st, const string &key_dir)
{
    string ckks_params_path("");
    string ckks_params_path1("/ckks_params.conf");
    ckks_params_path = "";
    ckks_params_path.append(key_dir);
    ckks_params_path.append(ckks_params_path1);
    // cout << "[INFO] ckksparams: " << ckks_params_path << endl;
    load_context(op_st.context, ckks_params_path);
    // PublicKey pk;
    SecretKey sk;
    string keypath("");
    string keypath1("ckks.sk");
    keypath.append(key_dir);
    keypath.append(keypath1);
    // cout << "[INFO] Keypath encrypt: " << keypath << endl;
    load_key(op_st.context, keypath, sk);
    op_st.decr = new Decryptor(op_st.context, sk);
    // op_st.icode = new IntegerEncoder(op_st.context);
    op_st.ccode = new CKKSEncoder(op_st.context);
    // auto &context_data = *(op_st.context.key_context_data());
    auto &context_data = *op_st.context->key_context_data();
    int poly_deg = context_data.parms().poly_modulus_degree();
    switch (poly_deg)
    {
    case 4096:
        op_st.scale = pow(2.0, 20);
    case 8192:
        op_st.scale = pow(2.0, 40);
    case 16384:
        op_st.scale = pow(2.0, 40);
        // op_st.scale = pow(2.0, 20);
    }
    // return 1;
}

void init_operator_ckks(struct cevaluator_t &op_st, const string &key_dir)
{
    string ckks_params_path("");
    string ckks_params_path1("/ckks_params.conf");
    ckks_params_path = "";
    ckks_params_path.append(key_dir);
    ckks_params_path.append(ckks_params_path1);
    //   cout << "[INFO] bfvparams: " << ckks_params_path << endl;
    load_context(op_st.context, ckks_params_path);

    string keypath("");
    string keypath1("ckks.lk");
    keypath.append(key_dir);
    keypath.append(keypath1);
    //   cout << "[INFO] Keypath evaluator: " << keypath << endl;
    load_key(op_st.context, keypath, op_st.lk);

    string keypath3("");
    string keypath4("ckks.gk");
    keypath3.append(key_dir);
    keypath3.append(keypath4);
    //   cout << "[INFO] Keypath evaluator: " << keypath3 << endl;
    load_key(op_st.context, keypath3, op_st.gk);

    // op_st.eval = new Evaluator(op_st.context, sk);

    // op_st.icode = new IntegerEncoder(op_st.context);
    // op_st.ccode = new CKKSEncoder(op_st.context);
    op_st.eval = new Evaluator(op_st.context);
    // auto &context_data = *(op_st.context.key_context_data());
    auto &context_data = *op_st.context->key_context_data();
    int poly_deg = context_data.parms().poly_modulus_degree();
    switch (poly_deg)
    {
    case 4096:
        op_st.scale = pow(2.0, 20);
    case 8192:
        op_st.scale = pow(2.0, 40);
    case 16384:
        op_st.scale = pow(2.0, 40);
        // op_st.scale = pow(2.0, 20);
    }
    // return 1;
}

// int init_operator_ckks(struct cencryptor_t &op_st, const string &key_dir)
// {
//     int ret = 1;

//     //   if (!load_context("/ckks_params.conf", op_st.context)) {
//     //     cerr << "[seal-error] failure for loading ckks context during encryptor setting!" << endl;
//     //     ret = 0;
//     //   }
//     //   else {
//     //     PublicKey pk;
//     //     if (!load_key(op_st.context, "ckks.pk", pk)) {
//     //       cerr << "[seal-error] failure for loading ckks public key during encryptor setting!" << endl;
//     //       ret = 0;
//     //     }
//     //     else {
//     op_st.encr = new Encryptor(op_st.context, pk);
//     op_st.ccode = new CKKSEncoder(op_st.context);
//     auto &context_data = *(op_st.context.key_context_data());
//     int poly_deg = context_data.parms().poly_modulus_degree();
//     switch (poly_deg)
//     {
//     case 4096:
//         op_st.scale = pow(2.0, 20);
//     case 8192:
//         op_st.scale = pow(2.0, 40);
//     }
//     // }
//     //   }
//     return ret;
// }

void init_operator_batching(struct encryptor_t &op_st, const string &key_dir)
{
    init_operator(op_st, key_dir);
    op_st.bcode = new BatchEncoder(op_st.context);
}

void delete_operator(struct encryptor_t &op_st)
{
    delete op_st.encr;
    delete op_st.icode;
}

void delete_operator_batching(struct encryptor_t &op_st)
{
    delete_operator(op_st);
    delete op_st.bcode;
}

void delete_operator_ckks(struct cencryptor_t &op_st)
{
    delete op_st.encr;
    delete op_st.ccode;
}

void delete_operator_ckks(struct cdecryptor_t &op_st)
{
    delete op_st.decr;
    delete op_st.ccode;
}

void delete_operator_ckks(struct cevaluator_t &op_st)
{
    delete op_st.eval;
}

void init_operator(struct decryptor_t &op_st)
{
    load_context(op_st.context, "bfv_params.conf");
    SecretKey sk;
    load_key(op_st.context, "bfv.sk", sk);
    op_st.decr = new Decryptor(op_st.context, sk);
    op_st.icode = new IntegerEncoder(op_st.context);
}

void init_operator(struct decryptor_t &op_st, const std::string &key_dir)
{
    string bfv_params_path("");
    string bfv_params_path1("/bfv_params.conf");
    bfv_params_path = "";
    bfv_params_path.append(key_dir);
    bfv_params_path.append(bfv_params_path1);
    //   cout << "[INFO] bfvparams: " << bfv_params_path << endl;

    load_context(op_st.context, bfv_params_path);
    SecretKey sk;
    string keypath("");
    string keypath1("bfv.sk");

    keypath.append(key_dir);
    keypath.append(keypath1);
    //   cout << "[INFO] Keypath decrypt: " << keypath << endl;

    load_key(op_st.context, keypath, sk);

    op_st.decr = new Decryptor(op_st.context, sk);
    op_st.icode = new IntegerEncoder(op_st.context);
}

void init_operator_batching(struct decryptor_t &op_st, const string &key_dir)
{
    init_operator(op_st, key_dir);
    op_st.bcode = new BatchEncoder(op_st.context);
}

void delete_operator(struct decryptor_t &op_st)
{
    delete op_st.decr;
    delete op_st.icode;
}

void delete_operator_batching(struct decryptor_t &op_st)
{
    delete_operator(op_st);
    delete op_st.bcode;
}

void init_operator(struct evaluator_t &op_st)
{
    load_context(op_st.context, "bfv_params.conf");
    load_key(op_st.context, "bfv.lk", op_st.lk);
    op_st.eval = new Evaluator(op_st.context);
}

void init_operator(struct evaluator_t &op_st, const string &relink_key_path)
{
    load_context(op_st.context, "bfv_params.conf");
    load_key(op_st.context, relink_key_path, op_st.lk);
    op_st.eval = new Evaluator(op_st.context);
}

void init_operator_batching(struct evaluator_t &op_st, const string &key_dir)
{
    string bfv_params_path("");
    string bfv_params_path1("/bfv_params.conf");
    bfv_params_path = "";
    bfv_params_path.append(key_dir);
    bfv_params_path.append(bfv_params_path1);
    //   cout << "[INFO] bfvparams: " << bfv_params_path << endl;
    load_context(op_st.context, bfv_params_path);

    string keypath("");
    string keypath1("bfv.lk");
    keypath.append(key_dir);
    keypath.append(keypath1);
    //   cout << "[INFO] Keypath evaluator: " << keypath << endl;
    load_key(op_st.context, keypath, op_st.lk);

    string keypath3("");
    string keypath4("bfv.gk");
    keypath3.append(key_dir);
    keypath3.append(keypath4);
    //   cout << "[INFO] Keypath evaluator: " << keypath3 << endl;
    load_key(op_st.context, keypath3, op_st.gk);

    op_st.eval = new Evaluator(op_st.context);
}

void delete_operator(struct evaluator_t &op_st)
{
    delete op_st.eval;
}

void delete_operator_batching(struct evaluator_t &op_st)
{
    delete_operator(op_st);
}

void init_plaintext(struct encryptor_t &op_st, int64_t plain, Plaintext &pt)
{
    pt = Plaintext(op_st.icode->encode(plain));
}

void init_ciphertext(struct encryptor_t &op_st, int64_t plain, Ciphertext &ct)
{
    // cout << "[INFO] encrypting: " << endl;
    op_st.encr->encrypt(Plaintext(op_st.icode->encode(plain)), ct);
    // cout << plain << endl;
}

void init_ciphermatrix(struct encryptor_t &op_st, vector<int64_t> &plain_matrix, Ciphertext &encrypted_matrix)
{
    // cout << "[INFO] encrypting: " << endl;
    Plaintext plaintext_matrix;
    // BatchEncoder batch_encoder(op_st.context);
    // batch_encoder.encode(plain_matrix, plaintext_matrix);
    op_st.bcode->encode(plain_matrix, plaintext_matrix);
    // op_st.ccode->encode(plain_matrix, plaintext_matrix);
    op_st.encr->encrypt(plaintext_matrix, encrypted_matrix);
    // cout << plain << endl;
}

/* ckks plaintext management */
// void init_plaintext_ckks(CKKSEncoder& encoder, double scale, vector<double>& p_vector, Plaintext& pt, bool
// print_info) void init_plaintext_ckks(CKKSEncoder& encoder, double scale, vector<double>& p_vector, Plaintext& pt)
// {
//   try {
//     encoder.encode(p_vector, scale, pt);
//   }
//   catch (std::exception &e) {
//     clog << "[seal-error] catched exception: " << e.what() << endl;
//     clog << "[seal-error] ckks slots encoding error" << endl;
//   }

//   if (print_info) {
//     clog << "[seal-ckks] plaintexts: " << endl;
//     print_vectors(p_vector);
//   }
// }

/* ckks ciphertext management */
// void init_ciphertext(CKKSEncoder& encoder, Encryptor& encryptor, double scale, vector<double>& c_vector, Ciphertext&
// ct, bool print_info)
void init_ciphertext_ckks(
    CKKSEncoder &encoder, Encryptor &encryptor, double scale, vector<double> &c_vector, Ciphertext &ct)
{
    Plaintext pt;
    try
    {
        encoder.encode(c_vector, scale, pt);
    }
    catch (std::exception &e)
    {
        clog << "[seal-error] catched exception: " << e.what() << endl;
        clog << "[seal-error] ckks slots encoding error" << endl;
    }
    encryptor.encrypt(pt, ct);

    //   if (print_info) {
    //     clog << "[seal-ckks] ciphertext inputs: " << endl;
    //     print_vectors(c_vector);
    //   }
}

void init_ciphertext_ckks(cencryptor_t &op_st, double scale, vector<double> &c_vector, Ciphertext &ct)
{
    init_ciphertext_ckks(*(op_st.ccode), *(op_st.encr), scale, c_vector, ct);
}

void init_ciphertext_ckks(cencryptor_t &op_st, vector<double> &c_vector, Ciphertext &ct)
{
    init_ciphertext_ckks(*(op_st.ccode), *(op_st.encr), op_st.scale, c_vector, ct);
}



/* ckks decryption */
void decrypt_ciphertext_ckks(cdecryptor_t &op_st, Ciphertext &ct, vector<double> &pt_val)
{
    decrypt_ciphertext_ckks(*(op_st.ccode), *(op_st.decr), ct, pt_val);
}

void decrypt_ciphertext_ckks(CKKSEncoder &encoder, Decryptor &decryptor, Ciphertext &ct, vector<double> &pt_val)
{
    Plaintext pt;
    decryptor.decrypt(ct, pt);
    encoder.decode(pt, pt_val);

    //   if (print_info) {
    //     clog << "[seal-ckks] decrypted plaintexts: " << endl;
    //     print_vectors(pt_val);
    //   }
}

// vector<double> decrypt_ciphermatrix_ckks(struct decryptor_t &op_st, Ciphertext &ct)
// {
//     Plaintext pt;
//     op_st.decr->decrypt(ct, pt);
//     vector<double> pod_matrix;
//     // BatchEncoder batch_encoder(op_st.context);
//     // batch_encoder.decode(pt, pod_matrix);
//     encoder.decode(pt, pod_matrix);
//     // print_matrix(pod_matrix, 3);
//     decrypt_ciphertext_ckks
//     return pod_matrix;
// }

/* saving ciphertexts and plaintexts */
// plaintexts
int load_plaintext_ckks(struct cencryptor_t &op_st, Plaintext &pt, const string &filename)
{
    return load_plaintext(op_st.context, pt, filename);
}

int load_plaintext_ckks(struct cdecryptor_t &op_st, Plaintext &pt, const string &filename)
{
    return load_plaintext(op_st.context, pt, filename);
}

int load_plaintext_ckks(struct cevaluator_t &op_st, Plaintext &pt, const string &filename)
{
    return load_plaintext(op_st.context, pt, filename);
}
// ciphertexts
int load_ciphertext_ckks(struct cevaluator_t &op_st, Ciphertext &ct, const string &filename)
{
    return load_ciphertext(op_st.context, ct, filename);
}

int load_ciphertext_ckks(struct cencryptor_t &op_st, Ciphertext &ct, const string &filename)
{
    return load_ciphertext(op_st.context, ct, filename);
}

int load_ciphertext_ckks(struct cdecryptor_t &op_st, Ciphertext &ct, const string &filename)
{
    return load_ciphertext(op_st.context, ct, filename);
}

void decrypt_ciphertext(struct decryptor_t &op_st, Ciphertext &ct)
{
    Plaintext pt;
    op_st.decr->decrypt(ct, pt);
    int64_t res = op_st.icode->decode_int64(pt);
    // cout << "[INFO] decrypted result: " << res << endl;
}

int64_t decrypt_ciphertext_and_return_value(struct decryptor_t &op_st, Ciphertext &ct)
{
    Plaintext pt;
    op_st.decr->decrypt(ct, pt);
    int64_t res = op_st.icode->decode_int64(pt);
    // cout << "[INFO] Decrypted result: " << res << endl;
    return res;
}

vector<int64_t> decrypt_ciphermatrix(struct decryptor_t &op_st, Ciphertext &ct)
{
    Plaintext pt;
    op_st.decr->decrypt(ct, pt);
    vector<int64_t> pod_matrix;
    BatchEncoder batch_encoder(op_st.context);
    batch_encoder.decode(pt, pod_matrix);
    // print_matrix(pod_matrix, 3);
    return pod_matrix;
}

int save_plaintext(Plaintext &pt, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        pt.save(out_file);
    else
        ret = 0;
    return ret;
}

int save_ciphertext(Ciphertext &ct, const string &filename)
{
    int ret = 1;
    ofstream out_file;
    if (open_binary_file(out_file, filename))
        ct.save(out_file);
    else
        ret = 0;
    return ret;
}

int load_plaintext(shared_ptr<SEALContext> &context, Plaintext &pt, const string &filename)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        pt.load(context, in_file);
    else
        ret = 0;
    return ret;
}

int load_plaintext(struct evaluator_t &op_st, Plaintext &pt, const string &filename)
{
    return load_plaintext(op_st.context, pt, filename);
}

int load_plaintext(struct decryptor_t &op_st, Plaintext &pt, const string &filename)
{
    return load_plaintext(op_st.context, pt, filename);
}

int load_ciphertext(shared_ptr<SEALContext> &context, Ciphertext &ct, const string &filename)
{
    int ret = 1;
    ifstream in_file;
    if (open_binary_file(in_file, filename))
        ct.load(context, in_file);
    else
        ret = 0;
    return ret;
}

int load_ciphertext(struct evaluator_t &op_st, Ciphertext &ct, const string &filename)
{
    return load_ciphertext(op_st.context, ct, filename);
}

int load_ciphertext(struct decryptor_t &op_st, Ciphertext &ct, const string &filename)
{
    return load_ciphertext(op_st.context, ct, filename);
}

/* ckks plaintext management */
void init_plaintext_ckks(CKKSEncoder &encoder, double scale, vector<double> &p_vector, Plaintext &pt, bool print_info)
{
    try
    {
        encoder.encode(p_vector, scale, pt);
    }
    catch (std::exception &e)
    {
        clog << "[seal-error] catched exception: " << e.what() << endl;
        clog << "[seal-error] ckks slots encoding error" << endl;
    }

    // if (print_info)
    // {
    //     clog << "[seal-ckks] plaintexts: " << endl;
    //     print_vectors(p_vector);
    // }
}

void init_plaintext_ckks(cencryptor_t &op_st, double scale, vector<double> &p_vector, Plaintext &pt, bool print_info)
{
    init_plaintext_ckks(*(op_st.ccode), scale, p_vector, pt, print_info);
}

void init_plaintext_ckks(cencryptor_t &op_st, vector<double> &p_vector, Plaintext &pt, bool print_info)
{
    init_plaintext_ckks(*(op_st.ccode), op_st.scale, p_vector, pt, print_info);
}

void init_plaintext_ckks(cdecryptor_t &op_st, double scale, vector<double> &p_vector, Plaintext &pt, bool print_info)
{
    init_plaintext_ckks(*(op_st.ccode), scale, p_vector, pt, print_info);
}

void init_plaintext_ckks(cdecryptor_t &op_st, vector<double> &p_vector, Plaintext &pt, bool print_info)
{
    init_plaintext_ckks(*(op_st.ccode), op_st.scale, p_vector, pt, print_info);
}