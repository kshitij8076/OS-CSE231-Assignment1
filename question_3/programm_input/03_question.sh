#!/bin/bash

#make directory of result if not present 
if [ ! -d "Result" ]
then
  mkdir "Result"
fi

#read filee 
while IFS=' ' read -r line
do  
  read -r x y ops <<< $line

#use switch case   
  case "$ops" in
    "xor")
      result=$(echo "Result of xor $x $y : $((x ^ y))")
      ;;
    "product")
      result=$(echo "Result of product $x $y : $((x * y)) ")
      ;;
    "compare")
      if [ "$x" -gt "$y" ]
      then
        result=$(echo "result of compare $x $y : $x ")
      elif [ "$y" -gt "$x" ]
      then
      	result=$(echo "result of compare $x $y : $y ")      	        
      else      	
      	result=$(echo "both are equal $x $y" )
      	  
      fi
      ;;
      *)
       result=$(echo "this is invalid operation $ops or may be invalid number $x $y")
       echo "this is invalid operation $ops or may be invalid number $x $y" 
  esac
  
  echo "$result" >> "Result/output.txt"

done < "input.txt"

echo "result store "

