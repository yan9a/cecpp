#!/bin/bash

# create message text
echo -e "12345678">mes.txt
cat mes.txt

# generate key pair
echo "Genpkey ..."
# openssl genpkey -algorithm RSA -out private_key.pem
openssl genrsa -3 -out private_key.pem 1024

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

# print mod and exp from public key
openssl rsa -pubin -in public_key.pem -text -noout > modexp.txt
cat modexp.txt

# from private key
openssl rsa -in private.key -text > pkval.txt
cat pkval.txt
