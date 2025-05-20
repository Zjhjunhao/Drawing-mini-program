/****************************************************************************
** Meta object code from reading C++ file 'drawingtools.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../DrawingMini--ver 0.5/drawingtools.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawingtools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12DrawingToolsE_t {};
} // unnamed namespace

template <> constexpr inline auto DrawingTools::qt_create_metaobjectdata<qt_meta_tag_ZN12DrawingToolsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DrawingTools",
        "returnShape",
        "",
        "Shapes*",
        "p",
        "setColor",
        "color",
        "setSize",
        "size",
        "setMode",
        "mode",
        "setSelectedShape"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'returnShape'
        QtMocHelpers::SignalData<void(Shapes *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'setColor'
        QtMocHelpers::SlotData<void(QColor)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QColor, 6 },
        }}),
        // Slot 'setSize'
        QtMocHelpers::SlotData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Slot 'setMode'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'setSelectedShape'
        QtMocHelpers::SlotData<void(Shapes *)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DrawingTools, qt_meta_tag_ZN12DrawingToolsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DrawingTools::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12DrawingToolsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12DrawingToolsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12DrawingToolsE_t>.metaTypes,
    nullptr
} };

void DrawingTools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DrawingTools *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->returnShape((*reinterpret_cast< std::add_pointer_t<Shapes*>>(_a[1]))); break;
        case 1: _t->setColor((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 2: _t->setSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setMode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->setSelectedShape((*reinterpret_cast< std::add_pointer_t<Shapes*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DrawingTools::*)(Shapes * )>(_a, &DrawingTools::returnShape, 0))
            return;
    }
}

const QMetaObject *DrawingTools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawingTools::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12DrawingToolsE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DrawingTools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DrawingTools::returnShape(Shapes * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
