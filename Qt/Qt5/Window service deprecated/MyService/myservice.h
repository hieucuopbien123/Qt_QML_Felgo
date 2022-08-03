#ifndef MYSERVICE_H
#define MYSERVICE_H

#include <QApplication>
#include <QObject>
#include <QDebug>
#include "qtservice.h"

class MyService : public QtService<QApplication>
        //theo example
{
public:
    /**
     * @brief The constructor
     * @param argc
     * @param argv
     */
    MyService(int argc, char **argv);//Khi viết các thư viện nên comment code như này thì khi rê chuột vào sẽ hiện
    //còn code sử dụng nên tránh comment

    /**
     * @brief The deconstructor
     */
    ~MyService();

    /**
     * @brief Start the service
     */
    void start();

    /**
     * @brief Pause the service
     */
    void pause();

    /**
     * @brief Resume the service
     */
    void resume();

    /**
     * @brief Stop the service
     */
    void stop();

    /**
     * @brief processCommand
     * @param code
     */
    void processCommand(int code);

private:
    //Add in any pointers
};

#endif // MYSERVICE_H
