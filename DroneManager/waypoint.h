#ifndef WAYPOINT_H
#define WAYPOINT_H

// Qt
#include <QGeoCoordinate>
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT WayPoint
{
    Q_ENUMS(Type)

public:
    enum Type {POINT, LOITER, EIGHT, HIPPODROM};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    WayPoint();

    //! Constructor
    WayPoint(const QGeoCoordinate &geoCoord, const Type &eType=POINT);

    //! Destructor
    virtual ~WayPoint();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return geoCoord
    const QGeoCoordinate &geoCoord() const;

    //! Return type
    const Type &type() const;

private:
    //! Geo coordinate
    QGeoCoordinate m_geoCoord;

    //! Point type
    Type m_eType = POINT;
};
}

#endif // WAYPOINT_H
