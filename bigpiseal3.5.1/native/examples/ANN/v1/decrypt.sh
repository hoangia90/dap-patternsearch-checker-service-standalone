#decrypt
resultPath=$1
# ex: result/l.ct
sample=$2
# ex: 40
keyDir=$3
# ex: keys/

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./ANN_decrypt_v1 "$resultPath" "$sample" "$keyDir"
time ${CURR_DIR}/ANN_decrypt_v1 "$resultPath" "$sample" "$keyDir"