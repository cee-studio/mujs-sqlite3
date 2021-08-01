#include <stdio.h>
#include <stdlib.h>

#include "mujs.h"
#include "js_sqlite3.h"

const char *g_config_file;

#define DB_NAME  "'mujs.db'"
#define SQL_EXEC_STMT "'DROP TABLE IF EXISTS cats;"              \
                      "CREATE TABLE cats (name TEXT, age INT);'"
#define SQL_PREPARE_INSERT_STMT "'INSERT INTO cats (name, age) VALUES (?, ?)'"
#define SQL_PREPARE_SELECT_STMT "'SELECT age FROM cats WHERE name = ?'"

int main(void)
{
  js_State *J = js_newstate(NULL, NULL, JS_STRICT);
  jssqlite3_init(J);

  /* TEST SQLITE3 BINDING */
  js_dostring(J, "var db = new Database();");
  js_dostring(J, "db.open("DB_NAME");");
  js_dostring(J, "db.exec("SQL_EXEC_STMT");");
  js_dostring(J, "var stmt = db.prepare("SQL_PREPARE_INSERT_STMT");");
  js_dostring(J, "stmt.run('Joey', 2);");
  js_dostring(J, "stmt = db.prepare("SQL_PREPARE_SELECT_STMT");");
  js_dostring(J, "var cat = stmt.get('Joey');");
  js_dostring(J, "print(JSON.stringify(cat));");
  js_dostring(J, "db.close();");

  return EXIT_SUCCESS;
}
