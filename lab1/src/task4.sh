#!/bin/bash
i=0
sum=0
IFS=" "
for number in $@ ; do
  # echo $number
  # break;
  ((sum+=number))
  ((i++))
done
average=`echo "$sum / $i" | bc -l`
echo "Got $i arguments"
echo "The total is $sum"
printf "An average is %.2f\n" $average