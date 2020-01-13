#include "inputeffect.h"

#include "ports/outport.h"
#include <QDebug>

InputEffect::InputEffect(Audio* parent) : Effect(parent)
{
    effectName = "Input Device Effect";
    type = 0;
    inputDevicePort = new OutPort("Input Device port", this);
    addPort(inputDevicePort,QPointF(50,100));
    data = {};
}

void InputEffect::giveData(char *data, int readLength)
{
    if (sizeof(this->data) < readLength){
        this->data = new char[readLength];
    }
    for (int i = 0; i < readLength; i++){
        this->data[i] = data[i];
    }
    //memcpy(this->data, data, readLength);
    hasData = true;
}

void InputEffect::giveDataFloat(float *dataFloat, int readLength)
{
    if (sizeof(this->dataFloat) < readLength){
        this->dataFloat = new float[readLength];
    }
    for (int i = 0; i < readLength; i++){
        this->dataFloat[i] = dataFloat[i];
    }
    //memcpy(this->data, data, readLength);
    hasData = true;
}

void InputEffect::applyEffect(char *in, char *out, int readLength)
{
    out = in;
}

char *InputEffect::getData(OutPort*, int readLength)
{
    if (hasData){
        hasData = false;
        return data;
    } else {
        qWarning() << "Error, has no data!";
        return nullptr;
    }
}
