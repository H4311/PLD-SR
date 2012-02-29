#!/bin/sh

mysql -u root -p < creationDB.sql
mysql -u root -p < createUser.sql
mysql -u rithm -p pld < createTables.sql
mysql -u rithm -p pld < insertValues.sql
