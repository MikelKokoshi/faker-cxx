#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace faker
{

struct Column
{
    std::string name;
    std::string type;

    bool operator==(const Column& other) const
    {
        // Implement the logic to compare two Column objects
        return name == other.name; // Adjust the comparison based on your requirements
    }
};
struct TableSchema
{
    std::string name;
    std::vector<Column> columns;

    std::string toString() const
    {
        std::stringstream ss;
        ss << name << "(";
        for (size_t i = 0; i < columns.size(); ++i)
        {
            ss << columns[i].name;
            if (i < columns.size() - 1)
            {
                ss << ",";
            }
        }
        ss << ")";
        return ss.str();
    }
};

const std::vector<std::string> sqlCommandFormats = {"SELECT * FROM {table_name};",
                                                    "SELECT {table_columns} FROM {table_name};",
                                                    "DROP TABLE {table_name};",
                                                    "INSERT INTO {table} VALUES {values}"};

const std::vector<TableSchema> schemas = {
    TableSchema{"User", {Column{"username", "string"}, Column{"email", "string"}, Column{"age", "int"}}},

    TableSchema{"Product", {Column{"product_id", "int"}, Column{"product_name", "string"}}}};

class Database
{
public:
    /**
     * @brief Returns a random database column name.
     *
     * @returns Database column name.
     *
     * @code
     * Database::columnName() // "created_at"
     * @endcode
     */
    static std::string columnName();

    /**
     * @brief Returns a random database column type.
     *
     * @returns Database column type.
     *
     * @code
     * Database::columnType() // "timestamp"
     * @endcode
     */
    static std::string columnType();

    /**
     * @brief Returns a random database collation.
     *
     * @returns Database collation.
     *
     * @code
     * Database::collation() // "utf8_unicode_ci"
     * @endcode
     */
    static std::string collation();

    /**
     * @brief Returns a random database engine.
     *
     * @returns Database engine.
     *
     * @code
     * Database::engine() // "ARCHIVE"
     * @endcode
     */
    static std::string engine();

    /**
     * @brief Returns a MongoDB Object Id.
     *
     * @returns MongoDB Object Id.
     *
     * @code
     * Database::mongoDbObjectId() // "e175cac316a79afdd0ad3afb"
     * @endcode
     */
    static std::string mongoDbObjectId();

    /**
     * @brief Return a database table casually generated.
     *
     * @return TableSchema generated.
     *
     * @code
     * Databse::table()
     * @endcode
     */
    static TableSchema table();

    static std::string sqlCommand();
};
}
