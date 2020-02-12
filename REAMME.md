## NodeJs Sqlite Addons

* Develop this to use in my project

### Install npm modules for Development

* npm install -g node-addon-api@^1.7.1
* npm install -g node-gyp@6.0.1"

### Generate and Build addon

* Type in terminal root map:
* Will build the Addon in Build/Release/< addon-name >.node

```

node-gyp build -Wunused-result

```

* The build can then be import to your node js project:

```

const testAddon = require('./build/Release/< addon-name >.node');

```

### Reference

* [NodeJs Addon - Create and Build addon](https://nodejs.org/api/addons.html#addons_c_addons)
* [SQLite Amalgamation - sqlite3.cc sqlite3.h](https://www.sqlite.org/amalgamation.html)