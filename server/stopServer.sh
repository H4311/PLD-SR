#!/bin/bash

for line in $(cat pids); do
    kill "$line"
done
sudo service mysql stop
rm pids
