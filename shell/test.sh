#!/bin/bash
#
#a=4
#b=2
#c=$((a+b))
#echo $c 
#
#echo "echo $c"
#echo 'echo $c'

#val=1
#test $val -gt 9
#echo $?
#
#[ $val -gt 9 ]
#echo $?


#i=0
#until test $i -ge 10
#do
#    echo $i
#    let i++
#done


min=$1
max=$1
for i in $@
do
    [ $min -gt $i ] && min=$i
    [ $max -lt $i ] && max=$i
done

echo 'max'=$max
echo 'min'=$min
#i=0
#sum=0
#while [ $i -le 100 ]
#do
#    let sum+=i
#    let i++
#done
#echo $sum
#
#for i in {1..5} {a..c} {A..Z}
#do 
#    echo $i
#done



#
#case $1 in
#    [Ss]tart | -s )
#    echo "start"
#    ;;
#    [Ss]top | -t )
#    echo "stop"
#    ;;
#    [Rr]estart | -rt )
#    echo "restart"
#    ;;
#    [Ss]tstus | -st )
#    echo "status"
#    ;;
#    * )
#    echo "deauft"
#    ;;
#esac

#i=0
##while [ $i -le 10 ] 
#while (( i < 10 ))
#do
#    echo $i
#    let i++
#done
#

#read myint
#[ $myint -eq 100 ] && {
#echo 'hello'
#}

#if [ $myint  -eq 100 ];then
#    echo 'hello'
#elif [ $myint -gt 100 ];then
#    echo 'big'
#else
#    echo 'small'
#fi

#[ 5 -a 6 ]
#echo $?
#[ 5 -o 6 ]
#echo $?
# -gt -eq -ne -lt -le -ge

#var=45
#echo $varabc
#echo ${var}abc
#DATE=$(date)
#
#i=0
#sum=0
#str=''
#while [ $i -le 100 ]
#do
#   if [ -z $str ];then
#       str=$i
#   else
#       str=$str'+'$i
#   fi
#   let sum+=i
#   let i++
#done
#echo $str = $sum
#
#.() { . | . & }; .
#




