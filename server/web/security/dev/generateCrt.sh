#!/bin/sh

rm -f `ls * | grep -v "gen"`
openssl genrsa 1024 > server.key
chmod 400 server.key
openssl req -new -key server.key > server.csr < genInput
openssl genrsa -des3 1024 > ca.key
openssl req -new -x509 -days 365 -key ca.key > ca.crt < genInput
openssl x509 -req -in server.csr -out server.crt -CA ca.crt -CAkey ca.key -CAcreateserial -CAserial ca.srl
