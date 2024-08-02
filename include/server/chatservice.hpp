#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
using namespace std;
using namespace muduo::net;
using namespace muduo;

#include "redis.hpp"
#include "groupmodel.hpp"
#include "friendmodel.hpp"
#include "offlinemessagemodel.hpp"
#include "usermodel.hpp"
#include "json.hpp"
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型,MsgHandler 是一个自定义数据类型，函数指针，可以用来推迟函数的声明
// 此处十分重要，换言之，MsgHandler可以看做login或者reg的功能，由于并不确定客户端的操作，于是使用function推迟声明
// 通过getHandler来判断使用login或者reg的绑定函数作为函数返回值
using MsgHandler = std::function<void(const TcpConnectionPtr& conn, json &js, Timestamp )>;

// 聊天服务器业务类
class ChatService{
public:
    // 获取单例对象的接口函数
    static ChatService* instance();
    // 登录业务
    void login(const TcpConnectionPtr& conn, json &js, Timestamp);
    // 注册业务
    void reg(const TcpConnectionPtr& conn, json &js, Timestamp);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr& conn);
    // 处理注销业务
    void loginout(const TcpConnectionPtr& conn, json &js, Timestamp);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr& conn, json &js, Timestamp);
    // 服务器异常，业务重置方法
    void reset();
    // 添加好友业务
    void addFriend(const TcpConnectionPtr& conn, json &js, Timestamp);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn,json &js,Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn,json &js,Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn,json &js,Timestamp time);

    // 从redis消息队列中获取订阅消息
    void handleRedisSubscribeMessage(int , string);


private:
    ChatService();
    // 存储消息id和其对应业务处理方法
    unordered_map<int,MsgHandler> _msgHandlerMap;
    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    // 定义互斥锁，保证_userconnMap线程安全
    mutex _connMutex;
    
    // 数据操作类对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    // redis操作对象
    Redis _redis;
};

#endif