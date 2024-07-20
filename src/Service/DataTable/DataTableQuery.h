//
// Created by Aashik on 30-06-2024.
//

#pragma once
#include <string>

class DataTableQuery {
public:
    static const std::string TableName;
    static const std::string SelectAll;
    static const std::string ColumnName;
    static const std::string EmptyRow;
    static const std::string DeleteRow;
    static const std::string DeleteColumn;
};

const std::string DataTableQuery::TableName = "SELECT table_name from gpkg_contents";
const std::string DataTableQuery::SelectAll = "SELECT * FROM '%s'";
const std::string DataTableQuery::ColumnName = "SELECT name FROM pragma_table_info('%s');";
const std::string DataTableQuery::EmptyRow = "INSERT INTO '%s' DEFAULT VALUES;";
const std::string DataTableQuery::DeleteRow = "DELETE FROM '%s' WHERE fid = ?";
const std::string DataTableQuery::DeleteColumn = "ALTER TABLE '%s' DROP COLUMN '%s'";
