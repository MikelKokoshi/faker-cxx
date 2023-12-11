#include "faker-cxx/Database.h"

#include "data/Collations.h"
#include "data/ColumnNames.h"
#include "data/ColumnTypes.h"
#include "data/Engines.h"
#include "faker-cxx/Helper.h"
#include "faker-cxx/String.h"

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

TableSchema Database::table()
{
    TableSchema retval;

    retval.name = "User";

    ColumnSchema usernameColumn;
    usernameColumn.name = "username";
    usernameColumn.type = "string";

    ColumnSchema emailColumn;
    emailColumn.name = "email";
    emailColumn.type = "string";

    ColumnSchema ageColumn;
    ageColumn.name = "age";
    ageColumn.type = "int";

    retval.columns.push_back(usernameColumn);
    retval.columns.push_back(emailColumn);
    retval.columns.push_back(ageColumn);
}
}
