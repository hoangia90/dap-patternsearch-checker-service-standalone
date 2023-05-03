# Evaluate

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

###################### General - Begin ######################
licensePath=$1 # ex: lcheck/l.ct
licensePathList=${@: 2:$#-5} # ex: parent/l0/l.ct parent/l1/l.ct parent/l2/l.ct parent/l3/l.ct parent/l4/l.ct parent/l5/l.ct parent/l6/l.ct parent/l7/l.ct parent/l8/l.ct parent/l9/l.ct
outputFileName=${@: -4:1} # ex: "l" (extension will be .ct)
outputDir=${@: -3:1} # ex: result/
sample=${@: -2:1} # ex: 40
KeyDir=${@: -1} # ex: keys/

time ${CURR_DIR}/similarityMatch_evaluate "$licensePath" $licensePathList "$outputFileName" "$outputDir" "$sample" "$KeyDir"
###################### General - End ########################