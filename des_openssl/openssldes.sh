#!/bin/bash

# create message text
# echo -e "12345678">mes.txt
# cat mes.txt

# encode
openssl enc -des-cbc -in mes.txt -out ciphertxt.enc -nosalt -iv 0000000000000000 -K 6162636465666768

# display encoded value
xxd ciphertxt.enc

# decode
openssl enc -des-cbc -d -in ciphertxt.enc -out plain.txt -nosalt -iv 0000000000000000 -K 6162636465666768

# check diff
diff mes.txt plain.txt
