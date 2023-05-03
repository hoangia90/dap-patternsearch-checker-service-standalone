#include "seal_api.h"

/* namespaces */
using namespace std;
using namespace seal;

/* functions */
int open_binary_file(ifstream &in_file, const string &filename)
{
  int ret = 1;
  in_file =  ifstream(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR] file opening failure" << endl;
    ret = 0;
  }

  return ret;
}

int open_binary_file(ofstream &out_file, const string &filename)
{
  int ret = 1;
  out_file =  ofstream(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR] file opening failure" << endl;
    ret = 0;
  }

  return ret;
}

int save_params(EncryptionParameters &params, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    params.save(out_file);
  else
    ret = 0;
  return ret;
}

int load_params(EncryptionParameters &params, const string &filename)
{
  int ret = 1;
  ifstream in_file;
  if(open_binary_file(in_file, filename))
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

void load_context(shared_ptr<SEALContext> &context, const string &filename)
{
  EncryptionParameters params;
  load_params(params, filename);
  context = SEALContext::Create(params);
  print_context(context);
}

/* print paramaeters function from examples.h */
void print_context(shared_ptr<SEALContext>& context)
{
  if (!context)
    throw invalid_argument("[ERROR] context is not set");

  auto &context_data = *context->key_context_data();
  /* which scheme is used */
  string scheme_name;
  switch (context_data.parms().scheme()) {
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

  /* Print the size of the true (product) coefficient modulus */
  cout << "[CONTEXT] coeff_modulus size: ";
  cout << context_data.total_coeff_modulus_bit_count() << " (";
  auto coeff_modulus = context_data.parms().coeff_modulus();
  size_t coeff_modulus_size = coeff_modulus.size();
  for (size_t i = 0; i < coeff_modulus_size - 1; i++)
    cout << coeff_modulus[i].bit_count() << " + ";
  cout << coeff_modulus.back().bit_count();
  cout << ") bits" << endl;

  std::cout << "[CONTEXT] coeff_modulus values: (" ;
  for(int i = 0; i < (coeff_modulus.size() - 1); ++i)
    cout  << coeff_modulus[i].value() << ",\t";
  cout << coeff_modulus[coeff_modulus.size() - 1].value() << ")" <<  endl;

  /* For the BFV scheme print the plain_modulus parameter */
  if (context_data.parms().scheme() == seal::scheme_type::BFV)
    cout << "[CONTEXT] plain_modulus: " << context_data.parms().plain_modulus().value() << endl;
}

int save_key(PublicKey &k, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    k.save(out_file);
  else
    ret = 0;
  return ret;
}

int save_key(SecretKey &k, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    k.save(out_file);
  else
    ret = 0;
  return ret;
}

int save_key(RelinKeys &k, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    k.save(out_file);
  else
    ret = 0;
  return ret;
}

int save_key(Serializable<RelinKeys> &k, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    k.save(out_file);
  else
    ret = 0;
  return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, PublicKey &k)
{
  int ret = 1;
  ifstream in_file;
  if(open_binary_file(in_file, filename))
    k.load(context, in_file);
  else
    ret = 0;
  return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, SecretKey &k)
{
  int ret = 1;
  ifstream in_file;
  if(open_binary_file(in_file, filename))
    k.load(context, in_file);
  else
    ret = 0;
  return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, RelinKeys &k)
{
  int ret = 1;
  ifstream in_file;
  if(open_binary_file(in_file, filename))
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
  if (serializable) {
    Serializable<RelinKeys> lk = keygen.relin_keys();
    save_key(lk, "bfv.lk");
  }
  else {
    RelinKeys lk = keygen.relin_keys_local();
    save_key(lk, "bfv.lk");
  }
}

void init_operator(size_t poly_d, size_t p_modulus, struct encryptor_t &op_st)
{
  load_context(op_st.context, "bfv_params.conf");
  PublicKey pk;
  load_key(op_st.context, "bfv.pk", pk);
  op_st.encr = new Encryptor(op_st.context, pk);
  op_st.icode = new IntegerEncoder(op_st.context);
}

void delete_operator(struct encryptor_t &op_st)
{
  delete op_st.encr;
  delete op_st.icode;
}

void init_operator(size_t poly_d, size_t p_modulus, struct decryptor_t &op_st)
{
  load_context(op_st.context, "bfv_params.conf");
  SecretKey sk;
  load_key(op_st.context, "bfv.sk", sk);
  op_st.decr = new Decryptor(op_st.context, sk);
  op_st.icode = new IntegerEncoder(op_st.context);
}

void delete_operator(struct decryptor_t &op_st)
{
  delete op_st.decr;
  delete op_st.icode;
}

void init_operator(size_t poly_d, size_t p_modulus, struct evaluator_t &op_st)
{
  load_context(op_st.context, "bfv_params.conf");
  load_key(op_st.context, "bfv.lk", op_st.lk);
  op_st.eval = new Evaluator(op_st.context);
}

void delete_operator(struct evaluator_t &op_st)
{
  delete op_st.eval;
}

void init_plaintext(struct encryptor_t &op_st, int64_t plain, Plaintext &pt)
{
  pt = Plaintext(op_st.icode->encode(plain));
}

void init_ciphertext(struct encryptor_t &op_st, int64_t plain, Ciphertext &ct)
{
  cout << "[INFO] encrypting: " << endl;
  op_st.encr->encrypt(Plaintext(op_st.icode->encode(plain)), ct);
  cout << plain << endl;
}

void decrypt_ciphertext(struct decryptor_t &op_st, Ciphertext &ct)
{
  Plaintext pt;
  op_st.decr->decrypt(ct, pt);
  int64_t res = op_st.icode->decode_int64(pt);
  cout << "[INFO] decrypted result: " << res << endl;
}

int save_plaintext(Plaintext &pt, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    pt.save(out_file);
  else
    ret = 0;
  return ret;
}

int save_ciphertext(Ciphertext &ct, const string &filename)
{
  int ret = 1;
  ofstream out_file;
  if(open_binary_file(out_file, filename))
    ct.save(out_file);
  else
    ret = 0;
  return ret;
}

int load_plaintext(shared_ptr<SEALContext> &context, Plaintext &pt, const string &filename)
{
  int ret = 1;
  ifstream in_file;
  if(open_binary_file(in_file, filename))
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
  if(open_binary_file(in_file, filename))
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
