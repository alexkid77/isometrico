#ifndef ITIMER_H
#define ITIMER_H

/** \brief Abstracion del temporizador
 *
 * \param
 * \param
 * \return
 *
 */

class ITimer
{
public:
    ITimer();
    virtual double GetTicks()=0;
    virtual ~ITimer();

protected:

private:
};

#endif // ITIMER_H
