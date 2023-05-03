#!/bin/bash
#
#    2020 CEA LIST.
declare -r ERROR_NUMBER_PARAM=1
declare -r ERROR_KEY_NOT_FOUND=3
declare -r KEYGEN_NOT_PERFORMED=4
#/opt/seal/native/bin
# /opt/pki/seal/
# /opt/pki/seal/natives/examples/generic
CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# params  executable seal_generic_encrypt
# value 
# path_to_key existing key pk encrypt 

if [ "$#" -ne 1 ]; then
    echo "You must enter exactly 1 command line arguments"
    # display help if empty
    echo " path to sk ,  "
    exit $ERROR_NUMBER_PARAM
fi


path_to_key=$1

# encryption
echo "key generation"
${CURR_DIR}/generic_genkey     $path_to_key  
# recuperate result
if [ "$?" == "0" ]; then
    echo ok done
else
  echo KEYGEN_NOT_PERFORMED 
  exit 4
fi 

exit
