
{
  "targets": [
    {
      "target_name": "sqlitebridge",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "sqlite-bridge.cc", "sqlite3.c", "sqlite3.h" ],
      # "include_dirs": [
      #   "<!@(node -p \"require('node-addon-api').include\")"
      # ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS', 'SQLITE_ENABLE_JSON1' ],
    }
  ]
}