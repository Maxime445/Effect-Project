#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>

QT_BEGIN_NAMESPACE
class Effect;
class EffectBuffer;
class EffectMap;
class InPort;
class InputEffect;
class OutPort;
class OutputEffect;
class QAudioInput;
class QAudioOutput;
class QAudioDeviceInfo;
QT_END_NAMESPACE


class Audio : public QObject
{
public:
    Audio(QObject* parent = nullptr);
    Q_OBJECT

public:
    QList<Effect*>* getEffectMap();
    void addEffect(Effect* e);
    void removeEffect(Effect* e);

    EffectBuffer* getEffectBuffer() {return m_buffer;}

    QList<QAudioDeviceInfo> availableAudioInputDevices();
    QList<QAudioDeviceInfo> availableAudioOutputDevices();
    void setInputDevice(QAudioDeviceInfo device);
    void setOutputDevice(QAudioDeviceInfo device);


private:
    //Input and output effects are created by default.
    InputEffect* m_inEffect;
    OutputEffect* m_outEffect;

    EffectMap* m_effectMap;

    InPort* inPort;
    OutPort* outPort;

    EffectBuffer* m_buffer;
    QAudioDeviceInfo* inputDevice;
    QAudioDeviceInfo* outputDevice;
    QAudioInput* inputAudio;
    QAudioOutput* outputAudio;

    bool running = false;

    void setupFormat();

public slots:
    bool runAudio();

};

#endif // AUDIO_H
