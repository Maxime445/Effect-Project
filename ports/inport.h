#ifndef INPORT_H
#define INPORT_H

#include <QObject>
#include "port.h"

QT_BEGIN_NAMESPACE
class OutPort;
class QComboBox;
QT_END_NAMESPACE

class InPort : public Port
{
    Q_OBJECT
public:
    InPort(QString name, Effect* parent);
    static QList<InPort*>* getInPortList(){return inportList;}

private:
    static QList<InPort*>* inportList;
    // Port interface
protected:
    char *getData() override;
};


#endif // INPORT_H