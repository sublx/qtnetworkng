QtNetworkNg
===========


Introduction
------------

QtNetworkgNg is a self-contained coroutine-based network toolkit, like boost::asio but uses concepts of QtNetwork and gevent of Python. Compare to boost::asio and Qt's QtNetwork, QtNetworkNg has more simpler API. As the name suggests, QtNetworkNg requires Qt5 framework. For more detail visit:

[Introduction to QtNetworkNg](http://qtng.org/intro.html)


Documents
---------

Visit http://qtng.org/

Examples
--------

Here comes a simple example to get web pages.

    #include <QtCore/QCoreApplication>
    #include "qtnetworkng/qtnetworkng.h"
    
    int main(int argc, char **argv)
    {
        QCoreApplication app(argc, argv);
        qtng::HttpSession session;
        qtng::HttpResponse r = session.get("https://news.163.com");
        qDebug() << r.html();
        return 0;
    }
    
And another exmaple to make tcp connection.

    #include <QtCore/QCoreApplication>
    #include "qtnetworkng/qtnetworkng.h"
    
    int main(int argc, char **argv)
    {
        QCoreApplication app(argc, argv);
        qtng::Socket conn;
        conn.connect("news.163.com", 80);
        conn.sendall("GET / HTTP/1.0\r\n\r\n");
        qDebug() << conn.recv(1024 * 8);
        return 0;
    }

To create tcp server.

    Socket s;
    CoroutineGroup workers;
    s.bind(QHostAddress::Any, 8000);
    s.listen(100);
    while(true) {
        QSharedPointer<Socket> request(s.accept());
        if(request.isNull()) {
            break;
        }
        workers.spawn([request] {
            request->sendall("hello!");
            request->close();
        });
    }
    
As you can see, networking programming is done with very simple API.

License
-------

The QtNetworkNg is distributed under LGPL 3.0 license.

You can obtain a copy of LGPL 3.0 license at: https://www.gnu.org/licenses/lgpl-3.0.en.html

Dependencies
------------

QtNetworkNg require QtCore, QtNetwork to build, and require OpenSSL lib at runtime if you use the `SslSocket`.

Qt 5 - https://www.qt.io/download

Supported Platforms
-----------------------

Linux, Windows, Android and OpenBSD is supported. Macos, iOS is not tested yet.

QtNetworkNg uses more effective boost::context asm code in arm, arm64, x86, amd64 machines, and uses native ucontext or windows fiber API in other architectures.


TODO List
---------

* Support HTTP/2
* Implements an HTTP 1.0 server.
* HTTP support gzip.
* HttpResponse support stream.
* Support HTTP proxy and cache.
* Auto detect HTML encoding.
* Add more OpenSSL functions.
* Support MacOS and iOS platform.
* Remove QtNetwork dependence.

Building
--------

1. Clone QtNetworkNg from github as git subrepository.
2. include `qtnetworkng/qtnetworkng.pri` in your `project.pro` file.
3. include `qtnetworkng/qtnetworkng.h` in you cpp files.

How to Contribute
-----------------

Create a pull request on github.com with your patch, then make a pull request to me.

