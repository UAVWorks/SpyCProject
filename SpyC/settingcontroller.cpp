// Qt
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QSettings>
#include <QLocale>

// Application
#include "settingcontroller.h"
#define USER_ARMY "/user/army"
#define USER_UNIT "/user/unit"
#define USER_MISSION "/user/mission"
#define USER_OPERATOR "/user/operator"
#define USER_LANGUAGE  "/user/language"
#define USER_MISSION_DIR "/user/mission_dir"
#define USER_MAP_DIR "/user/map_dir"
#define USER_LOG_DIR "/user/log_dir"
#define USER_ALERT_DIR "/user/alert_dir"
#define USER_GALLERY_DIR "/user/gallery_dir"

//-------------------------------------------------------------------------------------------------

SettingController::SettingController(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

SettingController::~SettingController()
{

}

//-------------------------------------------------------------------------------------------------

bool SettingController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);

    loadSettings();
    return true;
}

//-------------------------------------------------------------------------------------------------

void SettingController::shutdown()
{
    saveSettings();
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
}

//-------------------------------------------------------------------------------------------------

QString SettingController::snapShotPath(const QString &sDroneUID) const
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString sTimeStamp = QString("%1_%2_%3_%4_%5_%6").arg(curDateTime.date().day()).arg(curDateTime.date().month()).
            arg(curDateTime.date().year()).arg(curDateTime.time().hour()).arg(curDateTime.time().minute()).
            arg(curDateTime.time().second());
    QString sGalleryDir = QDir(m_sGalleryPath).absoluteFilePath(sDroneUID);
    sGalleryDir.replace(" ", "_");
    QDir dGalleryDir(sGalleryDir);
    dGalleryDir.mkpath(dGalleryDir.absolutePath());
    QString sGalleryFile = dGalleryDir.absoluteFilePath("snapshot_%1_%2.jpg").arg(sDroneUID).arg(sTimeStamp);
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
    if (sArmy != m_sArmy)
    {
        m_sArmy = sArmy;
        emit armyChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::unit() const
{
    return m_sUnit;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setUnit(const QString &sUnit)
{
    if (sUnit != m_sUnit)
    {
        m_sUnit = sUnit;
        emit unitChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mission() const
{
    return m_sMission;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMission(const QString &sMission)
{
    if (sMission != m_sMission)
    {
        m_sMission = sMission;
        emit missionChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::operatorName() const
{
    return m_sOperator;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setOperatorName(const QString &sName)
{
    if (sName != m_sOperator)
    {
        m_sOperator = sName;
        emit operatorNameChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::langString() const
{
    return m_sLangString;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLangString(const QString &sLangString)
{
    if (sLangString != m_sLangString)
    {
        m_sLangString = sLangString;
        emit langStringChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mapPath() const
{
    return m_sMapPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMapPath(const QString &sMapPath)
{
    if (sMapPath != m_sMapPath)
    {
        m_sMapPath = sMapPath;
        emit mapPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::missionPath() const
{
    return m_sMissionPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMissionPath(const QString &sMissionPath)
{
    if (sMissionPath != m_sMissionPath)
    {
        m_sMissionPath = sMissionPath;
        emit missionPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::logPath() const
{
    return m_sLogPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLogPath(const QString &sLogPath)
{
    if (sLogPath != m_sLogPath)
    {
        m_sLogPath = sLogPath;
        emit logPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::alertPath() const
{
    return m_sAlertPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setAlertPath(const QString &sAlertPath)
{
    if (sAlertPath != m_sAlertPath)
    {
        m_sAlertPath = sAlertPath;
        emit alertPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::galleryPath() const
{
    return m_sGalleryPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setGalleryPath(const QString &sGalleryPath)
{
    if (sGalleryPath != m_sGalleryPath)
    {
        m_sGalleryPath = sGalleryPath;
        emit galleryPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

int SettingController::hand() const
{
    return (int)m_eHand;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setHand(int iHand)
{
    m_eHand = (UIOrientation)iHand;
    emit handChanged();
}

//-------------------------------------------------------------------------------------------------

QMap<int, QVariant> SettingController::allSettings()
{
    QMap<int, QVariant> mAllSettings;
    mAllSettings[ARMY] = m_sArmy;
    mAllSettings[UNIT] = m_sUnit;
    mAllSettings[MISSION] = m_sMission;
    mAllSettings[OPERATOR] = m_sOperator;
    mAllSettings[LANGUAGE_STRING] = m_sLangString;
    mAllSettings[MAP_PATH] = m_sMapPath;
    mAllSettings[MISSION_PATH] = m_sMissionPath;
    mAllSettings[LOG_PATH] = m_sLogPath;
    mAllSettings[ALERT_PATH] = m_sAlertPath;
    mAllSettings[GALLERY_PATH] = m_sGalleryPath;
    return mAllSettings;
}

//-------------------------------------------------------------------------------------------------

void SettingController::loadSettings()
{
    qDebug() << "LOAD SETTINGS";
    QDir baseDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QSettings settings;
    QString sArmy = settings.value(USER_ARMY).toString();
    if (sArmy.simplified().isEmpty())
        sArmy = tr("Army");
    m_sArmy = sArmy;

    QString sUnit = settings.value(USER_UNIT).toString();
    if (sUnit.simplified().isEmpty())
        sUnit = tr("Unit");
    m_sUnit = sUnit;

    QString sMission = settings.value(USER_MISSION).toString();
    if (sMission.simplified().isEmpty())
        sMission = tr("Mission");
    m_sMission = sMission;

    QString sOperator = settings.value(USER_OPERATOR).toString();
    if (sOperator.simplified().isEmpty())
        sOperator = tr("Operator");
    m_sOperator = sOperator;

    QString sLangString = settings.value(USER_LANGUAGE).toString();
    if (sLangString.simplified().isEmpty())
        sLangString = "FR";
    applyLanguage(sLangString);

    QString sMapPath = settings.value(USER_MAP_DIR).toString();
    if (sMapPath.simplified().isEmpty())
        sMapPath = baseDir.absoluteFilePath("maps");
    createDir(sMapPath);
    m_sMapPath = sMapPath;

    QString sMissionPath = settings.value(USER_MISSION_DIR).toString();
    if (sMissionPath.simplified().isEmpty())
        sMissionPath = baseDir.absoluteFilePath("mission");
    createDir(sMissionPath);
    m_sMissionPath = sMissionPath;

    QString sLogPath = settings.value(USER_LOG_DIR).toString();
    if (sLogPath.simplified().isEmpty())
        sLogPath = baseDir.absoluteFilePath("logs");
    createDir(sLogPath);
    m_sLogPath = sLogPath;

    QString sAlertPath = settings.value(USER_ALERT_DIR).toString();
    if (sAlertPath.simplified().isEmpty())
        sAlertPath = baseDir.absoluteFilePath("alerts");
    createDir(sAlertPath);
    m_sAlertPath = sAlertPath;

    QString sGalleryPath = settings.value(USER_GALLERY_DIR).toString();
    if (sGalleryPath.simplified().isEmpty())
        sGalleryPath = baseDir.absoluteFilePath("gallery");
    createDir(sGalleryPath);
    m_sGalleryPath = sGalleryPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::saveSettings()
{
    qDebug() << "SAVE SETTINGS";
    QSettings settings;
    settings.setValue(USER_ARMY, m_sArmy);
    settings.setValue(USER_UNIT, m_sUnit);
    settings.setValue(USER_MISSION, m_sMission);
    settings.setValue(USER_OPERATOR, m_sOperator);
    settings.setValue(USER_LANGUAGE, m_sLangString);
    settings.setValue(USER_MAP_DIR, m_sMapPath);
    settings.setValue(USER_MISSION_DIR, m_sMissionPath);
    settings.setValue(USER_LOG_DIR, m_sLogPath);
    settings.setValue(USER_ALERT_DIR, m_sAlertPath);
    settings.setValue(USER_GALLERY_DIR, m_sGalleryPath);
}

//-------------------------------------------------------------------------------------------------

void SettingController::createDir(const QString &sDirPath)
{
    qDebug() << "CREATING DIR: " << sDirPath;
    QDir dir(sDirPath);
    if (!dir.exists())
      dir.mkpath(".");
}
