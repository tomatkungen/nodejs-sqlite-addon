
#include <node.h>
#include <node_buffer.h>
#include <sqlite3.h>

using namespace v8;

namespace hi {

  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::NewStringType;
  using v8::Object;
  using v8::String;
  using v8::Value;
  using v8::Exception;
  using v8::Value;
  using v8::Number;
  using v8::Null;

  void Version(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(
        isolate, "Tomatkungen v1.0", NewStringType::kNormal).ToLocalChecked());
  }

  void Execute(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    sqlite3 *db;
    int rc;
    sqlite3_stmt *stmt;

    // if not args[0] equals databasename, args[1] equals query
    if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Databasename and query should be supplied",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // if not args[0] equals String, args[1] equals String
    if (!args[0]->IsString() || !args[1]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Databasename and query should be strings",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // v8 to cpp string
    v8::String::Utf8Value str(isolate, args[0]);
    std::string databaseName(*str);
    
    // v8 to cpp string
    v8::String::Utf8Value s(isolate, args[1]);
    std::string query(*s);
    // cpp to v8 string
    // v8::Local<v8::String> v8String = v8::String::NewFromUtf8(isolate, cppStr.c_str(), v8::String::kNormalString);

    // Print back the args[0] to nodejs
    // args.GetReturnValue().Set(String::NewFromUtf8(
    //    isolate, firtsArg.c_str(), NewStringType::kNormal).ToLocalChecked());

    // Open database
    rc = sqlite3_open(
      databaseName.c_str(), &db
    );

    if ( rc != SQLITE_OK && rc != SQLITE_DONE ) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Can't open databases",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // Sql Create
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);    

    if ( rc !=  SQLITE_OK ) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            sqlite3_errmsg(db),
                            NewStringType::kNormal).ToLocalChecked()));

      return;
    }

    rc = sqlite3_step(stmt);

    // Failed the create request
    if ( rc != SQLITE_OK && rc != SQLITE_DONE ) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            sqlite3_errmsg(db),
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    args.GetReturnValue().Set(String::NewFromUtf8(
        isolate, "Execute successfully", NewStringType::kNormal).ToLocalChecked());
  }
 
  void Select(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    sqlite3 *db;
    int rc;
    sqlite3_stmt *stmt;

    // if not args[0] equals databasename, args[1] equals query
    if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Databasename and query should be supplied",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // if not args[0] equals String, args[1] equals String
    if (!args[0]->IsString() || !args[1]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Databasename and query should be strings",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // v8 to cpp string
    v8::String::Utf8Value str(isolate, args[0]);
    std::string databaseName(*str);
    
    // v8 to cpp string
    v8::String::Utf8Value s(isolate, args[1]);
    std::string query(*s);

    // Open database
    rc = sqlite3_open(
      databaseName.c_str(), &db
    );

    if ( rc != SQLITE_OK && rc != SQLITE_DONE ) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Can't open databases",
                            NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    // Sql Select
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);    

    if ( rc !=  SQLITE_OK ) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            sqlite3_errmsg(db),
                            NewStringType::kNormal).ToLocalChecked()));

      return;
    }

//     Local<Array> ary = Array::New(isolate);
//     Local<Object> obj = Object::New(isolate);
    
//     obj->Set(context, String::NewFromUtf8(isolate, "sum", NewStringType::kNormal).ToLocalChecked(), Number::New(isolate, 3));

//     ary->Set(context, 0, Integer::New(isolate ,2));
//     ary->Set(context, 0, Integer::New(isolate ,2));
//     ary->Set(context, 1, obj);
// args.GetReturnValue().Set(ary);
    

    Local<Array> sqlAry = Array::New(isolate);
    int sqlRow = 0;
    while ( sqlite3_step(stmt) != SQLITE_DONE ) {

      Local<Object> sqlObj = Object::New(isolate);

		  int sqlCol = sqlite3_column_count(stmt);
      for (int i = 0; i < sqlCol; i++) {
        
        const char * columnName = sqlite3_column_name(stmt, i);

        switch (sqlite3_column_type(stmt, i)) {
          case (SQLITE3_TEXT): {
              const char * columText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));

              (void)sqlObj->Set(context, 
                          String::NewFromUtf8(isolate,
                                              columnName,
                                              NewStringType::kNormal).ToLocalChecked(),
                          String::NewFromUtf8(isolate,
                                              columText,
                                              NewStringType::kNormal).ToLocalChecked()
              );
              break;
            }
          case (SQLITE_INTEGER): {
            int columnInteger = sqlite3_column_int64(stmt, i);

            (void)sqlObj->Set(context, 
                        String::NewFromUtf8(isolate,
                                            columnName,
                                            NewStringType::kNormal).ToLocalChecked(),
                        Integer::New(isolate, columnInteger)
            );
            break;
          };
          case (SQLITE_FLOAT): {
            double columnDouble = sqlite3_column_double(stmt, i);

            (void)sqlObj->Set(context, 
                        String::NewFromUtf8(isolate,
                                            columnName,
                                            NewStringType::kNormal).ToLocalChecked(),
                        Number::New(isolate, columnDouble)
            );

            break;
          }
          case (SQLITE_BLOB): {

            (void)sqlObj->Set(context, 
                        String::NewFromUtf8(isolate,
                                            columnName,
                                            NewStringType::kNormal).ToLocalChecked(),
                        node::Buffer::Copy(isolate,
                                           static_cast <const char *> (sqlite3_column_blob(stmt, i)),
                                           sqlite3_column_bytes(stmt, i)
                        ).ToLocalChecked()
            );

            break;
          }
          case (SQLITE_NULL): {
            
            (void)sqlObj->Set(context, 
                        String::NewFromUtf8(isolate,
                                            columnName,
                                            NewStringType::kNormal).ToLocalChecked(),
                        v8::Null(isolate)
            );

            break;
          }
          default: {
				    break;
          }
        }

        
      }
      (void)sqlAry->Set(context, sqlRow, sqlObj);
      sqlRow++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    args.GetReturnValue().Set(sqlAry);
  }

  void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "Version", Version);
    NODE_SET_METHOD(exports, "Execute", Execute);
    NODE_SET_METHOD(exports, "Select", Select);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);

}