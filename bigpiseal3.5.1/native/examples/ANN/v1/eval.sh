# evaluate
licensePath=$1
# ex: lcheck/l.ct
licensePathList=${@: 2:$#-5}
# licensePathList="${@:2:102}"
# for var in "${@: 2:$#-7}"
# do
#     echo "$var"
# done
# ex: parent/l0/l.ct parent/l1/l.ct parent/l2/l.ct parent/l3/l.ct parent/l4/l.ct parent/l5/l.ct parent/l6/l.ct parent/l7/l.ct parent/l8/l.ct parent/l9/l.ct
filename=${@: -4:1}
# ex: "l" (extension will be .ct)
outputDir=${@: -3:1}
# ex: result/
sample=${@: -2:1}
# ex: 40
KeyDir=${@: -1}
# ex: keys/
# linkingKeyPath=${@: -3:1}
# # ex: ckks.lk
# galoisKeyPath=${@: -2:1}
# # ex: ckks.gk
# publicKeyPath=${@: -1}
# # ex: ckks.pk

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# time ./ANN_evaluate_v1 "$licensePath" $licensePathList "$filename" "$outputDir" "$sample" "$linkingKeyPath" "$galoisKeyPath" "$publicKeyPath"
# time ./ANN_evaluate_v1 "$licensePath" $licensePathList "$filename" "$outputDir" "$sample" "$KeyDir"
time ${CURR_DIR}/ANN_evaluate_v1 "$licensePath" $licensePathList "$filename" "$outputDir" "$sample" "$KeyDir"