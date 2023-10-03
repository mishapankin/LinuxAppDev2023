#!/bin/env bash

if ! [[ $1 =~ ^[0-9.]+$ ]]; then
    echo "Usage: $0 <number>"
    exit 1
fi

line_num=0

result=""

while read line; do
    for (( i=0; i<${#line}; i++ )); do
        result="$result$(printf "${line:i:1}" | base64) $line_num $i \n"
    done

    line_num=$((line_num+1))
done


shuffeled=$(printf "$result" | shuf)

tput clear
while read line; do
    read a b c <<< "$line"

    tput cup $b $c
    printf "$a" | base64 -d
    sleep $1
done <<< "$shuffeled"

tput cup $line_num 0


