#Q3: Triangle
#number input
echo "Input the number of the rows"
read rows

#looping for arbitrary rows number triangle 
for((i=1;i<=rows;i++))
do
        for((j=rows-i+1;j>=1;j--))
        do
                echo -n " "
        done
        for((k=1;k<=i;k++))
        do
                echo -n "$i "
        done
        echo
done

#looping for same number of dot triangle
for((i=1;i<=rows;i++))
do
        for((j=rows-i+1;j>=1;j--))
        do
                echo -n " "
        done
        for((k=1;k<=i;k++))
        do
                echo -n ". "
        done
        echo
done

