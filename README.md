Encode: UTF-8
-------------

# 羽毛球馆问题

## 文件说明

* src/  源代码目录
* test_case/ 测试用例输入文件
* Makefile 

使用C++语言，所有的源码文件使用UTF-8编码

## 方案设计

采用模块化的设计，主要分为一下几个模块

1. InputOutput

    主要负责输入解析和格式化输出，类名为InputOutput，在InputOutput.h中定义

2. BillingRule

    实现收费规则，在BillingRule.h中定义。在 class BillingRule中定义了一下两个方法：

    virtual int getBilling( int wday, int hour );

    virtual float getPenalty( int wday, int hour );

    这两个方法中，wday指定星期几，1-7代表星期一到星期天，hour指定某一个小时时间段，返回指定的这一个小时所需要的费用

3. Schedule

    用于管理预定记录，实现预定记录的添加和取消，在Schedule.h中定义。其中包括ScheduleOfDay类，用于保存一天的记录信息。Schedule类中主要包含两个方法：

    bool add(const Date &date,const ScheduleItem &item);

    bool cancel(const Date &date,const ScheduleItem &item);

    这两个方法用于添加预定信息和取消预订信息，其中date表示预定日期，class  ScheduleItem中包含预定时间段、用户ID、收入、是否取消等属性。

4. PlayGround

    整合所有模块，实现预定、取消预约、收入的计算。

## 编译

此程序在linux平台使用gcc工具链编译和测试

    $ make
    c++ -Isrc/include   -c -o src/BillingRule.o src/BillingRule.cpp
    c++ -Isrc/include   -c -o src/main.o src/main.cpp
    c++ -Isrc/include   -c -o src/Schedule.o src/Schedule.cpp
    c++ -Isrc/include   -c -o src/InputOutput.o src/InputOutput.cpp
    c++ -Isrc/include   -c -o src/PlayGround.o src/PlayGround.cpp
    c++ -o test src/BillingRule.o src/main.o src/Schedule.o src/InputOutput.o src/PlayGround.o

在工程主目录运行make命令，生成test可执行文件完成编译

## 测试

在test\_case文件夹下包含测试用例输入文件，其中test\_case1.txt文件是题目中测试用例1，test\_case2.txt文件是题目中测试用例2

在工程主目录中完成编译后，执行测试用例1，运行命令

    $ ./test < test_cast1.txt
    



执行测试用例2，运行命令

    ./test < test_cast2.txt








