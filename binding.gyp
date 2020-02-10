
{
  "targets": [
    {
      "target_name": "hello",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "hej.cc", "sqlite3.c", "sqlite3.h" ],
      # "include_dirs": [
      #   "<!@(node -p \"require('node-addon-api').include\")"
      # ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}