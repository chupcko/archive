#!/bin/sh

ECHO=/bin/echo

show()
{
  ${ECHO} -ne \\033[${1}m\\033[${2}m"${3}"\\033[0m
}

for bc in $(seq 40 47)
do
  for fc in $(seq 30 37)
  do
    show ${bc} ${fc} "  ${bc}-${fc} "
    echo -n ' '
  done
  echo
  for fc in $(seq 90 97)
  do
    show ${bc} ${fc} "  ${bc}-${fc} "
    echo -n ' '
  done
  echo
done
for bc in $(seq 100 107)
do
  for fc in $(seq 30 37)
  do
    show ${bc} ${fc} " ${bc}-${fc} "
    echo -n ' '
  done
  echo
  for fc in $(seq 90 97)
  do
    show ${bc} ${fc} " ${bc}-${fc} "
    echo -n ' '
  done
  echo
done
