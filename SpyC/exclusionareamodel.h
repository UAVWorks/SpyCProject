#ifndef EXCLUSIONAREAMODEL_H
#define EXCLUSIONAREAMODEL_H

// Qt
#include <QAbstractListModel>
#include <QGeoCoordinate>

// Application
class BaseShape;

class ExclusionAreaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(BaseShape *currentShape READ currentShape WRITE setCurrentShape NOTIFY currentShapeChanged)

public:
    enum Roles {ShapeRole=Qt::UserRole+1};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    ExclusionAreaModel(QObject *pParent=nullptr);

    //! Destructor
    ~ExclusionAreaModel();

    //-------------------------------------------------------------------------------------------------
    // QAbstractListModel interface
    //-------------------------------------------------------------------------------------------------

    //! Return data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add rect
    Q_INVOKABLE void addRectangle(const QGeoCoordinate &center);

    //! Add circle
    Q_INVOKABLE void addCircle(const QGeoCoordinate &center);

    //! Add triangle
    Q_INVOKABLE void addTriangle(const QGeoCoordinate &center);

    //! Remove shape
    Q_INVOKABLE void removeShape(int iShapeIndex);

    //! Clear
    void clear();

private:
    //! Add shape
    void addShape(BaseShape *pShape);

    //! Return current shape
    BaseShape *currentShape() const;

    //! Set current shape
    void setCurrentShape(BaseShape *pShape);

private:
    //! Shapes
    QVector<BaseShape *> m_vShapes;

    //! Current shape
    BaseShape *m_pCurrentShape = nullptr;

signals:
    //! Current shape changed
    void currentShapeChanged();
};

#endif // EXCLUSIONAREAMODEL_H
