# 基于muduo网络库实现的ChatServer服务器
可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端的源码 基于muduo、redis、mysql实现

平台工具：vscode远程linux开发，cmake构建，linux shell输出项目编译脚本，需自行导入/配置json、muduo、mysql、nginx、redis

项目内容：
1.使用muduo网络库作为项目的网络核心模块，提供高并发网络IO服务，解耦网络和业务模块代码；
2.使用json序列化和反序列化消息作为私有通信协议
3.配置nginx基于TCP的负载均衡，实现聊天服务器的集群功能，提高服务的并发能力；
4.基于redis的发布-订阅功能，实现跨服务器的消息通信；
5.使用mysql关系型数据库作为项目数据的落地存储。

项目功能：
1.用户的注册、登录、退出；
2.添加好友，并一对一聊天；
3.创建群组、加入群组，并进行群聊；
4.根据用户在线或离线状态，进行实时消息推送 或者 储存至数据库等待用户上线后推送

![image](https://github.com/user-attachments/assets/53976cbf-e23d-4cad-ace1-34ab48da1151)
