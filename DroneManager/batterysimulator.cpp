// Qt
#include <QDebug>

// Application
#include "batterysimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

BatterySimulator::BatterySimulator(const QString &sDroneUID, QObject *pParent) : BaseSimulator(sDroneUID, pParent)
{
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &BatterySimulator::onTimeOut, Qt::QueuedConnection);
    m_timer.start(0);
}

//-------------------------------------------------------------------------------------------------

BatterySimulator::~BatterySimulator()
{

}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::start()
{
    m_timer.setInterval(500);
    m_bRepeat = true;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::onTimeOut()
{
    emit batteryLevelChanged(m_iBatteryLevel, m_sDroneUID);
    emit returnLevelChanged(m_iReturnLevel, m_sDroneUID);

    m_iBatteryLevel--;
    if (m_iBatteryLevel < 0)
        m_iBatteryLevel = 100;
    m_iReturnLevel = (100-m_iBatteryLevel)/2;
    if (m_bRepeat)
        m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::stop()
{
    m_timer.stop();
}
