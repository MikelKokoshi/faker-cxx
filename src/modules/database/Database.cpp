#include "../../../include/faker-cxx/Database.h"

#include "../../../include/faker-cxx/Helper.h"
#include "../../../include/faker-cxx/Number.h"
#include "../../../include/faker-cxx/String.h"
#include "../../../include/faker-cxx/Word.h"
#include "../../common/FormatHelper.h"
#include "data/Collations.h"
#include "data/ColumnNames.h"
#include "data/ColumnTypes.h"
#include "data/Engines.h"

namespace faker
{

std::string Database::columnName()
{
    return Helper::arrayElement<std::string>(columnNames);
}

std::string Database::columnType()
{
    return Helper::arrayElement<std::string>(columnTypes);
}

std::string Database::collation()
{
    return Helper::arrayElement<std::string>(collations);
}

std::string Database::engine()
{
    return Helper::arrayElement<std::string>(engines);
}

std::string Database::mongoDbObjectId()
{
    return String::hexadecimal(24, HexCasing::Lower, HexPrefix::None);
}

std::string Database::sqlCommand()
{
    const auto randomTable = table();
    const auto randomQueryFormat = Helper::arrayElement<std::string>(sqlCommandFormats);
    const auto randomTableName = table().name;

    const auto dataGeneratorsMapping = std::map<std::string, std::function<std::string()>>{
        {"table_name", [randomTable]() { return randomTable.name; }},
        {"table_columns",
         [randomTable]()
         {
             std::stringstream ss;
             auto randomColumns = Helper::arrayElements(randomTable.columns);

             for (unsigned int i = 0; i < randomColumns.size(); i++)
             {
                 if (i == 0 || i == (randomColumns.size() - 1))
                 {
                     ss << randomColumns[i].name;
                     continue;
                 }
                 else
                 {
                     ss << "," << randomColumns[i].name << ",";
                 }
             }

             return ss.str();
         }},
        {"table", [randomTable]() { return randomTable.toString(); }},
        {"values", [randomTable]()
         {
             std::stringstream ss;
             ss << "(";

             for (unsigned int i = 0; i < randomTable.columns.size(); i++)
             {
                 if (randomTable.columns[i].type == "int")
                 {
                     ss << Number::integer(1000);
                 }
                 else if (randomTable.columns[i].type == "string")
                 {
                     ss << Word::noun();
                 }

                 if (i < randomTable.columns.size() - 1)
                 {
                     ss << ",";
                 }
             }

             ss << ")";
             return ss.str();
         }}};

    return FormatHelper::fillTokenValues(randomQueryFormat, dataGeneratorsMapping);
}

TableSchema Database::table()
{
    return Helper::arrayElement<TableSchema>(schemas);
}
}
