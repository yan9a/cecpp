#!/bin/bash

# create message text
# echo -e "12345678">mes.txt
# cat mes.txt

# generate key pair
echo "Genpkey ..."
openssl genpkey -algorithm RSA -out private_key.pem

echo "Pubkey ..."
openssl rsa -pubout -in private_key.pem -out public_key.pem

# encrypt
echo "Encrypt ..."
openssl rsautl -encrypt -in mes.txt -out ciphertext.enc -inkey public_key.pem -pubin

# display encoded value
echo "Display ciphertext ..."
xxd ciphertext.enc

# decrypt
echo "Decrypt ..."
openssl rsautl -decrypt -in ciphertext.enc -out plain.txt -inkey private_key.pem

# check diff
echo "Check ..."
diff mes.txt plain.txt
