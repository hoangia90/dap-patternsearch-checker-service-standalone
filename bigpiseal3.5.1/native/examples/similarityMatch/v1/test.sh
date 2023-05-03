# Testing Script

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )


###################### Test 1 - Begin ######################
mkdir -p keys/
mkdir -p lcheck/
mkdir -p parent/
mkdir -p result/
# rm ls.txt

# Number of ciphertext data, eg: (0..99)
min=0
max=0 # max=101 or 1631

n_char=39 # Number of chars/words of a ciphertext, eg: 9

# Encrypted number range, eg: 2(1-bit), 10, 100, 255(8-bit), 1000 
# range=255
range=2 

sample=40 # sampling size

# Generate keys
${CURR_DIR}/similarityMatch_genkey keys/ # gen keys

# Get random data line
if [[ "$max" -ne 0 ]]
then
   line=$((RANDOM %max))
else
   line=0
fi

lcheck=""
# Generate data randomly
for i in $(seq $min $max)
do
   mkdir -p parent/l"$i"/
   echo "Created folder $i" 
   value=""
   for j in $(seq 0 $n_char)
   do
      value+="$((RANDOM %$range)) "
   done
   echo $value
   echo $value >> ls.txt
   # ./similarityMatch_encrypt "$value" "l" parent/l"$i"/ $sample keys/
   ${CURR_DIR}/similarityMatch_encrypt "$value" "l" parent/l"$i"/ $sample keys/
   if [[ "$line" -eq "$i" ]]
   then
      lcheck="$value"
   fi
done

echo "Pick up data to check: $lcheck"

${CURR_DIR}/similarityMatch_encrypt "$lcheck" "l" lcheck/ $sample keys/

# Evaluate 
value1="lcheck/l.ct "
value2=""
for i in $(seq 0 $max)
do
   value2+="parent/l${i}/l.ct "
done
value3="$value1$value2"
echo "$value3"

time ${CURR_DIR}/similarityMatch_evaluate $value3 "l" result/ $sample keys/

echo ""

${CURR_DIR}/similarityMatch_decrypt_1st_result result/l.ct $sample keys/

# rm -r keys/*
# rm -r lcheck/*
# rm -r parent/*
# rm -r result/*
# rm ls.txt
###################### Test 1 - End ########################





###################### Report - Begin ######################
# sim: (eval: 0.465s, 0.488s, 0.480s decrypt: 0.028s, 0.080s, 0.077s)
# seq: (eval: 0.xxx, 0.xxx, 0.xxx decrypt: 0.xxx, 0.xxx, 0.xxx)
# max=203
# (eval: 3.635s, 3.510s, 3.628s decrypt: 0.062s, 0.153s. 0.134s)
# seq: (eval: 0.xxx, 0.xxx, 0.xxx decrypt: 0.xxx, 0.xxx, 0.xxx)
# max=407
# (eval: 38.607s, 39.600s, 39.565s decrypt: 0.264s, 0.260s, 0.245s)
# seq: (eval: 0.xxx, 0.xxx, 0.xxx decrypt: 0.xxx, 0.xxx, 0.xxx)
# max=815
# (eval: x decrypt: x )
###################### Report - End ########################