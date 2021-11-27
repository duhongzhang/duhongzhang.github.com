#include <iostream>
#include <array>
#include <thread>
#include <list>
#include <atomic>
#include <csignal>

extern "C" {
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <time.h>
};

//TODO: 3.-lptread，调试，属性，命令行
//TODO: 4.[=]，外面的array会报错

//3.如果发送多次[一次只能被一个线程捕捉]，多个线程都可以收到阻塞信号。
//存储阻塞的上下文，做中断处理。
void handler(int signo) {
    while (1) {
        cout << "recv handler: " << this_thread::get_id() << ", " << signo << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void wakeUp(int signo)
{
    printf("please wakeup!!\n");
}

atomic<int> count(0);

using namespace std;
//TODO: 1. TCP和UDP可以同时占用一个port？
namespace socket_use {
    /*
     The domain argument specifies a communication domain; this selects  the
           protocol  family  which will be used for communication.  These families
           are  defined  in  <sys/socket.h>.   The  currently  understood  formats
           include:

           Name                Purpose                          Man page
           AF_UNIX, AF_LOCAL   Local communication              unix(7)
           AF_INET             IPv4 Internet protocols          ip(7)
           AF_INET6            IPv6 Internet protocols          ipv6(7)
           AF_IPX              IPX - Novell protocols
           AF_NETLINK          Kernel user interface device     netlink(7)
           AF_X25              ITU-T X.25 / ISO-8208 protocol   x25(7)
           AF_AX25             Amateur radio AX.25 protocol
           AF_ATMPVC           Access to raw ATM PVCs
           AF_APPLETALK        AppleTalk                        ddp(7)
           AF_PACKET           Low level packet interface       packet(7)
           AF_ALG              Interface to kernel crypto API
    */

    /*
    The  socket  has  the indicated type, which specifies the communication
       semantics.  Currently defined types are:

       SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based
                       byte  streams.  An out-of-band data transmission mecha‐
                       nism may be supported.

       SOCK_DGRAM      Supports datagrams (connectionless, unreliable messages
                       of a fixed maximum length).

       SOCK_SEQPACKET  Provides  a  sequenced,  reliable,  two-way connection-
                       based data transmission path  for  datagrams  of  fixed
                       maximum  length;  a  consumer  is  required  to read an
                       entire packet with each input system call.

       SOCK_RAW        Provides raw network protocol access.

       SOCK_RDM        Provides a reliable datagram layer that does not  guar‐
                       antee ordering.

       SOCK_PACKET     Obsolete  and  should  not be used in new programs; see
                       packet(7).

       Some socket types may not be implemented by all protocol families.

       Since Linux 2.6.27, the type argument serves a second purpose: in addi‐
       tion  to specifying a socket type, it may include the bitwise OR of any
       of the following values, to modify the behavior of socket():

       SOCK_NONBLOCK   Set the O_NONBLOCK file status flag  on  the  new  open
                       file description.  Using this flag saves extra calls to
                       fcntl(2) to achieve the same result.

       SOCK_CLOEXEC    Set the close-on-exec (FD_CLOEXEC) flag on the new file
                       descriptor.   See the description of the O_CLOEXEC flag
                       in open(2) for reasons why this may be useful.
    */
    /*
       The protocol specifies a  particular  protocol  to  be  used  with  the
       socket.  Normally only a single protocol exists to support a particular
       socket type within a given protocol family, in which case protocol  can
       be  specified  as  0.   However, it is possible that many protocols may
       exist, in which case a particular protocol must be  specified  in  this
       manner.   The  protocol number to use is specific to the “communication
       domain” in which communication is to take place; see protocols(5).  See
       getprotoent(3) on how to map protocol name strings to protocol numbers.
    */
    class socket_client{
        int sockfd;
        int init() {
            //socket - create an endpoint for communication
            //int socket(int domain, int type, int protocol);
            int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (sockfd < 0) {
                perror("socket failed = ");
                exit(1);
            }

            //int bind(int socket, const struct sockaddr* address, socklen_t address_len);
            struct sockaddr_in address;
            address.sin_family = AF_INET;
            address.sin_port = htons(5060);
            address.sin_addr.s_addr = inet_addr("127.0.0.1");

            //TODO: 2.static cast 不行
            int ret = bind(sockfd, reinterpret_cast<sockaddr *>(&address), sizeof(sockaddr));
            if (ret < 0) {
                perror("bind failed = ");
                exit(2);
            }

            /*
                The backlog argument defines the maximum length to which the queue of pending connections for sockfd may  grow.   If  a  connection  request
                arrives  when  the queue is full, the client may receive an error with an indication of ECONNREFUSED or, if the underlying protocol supports
                retransmission, the request may be ignored so that a later reattempt at connection succeeds.
            */
            //int listen(int sockfd, int backlog);
            ret = listen(sockfd, 128);
            if (ret < 0) {
                perror("listen failed = ");
                exit(3);
            }

            return sockfd;
        }

    public:
        int operator()() { return sockfd; }
        socket_client(): sockfd(init()) {
        }

        ~socket_client() {
            if (sockfd > -1)
                close(sockfd);
        }
    };
}



int main()
{
    //signal(SIGALRM, wakeUp);
    //signal(SIGINT, handler);
    //signal(SIGHUP, handler);
    //signal(SIGKILL, handler); //4.没有效果，SIGKILL和SIGSTP不能设定handler
    socket_use::socket_client sc;
    //printf("ready to alarm\n");
    //alarm(100);
    //printf("alarm and pause\n"); 
    //pause();
    //printf("pause stop\n");
/*
    flags     Specifies the type of message reception. Values of this argument are formed by logically OR'ing zero or more of the following val‐
        ues:

        MSG_PEEK    Peeks at an incoming message. The data is treated as unread and the next recv() or similar function shall still return
                    this data.

        MSG_OOB     Requests out-of-band data. The significance and semantics of out-of-band data are protocol-specific.

        MSG_WAITALL On  SOCK_STREAM sockets this requests that the function block until the full amount of data can be returned. The func‐
                    tion may return the smaller amount of data if the socket is a message-based socket, if a signal is caught, if the con‐
                    nection is terminated, if MSG_PEEK was specified, or if an error is pending for the socket.
*/
 
    list<thread> vt;
    //ssize_t recv(int socket, void* buffer, size_t length, int flags);
    while (true) {
        

        sockaddr face_2_addr;
        socklen_t slen = sizeof(sockaddr);
        //int accept(int socket, struct sockaddr *restrict address, socklen_t* restrict address_len);
        int listenfd = accept(sc(), &face_2_addr, &slen);
        if (listenfd < 0) {
            perror("accept failed = ");
            exit(4);
        }
        else {
            sockaddr_in* sin = reinterpret_cast<sockaddr_in*>(&face_2_addr);
            cout << sin->sin_family << ", " << inet_ntoa(sin->sin_addr) << ", " << sin->sin_port << endl;
        }

        /*
        1、MSG_OOB 接收以out-of-band 送出的数据.
        2、MSG_PEEK 返回来的数据并不会在系统内删除, 如果再调用recv()会返回相同的数据内容.
        3、MSG_WAITALL 强迫接收到len 大小的数据后才能返回, 除非有错误或信号产生.
        4、MSG_NOSIGNAL 此操作不愿被SIGPIPE 信号中断返回值成功则返回接收到的字符数, 失败返回-1,错误原因存于errno 中.
        */

        vt.push_back(thread([=]() mutable {
            while (true) {
                long int start = clock();
                array<char, 1024> buffer = { 0 };
                //TODO: 对端关掉以后，不停的接收成功，size=0的消息。
/*
        RETURN VALUE
        These calls return the number of bytes received, or -1 if an error occurred.  In the event of an error, errno is set to indicate the error.
        When a stream socket peer has performed an orderly shutdown, the return value will be 0 (the traditional "end-of-file" return).

       (非阻塞)The value 0 may also be returned if the requested number of bytes to receive from a stream socket was 0.
*/
                //意外关闭，持续CLOSE_WAIT 7200s，未收到FIN【画图】
                long int size = recv(listenfd, static_cast<void*>(&buffer[0]), buffer.size(), 0);
                long int end = clock();
                if (size <= 0) {
                    perror("error : ");
                    close(listenfd);
                    break;
                }
                cout << "thread = " << this_thread::get_id() << ", fd = " << listenfd << ", recv size = " << size << ", " << "time = " << end - start << ", count = " << count++ << endl;

                //'\0'也会跟着持续遍历输出
                //for (const auto& i : buffer) {
                    //cout 
                    //TODO: 1.telnet 每次打印出来都是两个换行。
                    //TODO: 2.智能接受一个telnet连接，其他telnet连接消息发到哪了。
                printf("%s", buffer.data());
                //}
                //cout << endl;
            }
        }));
    }

    for (auto& i : vt) {
        i.join();
    }

    return 0;
}