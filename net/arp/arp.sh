#!/bin/bash

head='192.168.1'
i=1
count=0
while [ $i -le 254 ]
do
    if [ $count -gt 20 ];then
        count=0
        sleep 1
    fi
    ping -c 1 "${head}"".$i" &
    let i++
    let count++
done
wait
echo "#########################################################"
arp -a | grep -v 'incomplete'
echo "#########################################################"

