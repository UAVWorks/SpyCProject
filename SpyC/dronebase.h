#ifndef DRONEBASE_H
#define DRONEBASE_H

// Qt
#include <QObject>
#include <QGeoCoordinate>

// Application
#include "settingcontroller.h"
class WayPointModel;
class AlertModel;
class GalleryModel;
class ExclusionAreaModel;

class DroneBase : public QObject
{
    Q_OBJECT

    // UID & video URL
    Q_PROPERTY(QString uid READ uid NOTIFY uidChanged)
    Q_PROPERTY(QString videoUrl READ videoUrl NOTIFY uidChanged)

    // Initial position, current position and heading
    Q_PROPERTY(QGeoCoordinate initialPosition READ initialPosition NOTIFY initialPositionChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double heading READ heading WRITE setHeading NOTIFY headingChanged)

    // State, edit mode, work mode and global status
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString stateText READ stateText NOTIFY stateChanged)
    Q_PROPERTY(int workMode READ workMode WRITE setWorkMode NOTIFY workModeChanged)
    Q_PROPERTY(int defaultWorkMode READ defaultWorkMode NOTIFY defaultWorkModeChanged)
    Q_PROPERTY(int currentExclusionShape READ currentExclusionShape WRITE setCurrentExclusionShape NOTIFY currentExclusionShapeChanged)
    Q_PROPERTY(int globalStatus READ globalStatus NOTIFY globalStatusChanged)

    // Battery and GPS level/status
    Q_PROPERTY(int batteryLevel READ batteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int returnLevel READ returnLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int gpsStrength READ gpsStrength WRITE setGPSStrength NOTIFY gpsStrengthChanged)
    Q_PROPERTY(int batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(int gpsStatus READ gpsStatus NOTIFY gpsStatusChanged)

    // Mission plan model and safety model
    Q_PROPERTY(WayPointModel *missionPlanModel READ missionPlanModel NOTIFY missionPlanModelChanged)
    Q_PROPERTY(WayPointModel *safetyModel READ safetyModel NOTIFY safetyModelChanged)
    Q_PROPERTY(WayPointModel *landingPlanModel READ landingPlanModel NOTIFY landingPlanModelChanged)
    Q_PROPERTY(ExclusionAreaModel *exclusionAreaModel READ exclusionAreaModel NOTIFY exclusionAreaModelChanged)
    Q_PROPERTY(AlertModel *alertModel READ alertModel NOTIFY alertModelChanged)
    Q_PROPERTY(GalleryModel *galleryModel READ galleryModel NOTIFY galleryModelChanged)

    Q_ENUMS(Status)
    Q_ENUMS(State)
    Q_ENUMS(WorkMode)
    Q_ENUMS(AlertType)
    Q_ENUMS(ExclusionShape)

public:
    //! Define a status
    enum Status {NOMINAL=Qt::UserRole+1, WARNING, CRITICAL};

    //! Define a drone state
    enum State {IDLE=Qt::UserRole+1, FLYING};

    //! Define a drone mode
    enum WorkMode {MISSION_PLAN_EDIT=Qt::UserRole+1, SAFETY_EDIT, LANDING_PLAN_EDIT, CARTO_EDIT, PAYLOAD_EDIT, GALLERY_EDIT, EXCLUSION_EDIT};

    //! Exclusion shape
    enum ExclusionShape {CIRCLE=Qt::UserRole+1, RECTANGLE, TRIANGLE};

    //! Alert type
    enum AlertType {NO_ALERT=Qt::UserRole+1, BATTERY, GPS, POSITION};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit DroneBase(QObject *pParent=nullptr);

    //! Constructor
    DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPosition, QObject *pParent=nullptr);

    //! Destructor
    virtual ~DroneBase();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone uid
    const QString &uid() const;

    //! Return video url
    const QString &videoUrl() const;

    //! Return battery level
    int batteryLevel() const;

    //! Set battery level
    void setBatteryLevel(int iBatteryLevel);

    //! Return level
    int returnLevel() const;

    //! Set return level
    void setReturnLevel(int iReturnLevel);

    //! Return GPS strength
    int gpsStrength() const;

    //! Set GPS strength
    void setGPSStrength(int iStrength);

    //! Return initial position
    const QGeoCoordinate &initialPosition() const;

    //! Return position
    const QGeoCoordinate &position() const;

    //! Set position
    void setPosition(const QGeoCoordinate &pos);

    //! Return heading
    double heading() const;

    //! Set heading
    void setHeading(double dHeading);

    //! Return battery status
    int batteryStatus() const;

    //! Set battery status
    void setBatteryStatus(int iBatteryStatus);

    //! Return GPS status
    int gpsStatus() const;

    //! Set GPS status
    void setGPSStatus(int iGPSStatus);

    //! Set global status
    void setGlobalStatus(const Status &eStatus);

    //! Return global status
    int globalStatus() const;

    //! Return state
    int state() const;

    //! Return state text
    QString stateText() const;

    //! Set state
    void setState(int iState);

    //! Return work mode
    int workMode() const;

    //! Set work mode
    void setWorkMode(int iMode);

    //! Return default work mode
    int defaultWorkMode() const;

    //! Return current exclusion shape
    int currentExclusionShape() const;

    //! Set current exclusion shape
    void setCurrentExclusionShape(int iExclusionShape);

    //! Set default work mode
    Q_INVOKABLE void setDefaultWorkMode();

    //! Return mission plan model
    WayPointModel *missionPlanModel() const;

    //! Return safety model
    WayPointModel *safetyModel() const;

    //! Return landing plan model
    WayPointModel *landingPlanModel() const;

    //! Return alert model
    AlertModel *alertModel() const;

    //! Gallery model
    GalleryModel *galleryModel() const;

    //! Exclusion area model
    ExclusionAreaModel *exclusionAreaModel() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Initialize
    void initialize(const QMap<int, QVariant> &mSettings);

    //! Clear mission plan
    Q_INVOKABLE void clearMissionPlan();

    //! Clear safety
    Q_INVOKABLE void clearSafety();

    //! Clear landing plan
    Q_INVOKABLE void clearLandingPlan();

    //! Add coordinate to mission plan
    Q_INVOKABLE void addCoordinateToMissionPlan(const QGeoCoordinate &geoCoordinate);

    //! Add coordinate to safety
    Q_INVOKABLE void addCoordinateToSafety(const QGeoCoordinate &geoCoordinate);

    //! Add coordinate to landing plan
    Q_INVOKABLE void addCoordinateToLandingPlan(const QGeoCoordinate &geoCoordinate);

    //! Set mission plan point position
    Q_INVOKABLE void setMissionPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Set safety point position
    Q_INVOKABLE void setSafetyPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Set landing plan point position
    Q_INVOKABLE void setLandingPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Remove coordinate from safety at index
    Q_INVOKABLE void removeCoordinateFromSafetyPlanAtIndex(int iPointIndex);

    //! Remove coordinate from mission plan at index
    Q_INVOKABLE void removeCoordinateFromMissionPlanAtIndex(int iPointIndex);

    //! Remove coordinate from landing plan at index
    Q_INVOKABLE void removeCoordinateFromLandingPlanAtIndex(int iPointIndex);

    //! Clear exclusion areas
    Q_INVOKABLE void clearExclusionAreas();

    //! Close safety
    void closeSafety();

private:
    //! Update battery status
    void updateBatteryStatus();

    //! Update GPS status
    void updateGPSStatus();

private:
    //! Settings
    QMap<int, QVariant> m_mSettings;

    //! UID
    QString m_sDroneUID = "";

    //! Video URL
    QString m_sVideoUrl = "";

    //! Battery level
    int m_iBatteryLevel = 0;

    //! Return level
    int m_iReturnLevel = 0;

    //! Battery status
    Status m_eBatteryStatus = NOMINAL;

    //! GPS strength
    int m_iGPSStrength = 0;

    //! GPS status
    Status m_eGPSStatus = NOMINAL;

    //! Original position
    QGeoCoordinate m_initialPosition;

    //! Position
    QGeoCoordinate m_position;

    //! Heading
    double m_dHeading = 0;

    //! State
    State m_eState = IDLE;

    //! Work mode
    WorkMode m_eWorkMode = PAYLOAD_EDIT;

    //! Default work mode
    WorkMode m_eDefaultWorkMode = PAYLOAD_EDIT;

    //! Current exclusion shape
    ExclusionShape m_eExclusionShape = CIRCLE;

    //! Global status
    Status m_eGlobalStatus = Status::NOMINAL;

    //! Mission plan model
    WayPointModel *m_pMissionPlanModel = nullptr;

    //! Safety model
    WayPointModel *m_pSafetyModel = nullptr;

    //! Landing plan model
    WayPointModel *m_pLandingPlanModel = nullptr;

    //! Alert model
    AlertModel *m_pAlertModel = nullptr;

    //! Gallery model
    GalleryModel *m_pGalleryModel = nullptr;

    //! Exclusion area model
    ExclusionAreaModel *m_pExclusionAreaModel = nullptr;

    //! Setting controller
    SettingController m_settingController;

public slots:
    //! Global status changed
    void onGlobalStatusChanged();

signals:
    //! UID changed
    void uidChanged();

    //! Video url changed
    void videoUrlChanged();

    //! Global status changed
    void globalStatusChanged();

    //! Mode changed
    void stateChanged();

    //! Battery level changed
    void batteryLevelChanged();

    //! Return level changed
    void returnLevelChanged();

    //! GPS strength changed
    void gpsStrengthChanged();

    //! Battery status changed
    void batteryStatusChanged();

    //! GPS status changed
    void gpsStatusChanged();

    //! Position changed
    void positionChanged();

    //! Initial position changed
    void initialPositionChanged();

    //! Heading changed
    void headingChanged();

    //! Position status changed
    void positionStatusChanged();

    //! Mission plan model changed
    void missionPlanModelChanged();

    //! Safety model changed
    void safetyModelChanged();

    //! Landing plan model changed
    void landingPlanModelChanged();

    //! Exclusion area model changed
    void exclusionAreaModelChanged();

    //! Alert model changed
    void alertModelChanged();

    //! Gallery model changed
    void galleryModelChanged();

    //! Edit mode changed
    void workModeChanged();

    //! Default work mode changed
    void defaultWorkModeChanged();

    //! Current exclusion shape changed
    void currentExclusionShapeChanged();
};

Q_DECLARE_METATYPE(DroneBase::Status)
Q_DECLARE_METATYPE(DroneBase::State)
Q_DECLARE_METATYPE(DroneBase::WorkMode)
Q_DECLARE_METATYPE(DroneBase::AlertType)
Q_DECLARE_METATYPE(DroneBase::ExclusionShape)

#endif // DRONEBASE_H
