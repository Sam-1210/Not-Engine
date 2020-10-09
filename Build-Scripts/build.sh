#!/bin/bash
set echo off
clear
printf "~~~~~~~~~~~~~~~~~ Not Engine Project Setup ~~~~~~~~~~~~~~~~~\n"
printf "\n\t\tChoose Your Build Option :\n\t\t\t1. gmake\n\t\t\t2. gmake2\n\t\t\t3. codelite\n\t\t\t4. quit\n\n"
printf "Enter Your Choice (1/2/3/4)\t:\t"
read choice
cd ../
printf "\n*******Build Log*********\n"
if [[ $choice == 1 ]]
then
    echo Build System Set For gmake, Calling Premake
    ./Utils/bin/Premake/premake5 gmake
elif [[ $choice == 2 ]]
then
    echo Build System Set For gmake2, Calling Premake
    ./Utils/bin/Premake/premake5 gmake2
elif [[ $choice == 3 ]]
then
    echo Build System Set For codelite, Calling Premake
    ./Utils/bin/Premake/premake5 codelite
elif [[ $choice == 4 ]]
then
    echo Exiting...
else
    echo Wrong Choice, Exiting...
fi
printf "\n**************************\n"
printf "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
exit