# Decrypt Result

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

###################### General - Begin ######################
resultPath=$1 # ex: result/l.ct
sample=$2 # ex: 40
keyDir=$3 # ex: keys/

time ${CURR_DIR}/similarityMatch_decrypt_result "$resultPath" "$sample" "$keyDir"
###################### General - End ########################