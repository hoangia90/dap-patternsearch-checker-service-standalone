mkdir -p keys/
mkdir -p lcheck/
mkdir -p parent/
mkdir -p result/
# rm ls.txt


# bash data_creating.sh 0 99 9 1000

# Number of driving licenses, eg: (0..99)
min=0
max=101
# max=1631
# max=101
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

# Number of chars/words of a driving license, eg: 9
n_char=39

# Encrypted number range, eg: 10, 100, 1000 for 1 2 3 4 digits
range=255
# (8-bit)

# sampling size
sample=40

CURR_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Note 



# gen keys
# ./patternSearch_genkey_v2 keys/
${CURR_DIR}/patternSearch_genkey_v2 keys/

line=$((RANDOM %max))
lcheck=""
# gen data
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
   # ./patternSearch_encrypt_v2 "$value" "l" parent/l"$i"/ $sample keys/
   ${CURR_DIR}/patternSearch_encrypt_v2 "$value" "l" parent/l"$i"/ $sample keys/

   if [[ "$line" -eq "$i" ]]
   then
      lcheck="$value"
   fi

done



# get random lc
# lcheck=$(sed -n "$((RANDOM %9){p;q}" ls.txt)
# line=$((RANDOM %max))
# lcheck="$(sed -n "${line}{p;q}" ls.txt)"
echo "Pick up license to check: $lcheck"
# ./patternSearch_encrypt_v2 "$lcheck" "l" lcheck/ $sample keys/
${CURR_DIR}/patternSearch_encrypt_v2 "$lcheck" "l" lcheck/ $sample keys/
# ./patternSearch_encrypt "47 25 76 23 30 21 1 47 88 3" "a" keys/bfv.pk lcheck/




# eval 
value1="lcheck/l.ct "


value2=""
for i in $(seq 0 $max)
do
   value2+="parent/l${i}/l.ct "
done

# value2="${value1} ${value2}"
value3="$value1$value2"
echo "$value3"

# time ./patternSearch_evaluate_v2 $value3 "l" result/ $sample keys/
# ./patternSearch_evaluate_v2 $value3 "l" result/ $sample keys/
time ${CURR_DIR}/patternSearch_evaluate_v2 $value3 "l" result/ $sample keys/

echo ""

# time ./patternSearch_decrypt_result_v2 result/l.ct $sample keys/
# ./patternSearch_decrypt_result_v2 result/l.ct $sample keys/
${CURR_DIR}/patternSearch_decrypt_result_v2 result/l.ct $sample keys/


# rm -r keys/*
# rm -r lcheck/*
# rm -r parent/*
# rm -r result/*
# rm ls.txt
