#gen key 
keyDir=$1
# ex: keys/

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./patternSearch_genkey_v2 "$keyDir"
time ${CURR_DIR}/patternSearch_genkey_v2 "$keyDir"