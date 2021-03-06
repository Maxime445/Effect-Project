﻿#include "effectmap.h"

#include <QComboBox>
#include <QHash>
#include <QDebug>

#include "audio.h"
#include "effect.h"
#include "effectbuffer.h"
#include "effectsLib/inputeffect.h"
#include "effectsLib/outputeffect.h"
#include "ports/port.h"
#include "ports/outport.h"
#include "ports/inport.h"

#include <effectsLib/echoeffect1.h>
#include <effectsLib/multiplyeffect.h>
#include <effectsLib/paneffect.h>

EffectMap::EffectMap(Audio *parent) : QObject(parent),
    m_effectMap(new QMap<Effect*, Port*>()),
    m_connectionsMap(new QHash<Port*, Port*>())
{

}

char *EffectMap::getData(Effect *e, Port* p)
{
    if (e->type == 0){
        // Input device effect - just get data.
        return static_cast<InputEffect*>(e)->getData(nullptr, readLength);
    }

    if (m_connectionsMap->contains(p)){
        if (p->portType == 0){
            // Input Port - returns connected output port effect
            OutPort* connectedPort = static_cast<OutPort*>(m_connectionsMap->value(p));
            Effect* connectedEffect = m_effectMap->key(connectedPort);
            char* data = connectedEffect->getData(connectedPort, readLength);
            if (data){
                return data;
            } else {
                qDebug() <<  "No data returned!!";
                qDebug() << e->effectName << " port " << p->getName() << " to " << connectedEffect->effectName << " port " << connectedPort->getName();
                return nullptr;
            }
        }
    }
}

bool EffectMap::isPortConnected(Port *p)
{
    return m_connectionsMap->contains(p);
}

void EffectMap::addEffect(Effect *e)
{
    for (Port* p : e->getPorts()){
        m_effectMap->insertMulti(e,p);
    }
}

void EffectMap::deleteEffect(Effect *e)
{
    // Remove Connections
    for (Port* p : e->getPorts()){
        if (m_connectionsMap->contains(p)){
            p = m_connectionsMap->take(p);
            m_connectionsMap->take(p);
        }
    }
    // Remove Effect
    m_effectMap->remove(e);
}

void EffectMap::connectPorts(Port *p1, Port *p2)
{
/*
    if (m_connectionsMap->contains(p1)){
        p1 = m_connectionsMap->take(p1);
        p1 = m_connectionsMap->take(p1);
    }
    if (m_connectionsMap->contains(p2)){
        p2 = m_connectionsMap->take(p2);
        p2 = m_connectionsMap->take(p2);
    }*/
    m_connectionsMap->insert(p1, p2);
    m_connectionsMap->insert(p2, p1);
}

void EffectMap::disconnectPorts(Port *p1, Port *p2)
{
    if (m_connectionsMap->contains(p1) && m_connectionsMap->contains(p2)){
        if (
                (m_connectionsMap->find(p1).value() == p2) &&
                (m_connectionsMap->find(p2).value() == p1)){
            m_connectionsMap->remove(p1);
            m_connectionsMap->remove(p2);
        }
    }
}


