#include "radiodevice.h"

RadioDevice::RadioDevice(const RadioType type) :
    QObject(nullptr)
{
    qRegisterMetaType<Position>("Position");
    type_            = type;
    newDataReceived_ = false;
}

RadioDevice::RadioDevice(const RadioDevice& radio) :
    QObject(nullptr)
{
    type_            = radio.type_;
    data_            = radio.data_;
    newDataReceived_ = radio.newDataReceived_;
}

void RadioDevice::TransmitData(const Position& data)
{
    if(type_ == RECEIVER)
    {
        qCritical() << "Radio Device: it is receiver, you should not try to transmit data";
        return;
    }

    emit Transmit(data);
}

const Position& RadioDevice::ReceiveData()
{
    if(type_ == TRANSMITTER)
    {
        qCritical() << "Radio Device: it is transmitter, you should not try to receive data";
    }

    newDataReceived_ = false;
    return data_;
}

bool RadioDevice::newDataReceived()
{
    if(type_ == TRANSMITTER)
    {
        return false;
    }
    return newDataReceived_;
}

void RadioDevice::Receive(Position data)
{
    if(type_ == TRANSMITTER)
    {
        return;
    }

    newDataReceived_ = true;
    data_            = data;
}
