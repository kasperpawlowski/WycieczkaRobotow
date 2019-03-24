#ifndef RADIODEVICE_H
#define RADIODEVICE_H

#include <QObject>
#include <QDebug>
#include "position.h"

/*!
 * \brief The RadioDevice class is a simple class that can transmit the Position
 *        data or receive the Position data to/from other radio devices
 *
 * There are three types of radio devices:
 * TRANSMITTER - can only thansmit the Position data to other radio devices
 * RECEIVER - can only receive the Position data from other radio devices
 * BOTH - can transmit and receive the Position data to/from other radio devices
 */
class RadioDevice : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief The RadioType enum describes the radio device type
     */
    enum RadioType {TRANSMITTER, RECEIVER, BOTH};

    /*!
     * \brief RadioDevice constructs a RadioDevice of desired type
     * \param[in] type radio device type
     */
    RadioDevice(const RadioType type);

    /*!
     * \brief RadioDevice copy constructor
     * \param[in] radio RadioDevice to be copied
     */
    RadioDevice(const RadioDevice& radio);

    /*!
     * \brief TransmitData transmits Position data to other connected
     *        radio devices
     * \param[in] data Position data to be transmitted
     */
    void TransmitData(const Position& data);

    /*!
     * \brief ReceiveData receives Position data from other connected
     *        radio devices
     * \return received Position data
     */
    const Position& ReceiveData();

    /*!
     * \brief newDataReceived indicates whether new data has been received
     * \return true when new data received and have not been read yet,
     *         false otherwise
     */
    bool newDataReceived();

public slots:
    /*!
     * \brief Receive shall be connected to the Transmit signal of the radio
     *        device that we want receive Position data from
     * \param data
     */
    void Receive(Position data);

signals:
    /*!
     * \brief Transmit emitted when Position data sent by the radio device
     * \param data
     */
    void Transmit(Position data);

private:
    RadioDevice() = delete;
    RadioType type_;
    Position  data_;
    bool      newDataReceived_;
};

#endif // RADIODEVICE_H
