#!/bin/bash
#
#    2020 CEA LIST.
declare -r ERROR_NUMBER_PARAM=1
declare -r ERROR_VALUE_PARAM=2
declare -r ERROR_KEY_NOT_FOUND=3
declare -r ERRROR_ENCRYPT_DECRYPT_NOT_PERFORMED=4
declare -r ERROR_FILE_ZIP_NOTFOUND=5
#/opt/seal/native/bin
# /opt/pki/seal/
# /opt/pki/seal/natives/examples/generic
CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# params  executable seal_generic_encrypt
# value 
# size_bit 1 63 , limited to 63 bits Seal  -ou 2-**63signed  max=x value to test 
# signed 0  unsigned 1 signed 
# path_to_key existing key pk encrypt 
# path_storage 


if [ "$#" -ne 6 ]; then
    echo "You must enter exactly 6 command line arguments"
    # display help if empty
    echo "value , size bit <1..63>, signed <0,1> , path to sk , path to storage, prefix "
    exit $ERROR_NUMBER_PARAM
fi

[ -n "$1" ] && [ "$1" -eq "$1" ] 2>/dev/null
if [ $? -ne 0 ]; then
   echo $1 is not number
   exit 2
fi
[ -n "$2" ] && [ "$2" -eq "$2" ] 2>/dev/null
if [ $? -ne 0 ]; 
   then
      echo $2 is not number
      exit 2
   else 
       if [ "$2" -ge 1 -a "$2" -le 63 ]; 
       then echo "size input Ok"
       else 
		echo "ERROR_SIZING VALUE " $2 ",size bit is  1..63"
		exit 2
    fi
fi


value=$1
size_bit=$2

case $3 in
    ''|*[!0-1]*) echo bad signed value $3 , only 0 or 1; exit 2;;
    *) echo Signed value OK;;
esac
Signed=$3




path_to_key=$4
if [[ "$path_to_key" == */ ]]
then
    file="$path_to_key"bfv.pk 
else
    file="$path_to_key"/bfv.pk 
fi

if test -f "$file"; then
    echo "$file exist"
else 
    echo "ERROR_KEY_NOT_FOUND   " $4/bfv.pk" not found" 
    exit 3       
fi



directory=$5
if  [  -d "$directory" ]
then
    echo "OK"       
else 
    echo " Path to storage directory " $5 " not found" 
    mkdir $directory
    #
    echo " path to storage created"
        
fi


path_storage=$5
prefix=$6

defaut_coherence_test_value_sizebit_seal()
{
    # define max value  equal 2*2  ..*2 size_bit time
    ((X=(2**$size_bit)-1)); echo "max value"  $X
    ((Y=(2**63)-1)); echo "max value 2**63 -1"  $Y
#    let "maxvalue=1"    
#    for i in $(seq $1 $size_bit)
#    do
#        let "maxvalue=maxvalue*2"
#    done
    if [ "$value" -gt "$Y" ]; then
        echo " value  to high or equal",  $value, " to max value" $Y
        exit 2
    fi 
}



defaut_coherence_test_value_sizebit_seal

# encryption
echo "encryption"
${CURR_DIR}/generic_encrypt $value $prefix    $path_to_key $path_storage 
# recuperate result
if [ "$?" == "0" ]; then
    echo ok done
else
  echo ENCRYPTION_NOT_PERFORMED 
  exit 4
fi 



exit
