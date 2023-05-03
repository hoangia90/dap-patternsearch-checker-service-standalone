#include <sys/stat.h>
#include "multiply.h"

using namespace std;
using namespace seal;

inline bool exists_file (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char **argv)
{
  if(argc != 5) {
    cout << "ct1.ct x ct2.ct = ct3.ct"  << endl;
    cout << "[ERROR] please enter 3 ciphertext /path/to/ct1.ct /path/to/ct2.ct /path/to/result.ct full/path/to/publickey" << endl;
    //  ../generic_evaluate /path/to/ct1.ct /path/to/ct2.ct /path/to/result.ct /home/bigpi/path/to/pubKey
    return EXIT_FAILURE;
  }
  
  struct evaluator_t eval;
  string Ct1 = argv[1];
  string Ct2 = argv[2];
  string Ct3 = argv[3];
  string pathK1 = argv[4];
  string pathK ="";

  if (exists_file(Ct1) == false || exists_file(Ct2) == false) 
  {
    cout << "[ERROR] please enter 2 first ciphertext input /path/to/ct1.ct /path/to/ct2.ct" << endl;
    return EXIT_FAILURE;
  }

/*    if (suffix_exist(Ct3, "/") == false) {
cout << "[ERROR] please enter 3rd parameter /path/to/result/name.ct/you/wish" << endl;
      return EXIT_FAILURE;
  } */


  if (suffix_exist(pathK1, "/")) 
  {
      pathK =pathK1;
  }
  else
  {
    pathK .append(pathK1);
    pathK .append("/");
  }

  init_operator(2048, 256, eval,pathK);

  Ciphertext ct1, ct2, ct3;
  string prefix("");
  load_ciphertext(eval, ct1, Ct1);
  load_ciphertext(eval, ct2, Ct2);
  multiply_ciphertext(eval, ct1, ct2, ct3);

  save_ciphertext(ct3, Ct3);

  delete_operator(eval);
    return 0;
}



