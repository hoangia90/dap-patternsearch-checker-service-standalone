#encrypt
licenseNo=$1
# ex: "23 65 78 127 255" (en ASCII)
filename=$2
# ex: "l" (extension will be .ct)
outputDir=$3
# ex: lcheck/
sample=$4
# ex: 40
keyDir=$5
# ex: keys/

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./patternSearch_encrypt_v2 "$licenseNo" "$filename" "$outputDir" "$sample" "$keyDir"
time ${CURR_DIR}/patternSearch_encrypt_v2 "$licenseNo" "$filename" "$outputDir" "$sample" "$keyDir"