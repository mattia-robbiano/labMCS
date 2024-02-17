#!/bin/bash
rm fileInput
for planet in $*
do
    grep -A11 "GMs\[]" effemeridi.h | grep -v "GMs\[]" | grep "$planet" | awk '{print $1}'>>fileInput
    grep -A6 "// $planet" effemeridi.h | grep -v "// $planet" >> fileInput
done
