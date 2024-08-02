#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>
#include <string>
using namespace std;

// 数据库操作类
class MySQL
{
public:
    // 初始化数据库连接
    MySQL();
    // 释放数据库连接资源
    ~MySQL();
    // 连接数据库
    bool connect();
    // 更新操作
    bool update(string sql);
    // 查询操作,MYSQL_RES是结构体类型，用于存储查询结果集。
    MYSQL_RES *query(string sql);
    // 获取连接
    MYSQL* getConnection();

private:
    MYSQL *_conn;   //一个指向 MYSQL 结构体的指针,将 _conn 作为私有成员变量，可以保护数据库连接对象不被外部直接访问和修改，从而确保数据库连接的正确使用和管理
};

#endif