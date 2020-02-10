//index.js
const testAddon = require('./build/Release/hello.node');
console.log('addon',testAddon);
console.log('addon',testAddon.hello());

var query ="CREATE TABLE PRODUCT("+
"ID INT PRIMARY KEY     NOT NULL,"+
"NAME           TEXT    NOT NULL,"+
"AGE            INT     NOT NULL,"+
"ADDRESS        CHAR(50),"+
"SALARY         REAL );";

try {
    console.log('addon',testAddon.Select('test.db', query));
} catch (e) {
    console.log('-----');
    console.log(e);
}
module.exports = testAddon;