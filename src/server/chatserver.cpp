#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include<string>
#include<functional>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(
    EventLoop *loop,
    const InetAddress &listenAddr,
    const string &nameArg
) : _server(loop,listenAddr,nameArg) , _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback( std::bind(&ChatServer::onConnection, this, _1) );

    // 注册消息回调
    _server.setMessageCallback( std::bind(&ChatServer::onMessage, this, _1, _2, _3) );

    // 设置线程数量
    _server.setThreadNum(4);

}

// 启动服务
void ChatServer::start(){
    _server.start();
}

// 上报连接相关信息的回调函数
void ChatServer::onConnection( const TcpConnectionPtr& conn){
    // 客户端断开连接
    if(!conn->connected()){
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

// 上报读写事件相关信息的回调函数
void ChatServer::onMessage( const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time){
    string buf = buffer->retrieveAllAsString();
    // 数据反序列化（解码）
    json js = json::parse(buf);
    // 达到的目的：完全解耦网络模块和业务模块的代码    回调函数
    // 通过js["msgid"]获取-》业务处理器handler-》conn js time
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn,js,time);
}