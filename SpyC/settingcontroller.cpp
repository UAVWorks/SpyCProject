// Qt
#include <QDebug>
#include <QDir>
#include <QDateTime>

// Application
#include "settingcontroller.h"

//-------------------------------------------------------------------------------------------------

SettingController::SettingController(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

SettingController::~SettingController()
{

}

//-------------------------------------------------------------------------------------------------

void SettingController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void SettingController::applyLanguage(const QString &sLang)
{
    setLangString(sLang);
    if (sLang == "FR")
        setLanguage(QLocale::French);
    else
    if (sLang == "US")
        setLanguage(QLocale::English);
    else
    if (sLang == "SD")
        setLanguage(QLocale::Arabic);
}

//-------------------------------------------------------------------------------------------------

QString SettingController::droneGalleryShotPath(const QString &sDroneUID) const
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString sTimeStamp = QString("%1_%2_%3_%4_%5_%6").arg(curDateTime.date().day()).arg(curDateTime.date().month()).
            arg(curDateTime.date().year()).arg(curDateTime.time().hour()).arg(curDateTime.time().minute()).
            arg(curDateTime.time().second());
    QDir dGalleryDir = QDir(m_sGalleryPath).absoluteFilePath(sDroneUID);
    dGalleryDir.mkpath(".");
    QString sGalleryFile = dGalleryDir.absoluteFilePath("snapshot_%1_%2.jpg").arg(sDroneUID).arg(sTimeStamp);
    sGalleryFile.replace(" ", "_");
    return sGalleryFile;
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::army() const
{
    return m_sArmy;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setArmy(const QString &sArmy)
{
    m_sArmy = sArmy;
    emit armyChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::unit() const
{
    return m_sUnit;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setUnit(const QString &sUnit)
{
    m_sUnit = sUnit;
    emit unitChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mission() const
{
    return m_sMission;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMission(const QString &sMission)
{
    m_sMission = sMission;
    emit missionChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::operatorName() const
{
    return m_sOperator;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setOperatorName(const QString &sName)
{
    m_sOperator = sName;
    emit operatorNameChanged();
}

//-------------------------------------------------------------------------------------------------

int SettingController::language() const
{
    return (int)m_eLanguage;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLanguage(int iLanguage)
{
    m_eLanguage = (QLocale::Language)iLanguage;
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::langString() const
{
    return m_sLangString;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLangString(const QString &sLangString)
{
    m_sLangString = sLangString;
    emit langStringChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mapPath() const
{
    return m_sMapPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMapPath(const QString &sMapPath)
{
    m_sMapPath = sMapPath;
    emit mapPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::missionPath() const
{
    return m_sMissionPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMissionPath(const QString &sMissionPath)
{
    m_sMissionPath = sMissionPath;
    emit missionPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::logPath() const
{
    return m_sLogPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLogPath(const QString &sLogPath)
{
    m_sLogPath = sLogPath;
    emit logPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::alertPath() const
{
    return m_sAlertPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setAlertPath(const QString &sAlertPath)
{
    m_sAlertPath = sAlertPath;
    emit alertPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::galleryPath() const
{
    return m_sGalleryPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setGalleryPath(const QString &sGalleryPath)
{
    m_sGalleryPath = sGalleryPath;
    emit galleryPathChanged();
}

//-------------------------------------------------------------------------------------------------

QMap<int, QVariant> SettingController::allSettings()
{
    QMap<int, QVariant> mAllSettings;
    mAllSettings[ARMY] = m_sArmy;
    mAllSettings[UNIT] = m_sUnit;
    mAllSettings[MISSION] = m_sMission;
    mAllSettings[OPERATOR] = m_sOperator;
    mAllSettings[LANGUAGE] = m_eLanguage;
    mAllSettings[LANGUAGE_STRING] = m_sLangString;
    mAllSettings[MAP_PATH] = m_sMapPath;
    mAllSettings[MISSION_PATH] = m_sMissionPath;
    mAllSettings[LOG_PATH] = m_sLogPath;
    mAllSettings[ALERT_PATH] = m_sAlertPath;
    mAllSettings[GALLERY_PATH] = m_sGalleryPath;
    return mAllSettings;
}
