#ifndef REP_BASESIMULATIONINTERFACE_REPLICA_H
#define REP_BASESIMULATIONINTERFACE_REPLICA_H

// This is an autogenerated file.
// Do not edit this file, any changes made will be lost the next time it is generated.

#include <QtCore/qobject.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qvariant.h>
#include <QtCore/qmetatype.h>

#include <QtRemoteObjects/qremoteobjectnode.h>
#include <QtRemoteObjects/qremoteobjectpendingcall.h>
#include <QtRemoteObjects/qremoteobjectreplica.h>

#include "basictypes.h"

class BaseSimulationInterfaceReplica : public QRemoteObjectReplica
{
    Q_OBJECT
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "BaseSimulationInterface")
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "ac8eb22012f29d013df92e6baaae5cd8676835b0")

public:
    BaseSimulationInterfaceReplica() : QRemoteObjectReplica() { initialize(); }
    static void registerMetatypes()
    {
        static bool initialized = false;
        if (initialized)
            return;
        initialized = true;
        qRegisterMetaType<DisplayableObjectType>();
        qRegisterMetaTypeStreamOperators<DisplayableObjectType>();
        qRegisterMetaType<PositionType>();
        qRegisterMetaTypeStreamOperators<PositionType>();
        qRegisterMetaType<RectDimentionsType>();
        qRegisterMetaTypeStreamOperators<RectDimentionsType>();

    }

private:
    BaseSimulationInterfaceReplica(QRemoteObjectNode *node, const QString &name = QString())
        : QRemoteObjectReplica(ConstructWithNode)
    {
        initializeNode(node, name);
    }

    void initialize() override
    {
        BaseSimulationInterfaceReplica::registerMetatypes();
        QVariantList properties;
        properties.reserve(0);
        setProperties(properties);
    }

public:
    virtual ~BaseSimulationInterfaceReplica() {}


Q_SIGNALS:
    void clearReqFwd();
    void addObjectReqFwd(const int __repc_variable_1, const DisplayableObjectType __repc_variable_2);
    void deleteObjectReqFwd(const int __repc_variable_1);
    void updateObjectPositionReqFwd(const int __repc_variable_1, const PositionType __repc_variable_2);
    void situationRectDimensionsReqFwd();
    void situationRectDimensionsInfoFwd(const RectDimentionsType __repc_variable_1);
    void cannotAddObjectFwd(const int __repc_variable_1);
    void cannotDeleteObjectFwd(const int __repc_variable_1);
    void cannotUpdateObjectPositionFwd(const int __repc_variable_1);
    void simulationFinishedFwd();

public Q_SLOTS:
    void clearReqReemit()
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("clearReqReemit()");
        QVariantList __repc_args;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void addObjectReqReemit(const int __repc_variable_1, const DisplayableObjectType __repc_variable_2)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("addObjectReqReemit(int,DisplayableObjectType)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
            << QVariant::fromValue(__repc_variable_2)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void deleteObjectReqReemit(const int __repc_variable_1)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("deleteObjectReqReemit(int)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void updateObjectPositionReqReemit(const int __repc_variable_1, const PositionType __repc_variable_2)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("updateObjectPositionReqReemit(int,PositionType)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
            << QVariant::fromValue(__repc_variable_2)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void situationRectDimensionsReqReemit()
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("situationRectDimensionsReqReemit()");
        QVariantList __repc_args;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void situationRectDimensionsInfoReemit(const RectDimentionsType __repc_variable_1)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("situationRectDimensionsInfoReemit(RectDimentionsType)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void cannotAddObjectReemit(const int __repc_variable_1)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("cannotAddObjectReemit(int)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void cannotDeleteObjectReemit(const int __repc_variable_1)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("cannotDeleteObjectReemit(int)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void cannotUpdateObjectPositionReemit(const int __repc_variable_1)
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("cannotUpdateObjectPositionReemit(int)");
        QVariantList __repc_args;
        __repc_args
            << QVariant::fromValue(__repc_variable_1)
        ;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
    void simulationFinishedReemit()
    {
        static int __repc_index = BaseSimulationInterfaceReplica::staticMetaObject.indexOfSlot("simulationFinishedReemit()");
        QVariantList __repc_args;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }

private:
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};

#if (QT_VERSION < QT_VERSION_CHECK(5, 5, 0))
#endif


QT_BEGIN_NAMESPACE
QT_END_NAMESPACE


#endif // REP_BASESIMULATIONINTERFACE_REPLICA_H