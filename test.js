const testAddon = require('./build/Release/sqlitebridge.node');

var dataBase = "SQLITEDATABASE", query;

/**
 * List all functions 
 *
 * @return   
 * sqliteBridge {
 *   Version: [Function: Version],
 *   Execute: [Function: Execute],
 *   Select: [Function: Select]
 * }
 */
console.log('sqliteBridge', testAddon);


/**
 * Show Version
 * @return
 * Version Tomatkungen v1.0
 */
console.log('Version', testAddon.Version())

/**
 * CRUD - Create, Read, Update, Delete
 */

 /**
  * Create
  */
query = "CREATE TABLE PRODUCT("+
    "ID INT PRIMARY KEY     NOT NULL," +
    "NAME           TEXT    NOT NULL," +
    "AGE            INT     NOT NULL," +
    "ADDRESS        CHAR(50)," +
    "SALARY         REAL );";

try {
    console.log('Create - ', testAddon.Execute(dataBase, query)); //  Execute successfully
} catch (e) {
    console.log('> Error:');
    console.log(e); // table PRODUCT already exist
}

/**
 * Insert
 */
query = "INSERT INTO PRODUCT "+
        "(ID, NAME, AGE, ADDRESS, SALARY)" +
        "VALUES " +
        "(1, 'TOMAT', 12, 'TOMATGATAN', 13)";

try {
    console.log('INSERT - ', testAddon.Execute(dataBase, query)); // Execute successfully
} catch (e) {
    console.log(e); // NOT NULL constraint failed: PRODUCT.ID
}
    
/**
 * Select
 */
query ="SELECT * FROM PRODUCT";

try {
    console.log('SELECT - ', testAddon.Select(dataBase, query));   // { ID: 1, NAME: 'TOMAT', AGE: 12, ADDRESS: 'TOMATGATAN', SALARY: 13 }
} catch (e) {
    console.log('> Error:');
    console.log(e);
}

/**
 * Delete
 */
query = "DELETE FROM PRODUCT " +
        "WHERE ID=1";

try {
    console.log('DELETE - ', testAddon.Execute(dataBase, query)); // Execute successfully
} catch (e) {
    console.log('> Error:'); // near "ID": syntax error
    console.log(e);
}

/**
 * Select
 */
query ="SELECT * FROM PRODUCT";

try {
    console.log('SELECT - ', testAddon.Select(dataBase, query));   // []
} catch (e) {
    console.log('> Error:');
    console.log(e);
}

module.exports = testAddon;