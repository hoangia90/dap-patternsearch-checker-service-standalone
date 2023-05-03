#!/bin/bash

#
#    2020 CEA LIST. 

declare -r ERROR_NUMBER_PARAM=1
declare -r ERROR_VALUE_PARAM=2
declare -r ERROR_KEY_NOT_FOUND=3
declare -r ERRROR_ENCRYPT_DECRYPT_NOT_PERFORMED=4
declare -r ERROR_FILE_ZIP_NOT FOUND=5
CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# /opt/seal/native/bin
# /opt/pki/seal/
# /opt/pki/seal/natives/examples/generic
# seal preparation executable seal_generic_decrypt
# code genéré pour 63bits signés. 
# params  
# 1 size_bit 1 63
# 2 signed 0  unsigned 1 signed 
# 3 path_to_key .pk
# 4 path_to_storage  
# 5 prefix

if [ "$#" -ne 5 ]; then
    echo "You must enter exactly 5 command line arguments"
     echo "size bit <1..63>, signed <0,1> , path to sk , path to storage, prefix "
    exit 1
fi

# size bit  1 63 
case $1 in
    ''|*[!0-9]*) echo only numeric size 1..63;;
    *) echo  numeric 
    if [ "$1" -ge 1 -a "$1" -le 63 ]; then echo "size input Ok"
    else 
		echo echo "ERROR_SIZING VALUE " $1 ",size bit is  1..63"
		exit 2
    fi
    ;;
esac
size_bit=$1
# signed  0 or 1
case $2 in
    ''|*[!0-1]*) echo bad only 0 or 1 for signed value; exit 2;;
    *) echo Signed value OK;;
esac
signed=$2

# path to sk an key existence
#  if not found error
path_to_key=$3
# si $3 contient  .sk  à la fin, alors c'est correct sinon 
# si cest directory alors ajouter bfv.sk a la fin
# si c'est un fichier, verifier l'existence

if [[ "$path_to_key" == */ ]]
then
    file="$path_to_key"bfv.sk 
else
    file="$path_to_key"/bfv.sk 
fi

if test -f "$file"; then
    echo "$file exist"
else 
    echo " ERROR_KEY_NOT_FOUND " $3/bfv.sk " not found" $file
    exit  3        
fi




# path to result
path_to_storage=$4
if [[ "$path_to_storage" == */ ]]
then
    file="$path_to_storage" 
else
    file="$path_to_storage"/
fi

prefix=$5
if  [  -d "$path_to_storage" ]
then
    echo 1
else 
    echo 3
    #~ extract_zip 
fi

${CURR_DIR}/generic_decrypt $prefix  $path_to_key  $path_to_storage 
# ./generic_decrypt ct2  /home/bigpi/ storage/
# recuperate result
if [ "$?" == "0" ]; then
    echo ok done
else
  echo DECRYPTION_NOT_PERFORMED 
  exit 4
fi 
