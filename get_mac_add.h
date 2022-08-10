#ifndef GET_MAC_ADD_H
#define GET_MAC_ADD_H
#include <QString>
#include "QtNetwork/QNetworkInterface"
#include "QtNetwork/QtNetwork"

class get_mac
{
    get_mac();
    ~get_mac();

public:

static QString get_mac_add()

        {
            foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
            {
                if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
                return netInterface.hardwareAddress();
            }
        return QString();
    }
};
#endif // GET_MAC_ADD_H
