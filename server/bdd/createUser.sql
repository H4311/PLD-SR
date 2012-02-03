USE pld;

CREATE USER 'rithm' IDENTIFIED BY 'rithm';
GRANT USAGE ON * . * TO 'rithm' IDENTIFIED BY 'rithm'; 
GRANT ALL PRIVILEGES ON pld.*   TO 'rithm';
