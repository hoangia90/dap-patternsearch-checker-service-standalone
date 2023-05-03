#ifndef _SEAL_API_H_
#define _SEAL_API_H_

/* includes */
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cassert>
#include <cstdint>
#include <boost/lexical_cast.hpp>
#include "seal/seal.h"

/* definitions */
struct encryptor_t {
  std::shared_ptr<seal::SEALContext>    context;
  seal::Encryptor                       *encr;
  seal::BatchEncoder                    *bcode;
  seal::IntegerEncoder                  *icode;
};

struct decryptor_t {
  std::shared_ptr<seal::SEALContext>    context;
  seal::Decryptor                       *decr;
  seal::BatchEncoder                    *bcode;
  seal::IntegerEncoder                  *icode;
};

struct evaluator_t {
  std::shared_ptr<seal::SEALContext>    context;
  seal::RelinKeys                       lk;
  seal::GaloisKeys                      gk;
  seal::Evaluator                       *eval;
};

/* prototypes */
/** for binary files management **/
int open_binary_file(std::ifstream& in_file, const std::string& filename);
int open_binary_file(std::ofstream& out_file, const std::string& filename);

/** for context management **/
int save_params(seal::EncryptionParameters &params, const std::string &filename);
int load_params(seal::EncryptionParameters &params, const std::string &filename);

void init_context(size_t poly_d, size_t p_modulus, std::shared_ptr<seal::SEALContext>& context);
void load_context(std::shared_ptr<seal::SEALContext>& context, const std::string& filename);
void print_context(std::shared_ptr<seal::SEALContext>& context);

/** for key management **/
int save_key(seal::PublicKey& k, const std::string& filename);
int save_key(seal::SecretKey& k, const std::string& filename);
int save_key(seal::RelinKeys& k, const std::string& filename);
int save_key(seal::GaloisKeys& k, const std::string& filename);
int load_key(std::shared_ptr<seal::SEALContext>& context, const std::string& filename, seal::PublicKey& k);
int load_key(std::shared_ptr<seal::SEALContext>& context, const std::string& filename, seal::SecretKey& k);
int load_key(std::shared_ptr<seal::SEALContext>& context, const std::string& filename, seal::RelinKeys& k);
void generate_keys(size_t poly_d, size_t p_modulus, bool seriablizable = false);
void batching_generate_keys(size_t poly_d, int bit_size, const std::string key_path, bool serializable = false);
void batching_generate_keys(size_t poly_d, std::vector<int> bit_sizes, std::uint64_t plain_modulus, std::string key_dir, bool serializable = false);

/** for homomorphic operators management **/
void init_operator(struct encryptor_t& op_st);
void init_operator(struct encryptor_t &op_st, const std::string& public_key_path);
void init_operator_batching(struct encryptor_t &op_st, const std::string& key_dir);
void init_operator(struct decryptor_t& op_st);
void init_operator(struct decryptor_t &op_st, const std::string& secret_key_path);
void init_operator_batching(struct decryptor_t &op_st, const std::string& key_dir);
void init_operator(struct evaluator_t& op_st);
void init_operator(struct evaluator_t& op_st, const std::string& relink_key_path);
void init_operator_batching(struct evaluator_t &op_st, const std::string &key_dir);
void delete_operator(struct encryptor_t& op_st);
void delete_operator_batching(struct encryptor_t& op_st);
void delete_operator(struct decryptor_t& op_st);
void delete_operator_batching(struct decryptor_t& op_st);
void delete_operator(struct evaluator_t& op_st);
void delete_operator_batching(struct evaluator_t& op_st);

/** for plaintexts and ciphertexts management **/
void init_plaintext(struct encryptor_t& op_st, int64_t plain, seal::Plaintext& pt);
void init_ciphertext(struct encryptor_t& op_st, int64_t plain, seal::Ciphertext& ct);
void init_ciphermatrix(struct encryptor_t &op_st, std::vector<int64_t> &plain_matrix, seal::Ciphertext &encrypted_matrix);
void decrypt_ciphertext(struct decryptor_t& op_st, seal::Ciphertext& ct);
std::int64_t decrypt_ciphertext_and_return_value(struct decryptor_t& op_st, seal::Ciphertext& ct);
std::vector<int64_t> decrypt_ciphermatrix(struct decryptor_t &op_st, seal::Ciphertext &ct);

int save_plaintext(seal::Plaintext& pt, const std::string& filename);
int save_ciphertext(seal::Ciphertext& ct, const std::string& filename);
int load_plaintext(std::shared_ptr<seal::SEALContext>& context, seal::Plaintext& pt, const std::string& filename);
int load_plaintext(struct evaluator_t& op_st, seal::Plaintext& pt, const std::string& filename);
int load_plaintext(struct decryptor_t& op_st, seal::Plaintext& pt, const std::string& filename);
int load_ciphertext(std::shared_ptr<seal::SEALContext>& context, seal::Ciphertext& ct, const std::string& filename);
int load_ciphertext(struct evaluator_t& op_st, seal::Ciphertext& ct, const std::string& filename);
int load_ciphertext(struct decryptor_t& op_st, seal::Ciphertext& ct, const std::string& filename);

#endif
