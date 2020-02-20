## NodeJs Sqlite Addons

* Develop this to use in my project

### Install npm modules for Development

* npm install -g node-addon-api@^1.7.1
* npm install -g node-gyp@6.0.1"

### File / Map Description

```
    |- /Build           // Generated Addon build
    |- sqlite3.h        // Lib
    |- sqlite3.c        // Lib
    |- config.gypi      // Configure file to build addon
    |- sqlite-bridge.cc // Addon NodeJS <-> Sqlite
    |- hello-world.cc   // Hello world addon example
    |- run              // Batch script that Compiles & Excutes sqlite3 test.c
    |- a.out            // Output from "Run script"
    |- test.db          // Sqlite db create from "Run script"
    |- test.js          // Generated and testing the Addon build
    |- README.md        // Description

```

### Generate and Build addon

* Type in terminal root map:

```
/* Will build the Addon in Build/Release/< addon-name >.node */
node-gyp build

```

* The build can then be imported to your node js project:

```

const testAddon = require('./build/Release/< addon-name >.node');

```

### Reference

* [NodeJs Addon - Create and Build addon](https://nodejs.org/api/addons.html#addons_c_addons)
* [SQLite Amalgamation - sqlite3.cc sqlite3.h](https://www.sqlite.org/amalgamation.html)