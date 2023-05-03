# Generate Keys 

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

###################### General - Begin ######################
keyDir=$1 # ex: keys/

time ${CURR_DIR}/similarityMatch_genkey "$keyDir"
###################### General - End ########################