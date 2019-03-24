#ifndef BASICSENSOR_H
#define BASICSENSOR_H

#include "basictypes.h"

/*!
 * \brief The BasicSensor class is a simple sensor capable of measuring wide range
 *        of physical quantities
 *
 * A sensor measures raw InputType quantity, processes it and outputs OutputType
 * quantity.
 */
template<typename InputType, typename OutputType>
class BasicSensor
{
public:
    /*!
     * \brief BasicSensor constructs a new BasicSensor
     */
    BasicSensor();

    /*!
     * \brief BasicSensor copy constructor
     * \param[in] sensor BasicSensor to be copied
     */
    BasicSensor(const BasicSensor& sensor);

    /*!
     * \brief ~BasicSensor destructs the BasicSensor
     */
    virtual ~BasicSensor();

    /*!
     * \brief set sets sensor input
     * \param[in] in raw measured data
     */
    virtual void set(const InputType& in);

    /*!
     * \brief get returns processed data
     * \return
     */
    virtual const OutputType& get() const;

    /*!
     * \brief process a method that processes raw data to get output data
     *
     * This method has to be overloaded if any processing is needed. Defaultly
     * the process() method does nothing
     */
    virtual void process();

private:
    InputType  in_;
    OutputType out_;
};

template<typename InputType, typename OutputType>
BasicSensor<InputType, OutputType>::BasicSensor()
{

}

template<typename InputType, typename OutputType>
BasicSensor<InputType, OutputType>::BasicSensor(const BasicSensor& sensor)
{
    in_  = sensor.in_;
    out_ = sensor.out_;
}

template<typename InputType, typename OutputType>
BasicSensor<InputType, OutputType>::~BasicSensor()
{

}

template<typename InputType, typename OutputType>
void BasicSensor<InputType, OutputType>::set(const InputType& in)
{
    in_ = in;

    process();
}

template<typename InputType, typename OutputType>
const OutputType& BasicSensor<InputType, OutputType>::get() const
{
    return out_;
}

template<typename InputType, typename OutputType>
void BasicSensor<InputType, OutputType>::process()
{
    out_ = in_;
}

#endif // BASICSENSOR_H
