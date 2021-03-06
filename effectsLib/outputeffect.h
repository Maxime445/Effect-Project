#ifndef OUTPUTEFFECT_H
#define OUTPUTEFFECT_H

#include <QObject>
#include "effect.h"

QT_BEGIN_NAMESPACE
class InPort;
QT_END_NAMESPACE


class OutputEffect : public Effect
{
    Q_OBJECT
public:
    OutputEffect(Audio* parent = nullptr);


    char* getData(OutPort*, int) override;

private:
    InPort* outputDevicePort;

    void applyEffect(char *in, char *out, int readLength) override;
};

#endif // OUTPUTEFFECT_H
