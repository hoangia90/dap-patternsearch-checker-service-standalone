# Encrypt Data

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

###################### General - Begin ######################
licenseNo=$1 # ex: "23 65 78 127 255" (en ASCII)
outputFileName=$2 # ex: "l" (extension will be .ct)
outputDir=$3 # ex: lcheck/
sample=$4 # ex: 40
keyDir=$5 # ex: keys/

time ${CURR_DIR}/similarityMatch_encrypt "$licenseNo" "$outputFileName" "$outputDir" "$sample" "$keyDir"
###################### General - End ########################