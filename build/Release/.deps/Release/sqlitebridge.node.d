cmd_Release/sqlitebridge.node := c++ -bundle -undefined dynamic_lookup -Wl,-no_pie -Wl,-search_paths_first -mmacosx-version-min=10.10 -arch x86_64 -L./Release -stdlib=libc++  -o Release/sqlitebridge.node Release/obj.target/sqlitebridge/sqlite-bridge.o Release/obj.target/sqlitebridge/sqlite3.o 