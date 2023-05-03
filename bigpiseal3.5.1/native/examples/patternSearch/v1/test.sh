# mkdir -p lcheck/
# mkdir -p parent/
# mkdir -p result/
# # rm ls.txt


# # bash data_creating.sh 0 99 9 1000

# # Number of driving licenses, eg: (0..99)
# min=0
# max=5

# # Number of chars/words of a driving license, eg: 9
# n_char=7

# # Encrypted number range, eg: 10, 100, 1000 for 1 2 3 4 digits
# range=128
# # (8-bit)





# # gen keys
# ./patternSearch_genkey 

# line=$((RANDOM %max))
# lcheck=""
# # gen data
# for i in $(seq $min $max)
# do
#    mkdir -p parent/l"$i"/
#    echo "Created folder $i"
      
#    value=""
#    for j in $(seq 0 $n_char)
#    do
#       value+="$((RANDOM %$range)) "
#    done

#    echo $value
#    echo $value >> ls.txt
#    ./patternSearch_encrypt "$value" "a" bfv.pk parent/l"$i"/

#    if [[ "$line" -eq "$i" ]]
#    then
#       lcheck="$value"
#    fi

# done



# # get random lc
# # lcheck=$(sed -n "$((RANDOM %9){p;q}" ls.txt)
# # line=$((RANDOM %max))
# # lcheck="$(sed -n "${line}{p;q}" ls.txt)"
# echo "Pick up license to check: $lcheck"
# ./patternSearch_encrypt "$lcheck" "a" bfv.pk lcheck/
# # ./patternSearch_encrypt "47 25 76 23 30 21 1 47 88 3" "a" bfv.pk lcheck/




# # eval 
# value1=""
# for i in $(seq 0 $n_char)
# do
#    value1+="lcheck/a_${i}.ct "
# done

# value1="$(($n_char+1)) ${value1}"

# # v=$(($n_char+1))
# # echo $v

# value2=""
# for i in $(seq 0 $max)
# do
#    value2="${value2} $(($n_char+1)) "
#    for j in $(seq 0 $n_char)
#    do
#       value2+="parent/l${i}/a_${j}.ct "
#    done

#    # value2="${value2} $(($n_char+1))"
# done

# # value2="${value1} ${value2}"
# value3="$value1$value2"
# echo "$value3"

# ./patternSearch_evaluate "a" $value3 "a" result/ bfv.lk


# ./patternSearch_decrypt result/a.ct bfv.sk



# rm -r lcheck/*
# rm -r parent/*
# rm -r result/*








# # ./patternSearch_evaluate "a" 10 lcheck/a_0.ct lcheck/a_1.ct lcheck/a_2.ct lcheck/a_3.ct lcheck/a_4.ct lcheck/a_5.ct lcheck/a_6.ct lcheck/a_7.ct lcheck/a_8.ct lcheck/a_9.ct 10 parent/l0/a_0.ct parent/l0/a_1.ct parent/l0/a_2.ct parent/l0/a_3.ct parent/l0/a_4.ct parent/l0/a_5.ct parent/l0/a_6.ct parent/l0/a_7.ct parent/l0/a_8.ct parent/l0/a_9.ct 10 parent/l1/a_0.ct parent/l1/a_1.ct parent/l1/a_2.ct parent/l1/a_3.ct parent/l1/a_4.ct parent/l1/a_5.ct parent/l1/a_6.ct parent/l1/a_7.ct parent/l1/a_8.ct parent/l1/a_9.ct 10 parent/l2/a_0.ct parent/l2/a_1.ct parent/l2/a_2.ct parent/l2/a_3.ct parent/l2/a_4.ct parent/l2/a_5.ct parent/l2/a_6.ct parent/l2/a_7.ct parent/l2/a_8.ct parent/l2/a_9.ct 10 parent/l3/a_0.ct parent/l3/a_1.ct parent/l3/a_2.ct parent/l3/a_3.ct parent/l3/a_4.ct parent/l3/a_5.ct parent/l3/a_6.ct parent/l3/a_7.ct parent/l3/a_8.ct parent/l3/a_9.ct 10 parent/l4/a_0.ct parent/l4/a_1.ct parent/l4/a_2.ct parent/l4/a_3.ct parent/l4/a_4.ct parent/l4/a_5.ct parent/l4/a_6.ct parent/l4/a_7.ct parent/l4/a_8.ct parent/l4/a_9.ct 10 parent/l5/a_0.ct parent/l5/a_1.ct parent/l5/a_2.ct parent/l5/a_3.ct parent/l5/a_4.ct parent/l5/a_5.ct parent/l5/a_6.ct parent/l5/a_7.ct parent/l5/a_8.ct parent/l5/a_9.ct 10 parent/l6/a_0.ct parent/l6/a_1.ct parent/l6/a_2.ct parent/l6/a_3.ct parent/l6/a_4.ct parent/l6/a_5.ct parent/l6/a_6.ct parent/l6/a_7.ct parent/l6/a_8.ct parent/l6/a_9.ct 10 parent/l7/a_0.ct parent/l7/a_1.ct parent/l7/a_2.ct parent/l7/a_3.ct parent/l7/a_4.ct parent/l7/a_5.ct parent/l7/a_6.ct parent/l7/a_7.ct parent/l7/a_8.ct parent/l7/a_9.ct 10 parent/l8/a_0.ct parent/l8/a_1.ct parent/l8/a_2.ct parent/l8/a_3.ct parent/l8/a_4.ct parent/l8/a_5.ct parent/l8/a_6.ct parent/l8/a_7.ct parent/l8/a_8.ct parent/l8/a_9.ct 10 parent/l9/a_0.ct parent/l9/a_1.ct parent/l9/a_2.ct parent/l9/a_3.ct parent/l9/a_4.ct parent/l9/a_5.ct parent/l9/a_6.ct parent/l9/a_7.ct parent/l9/a_8.ct parent/l9/a_9.ct "a" result/ key/bfv.lk



# # ./patternSearch_encrypt "$lc1" "a" bfv.pk lcheck/

# #eval
# # ./patternSearch_evaluate "a" lcheck/ parent/ "a" result/ bfv.lk 

# #decrypt
# # ./patternSearch_decrypt "a" bfv.sk result/parent/



# #example

# # lc1=$1;
# # lc2=$2;

# # mkdir -p l1/;
# # mkdir -p l2/;
# # mkdir -p result/;

# # ./patternSearch_genkey 
# # ./patternSearch_encrypt "$lc1" "a" bfv.pk l1/
# # ./patternSearch_encrypt "$lc2" "a" bfv.pk l2/
# # ./patternSearch_evaluate "a" l1/ "a" l2/ "a" result/ bfv.lk 
# # ./patternSearch_decrypt "a" bfv.sk result/

# # rm l1/*;
# # rm l2/*;
# # rm result/*;