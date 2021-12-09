#Q2:Calculate factorial of a supplied number

#Input the numnber
echo "============ Factorial of a supplied number==================="
echo "Write the magical number"
read n

#looping
fact=1
i1=$n

# For removing decimal points + zeros
i1=$(echo "$i1"| grep -oE "^[+-]?[0-9]+")

while [ $i1 -ge 1 ]
do
        fact=`expr $fact \* $i1`    #multiplications
        i1=$(( $i1-1 ))             #decrementing $i1
done

echo "The factorial of $n is $fact."
