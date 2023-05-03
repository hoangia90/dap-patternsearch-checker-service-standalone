#gen key 
keyDir=$1
# ex: keys/

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./ANN_genkey_v1 "$keyDir"
time ${CURR_DIR}/ANN_genkey_v1 "$keyDir"