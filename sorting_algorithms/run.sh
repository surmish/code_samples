#! /bin/bash
if make; then
    ./sort --all --vector_size 10;    printf "\n";
    ./sort --all --vector_size 100;   printf "\n";
    ./sort --all --vector_size 1000;  printf "\n";
    ./sort --all --vector_size 10000; printf "\n";
else
   echo "Compile error";
fi 
