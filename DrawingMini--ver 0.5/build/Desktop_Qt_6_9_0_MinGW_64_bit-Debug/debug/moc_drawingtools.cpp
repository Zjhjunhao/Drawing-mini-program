/****************************************************************************
** Meta object code from reading C++ file 'drawingtools.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../drawingtools.h"
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
        "toolModeChanged",
        "mode",
        "setColor",
        "color",
        "setSize",
        "size",
        "setMode",
        "setSelectedShape",
        "setPKUImage",
        "badgeimage",
        "boyaimage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'returnShape'
        QtMocHelpers::SignalData<void(Shapes *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'toolModeChanged'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'setColor'
        QtMocHelpers::SlotData<void(QColor)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QColor, 8 },
        }}),
        // Slot 'setSize'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'setMode'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'setSelectedShape'
        QtMocHelpers::SlotData<void(Shapes *)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'setPKUImage'
        QtMocHelpers::SlotData<void(const QImage &, const QImage &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QImage, 14 }, { QMetaType::QImage, 15 },
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
        case 1: _t->toolModeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 3: _t->setSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->setMode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->setSelectedShape((*reinterpret_cast< std::add_pointer_t<Shapes*>>(_a[1]))); break;
        case 6: _t->setPKUImage((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DrawingTools::*)(Shapes * )>(_a, &DrawingTools::returnShape, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DrawingTools::*)(int )>(_a, &DrawingTools::toolModeChanged, 1))
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DrawingTools::returnShape(Shapes * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void DrawingTools::toolModeChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
