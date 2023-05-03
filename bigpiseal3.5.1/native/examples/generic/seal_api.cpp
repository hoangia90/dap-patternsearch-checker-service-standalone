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
    cerr << "[ERRROR06] file opening failure" << filename << endl;
    ret = 0;
  }

  return ret;
}

int open_binary_file(ofstream &out_file, const string &filename)
{
  int ret = 1;
  out_file =  ofstream(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR07] file opening failure" << filename << endl;
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

void init_context(size_t poly_d, size_t p_modulus, shared_ptr<SEALContext> &context,const std::string& pathname)
{
  EncryptionParameters params(scheme_type::BFV);
  params.set_poly_modulus_degree(poly_d);
  params.set_coeff_modulus(CoeffModulus::BFVDefault(poly_d));
  params.set_plain_modulus(p_modulus);
  //ruf
  //cout << "[INFO] save  bfvparams: " << pathname<< endl; 
  
  save_params(params, pathname);

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
  ofstream out_file(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR 00] File opening failure  " << filename << endl;
    exit(1) ;
    ret = 0;
  }
  else
    k.save(out_file);

  return ret;
}

int save_key(SecretKey &k, const string &filename)
{
  int ret = 1;
  ofstream out_file(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR 01] File opening failure  " << filename << endl;
    exit(1) ;
    ret = 0;
  }
  else
    k.save(out_file);

  return ret;
}

int save_key(RelinKeys &k, const string &filename)
{
  int ret = 1;
  ofstream out_file(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR 02] File opening failure  " << filename << endl;
    exit(1) ;
    ret = 0;
  }
  else
    k.save(out_file);
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
  int ret = 0;
  ifstream in_file(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR 03] File opening failure  " << filename << endl;
    exit(1) ;
    ret = 0;
  }
  else
    k.load(context, in_file);

  return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, SecretKey &k)
{
  int ret = 1;
  ifstream in_file(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR 04] File opening failure  " << filename << endl;
    ret = 0;
  }
  else
    k.load(context, in_file);

  return ret;
}

int load_key(shared_ptr<SEALContext> &context, const string &filename, RelinKeys &k)
{
  int ret = 1;
  ifstream in_file(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR 05] File opening failure"<< filename << endl;
    ret = 0;
  }
  else
    k.load(context, in_file);

  return ret;
}

void generate_keys(size_t poly_d, size_t p_modulus, const std::string& pathname, bool serializable )
//void generate_keys(size_t poly_d, size_t p_modulus, bool serializable ,const std::string& pathname)
{
  shared_ptr<SEALContext> context;
 
  string keypath("");
  string keypath1("/bfv.pk");
  string keypath2("/bfv.sk");
  string keypath3("/bfv.lk");
  string bfv_params_path("");
  string bfv_params_path1("/bfv_params.conf");

  if (suffix_exist(pathname, "/")) 
  { 
   keypath1="bfv.pk";
   keypath2="bfv.sk";
   keypath3="bfv.lk";
   bfv_params_path1="bfv_params.conf";
  }
  bfv_params_path="";
  bfv_params_path.append(pathname);
  bfv_params_path.append(bfv_params_path1);
  
  init_context(poly_d, p_modulus, context,bfv_params_path);
  KeyGenerator keygen(context);
  PublicKey pk = keygen.public_key();
  keypath.append(pathname);
  keypath.append(keypath1);  
    
  //cout << "[INFO] Keypathname pk: " << keypath << endl;
  save_key(pk, keypath );

  keypath="";
  keypath.append(pathname);
  keypath.append(keypath2);  
  SecretKey sk = keygen.secret_key();
  //cout << "[INFO] Keypathname sk: " << keypath << endl;
  save_key(sk, keypath);
  
  keypath="";
  keypath.append(pathname);
  keypath.append(keypath3);
  //cout << "[INFO] Keypathname lk: " << keypath << endl;
  if (serializable) {
    Serializable<RelinKeys> lk = keygen.relin_keys();
    save_key(lk, keypath);
  }
  else {
    RelinKeys lk = keygen.relin_keys_local();
    save_key(lk, keypath);
  }
}

void init_operator(size_t poly_d, size_t p_modulus, struct encryptor_t &op_st,const std::string& pathname)
{
  string bfv_params_path("");
  string bfv_params_path1("/bfv_params.conf");
  bfv_params_path="";
  bfv_params_path.append(pathname);
  bfv_params_path.append(bfv_params_path1);
  //cout << "[INFO] bfvparams: " << bfv_params_path << endl; 
  load_context(op_st.context, bfv_params_path);
  PublicKey pk;
  string keypath("");
  string keypath1("bfv.pk"); 
  keypath.append(pathname);
  keypath.append(keypath1);
  //cout << "[INFO] Keypath encrypt: " << keypath << endl;  
  load_key(op_st.context, keypath, pk);
  op_st.encr = new Encryptor(op_st.context, pk);
  op_st.icode = new IntegerEncoder(op_st.context);
}

void delete_operator(struct encryptor_t &op_st)
{
  delete op_st.encr;
  delete op_st.icode;
}

void init_operator(size_t poly_d, size_t p_modulus, struct decryptor_t &op_st,const std::string& pathname)
{
  string bfv_params_path("");
  string bfv_params_path1("/bfv_params.conf");
  bfv_params_path="";
  bfv_params_path.append(pathname);
  bfv_params_path.append(bfv_params_path1);
  cout << "[INFO] bfvparams: " << bfv_params_path << endl; 
  
  load_context(op_st.context, bfv_params_path);
  SecretKey sk;
  string keypath("");
  string keypath1("bfv.sk"); 
  
  keypath.append(pathname);
  keypath.append(keypath1);
  cout << "[INFO] Keypath decrypt: " << keypath << endl;

  load_key(op_st.context, keypath, sk);

  op_st.decr = new Decryptor(op_st.context, sk);
  op_st.icode = new IntegerEncoder(op_st.context);
}

void delete_operator(struct decryptor_t &op_st)
{
  delete op_st.decr;
  delete op_st.icode;
}

void init_operator(size_t poly_d, size_t p_modulus, struct evaluator_t &op_st,const std::string& pathname)
{
  string bfv_params_path("");
  string bfv_params_path1("/bfv_params.conf");
  bfv_params_path="";
  bfv_params_path.append(pathname);
  bfv_params_path.append(bfv_params_path1);
  cout << "[INFO] bfvparams: " << bfv_params_path << endl; 
  load_context(op_st.context, bfv_params_path);
  string keypath("");
  string keypath1("bfv.lk"); 
  keypath.append(pathname);
  keypath.append(keypath1);
  cout << "[INFO] Keypath evaluator: " << keypath << endl;
  load_key(op_st.context, keypath, op_st.lk);
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
  cout << "[INFO] Encrypting: " << endl;
  op_st.encr->encrypt(Plaintext(op_st.icode->encode(plain)), ct);
  cout << plain << endl;
}

void decrypt_ciphertext(struct decryptor_t &op_st, Ciphertext &ct)
{
  Plaintext pt;
  op_st.decr->decrypt(ct, pt);
  int64_t res = op_st.icode->decode_int64(pt);
  cout << "[INFO] Decrypted result: " << res << endl;
}

int save_plaintext(Plaintext &pt, const string &filename)
{
  int ret = 1;
  ofstream out_file(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR1 File opening failure  " << filename<< endl;
    ret = 0;
  }
  else
    pt.save(out_file);

  return ret;
}

int save_ciphertext(Ciphertext &ct, const string &filename)
{
  int ret = 1;
  ofstream out_file(filename, std::ios::binary);
  if(!out_file) {
    cerr << "[ERRROR2] File opening failure  " << filename << endl;
    ret = 0;
  }
  else
    ct.save(out_file);

  return ret;
}

int load_plaintext(shared_ptr<SEALContext> &context, Plaintext &pt, const string &filename)
{
  int ret = 1;
  ifstream in_file(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR3] File opening failure  " << filename << endl;
    ret = 0;
  }
  else
    pt.load(context, in_file);

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
  ifstream in_file(filename, std::ios::binary);
  if(!in_file) {
    cerr << "[ERRROR4] File opening failure  " << filename << endl;
    exit(1);
    ret = 0;
  }
  else
    ct.load(context, in_file);
    ret=0;
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



bool suffix_exist(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
