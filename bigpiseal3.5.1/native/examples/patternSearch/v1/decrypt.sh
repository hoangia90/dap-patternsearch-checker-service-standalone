#decrypt
resultPath=$1
# ex: result/l.ct
sample=$2
# ex: 40
keyDir=$3
# ex: keys/

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./patternSearch_decrypt_v2 "$resultPath" "$sample" "$keyDir"
time ${CURR_DIR}/patternSearch_decrypt_v2 "$resultPath" "$sample" "$keyDir"