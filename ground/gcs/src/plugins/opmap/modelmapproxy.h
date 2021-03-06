/**
 ******************************************************************************
 * @file       modelmapproxy.h
 *
 * @author     dRonin, http://dRonin.org/, Copyright (C) 2016
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2012-2013
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup OPMapPlugin Tau Labs Map Plugin
 * @{
 * @brief Tau Labs map plugin
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 *
 * Additional note on redistribution: The copyright and license notices above
 * must be maintained in each individual source file that is a derivative work
 * of this source file; otherwise redistribution is prohibited.
 */

#ifndef MODELMAPPROXY_H
#define MODELMAPPROXY_H
#include <QWidget>
#include "tlmapcontrol/tlmapcontrol.h"
#include "waypoint.h"
#include "QPointer"
#include <QItemSelectionModel>

#include "../pathplanner/flightdatamodel.h"

using namespace mapcontrol;

/**
 * @brief The ModelMapProxy class maps from the @ref FlightDataModel to the OPMap
 * and provides synchronization, both when the model changes updating the UI and
 * if it is modified on the UI propagating changes to the model
 */
class ModelMapProxy : public QObject
{
    typedef enum {
        OVERLAY_LINE,
        OVERLAY_CURVE_RIGHT,
        OVERLAY_CURVE_LEFT,
        OVERLAY_CIRCLE_RIGHT,
        OVERLAY_CIRCLE_LEFT
    } overlayType;
    Q_OBJECT
public:
    explicit ModelMapProxy(QObject *parent, TLMapWidget *map, FlightDataModel *model,
                           QItemSelectionModel *selectionModel);

    //! Get the handle to a waypoint graphical item
    WayPointItem *findWayPointNumber(int number);

    //! When a waypoint is created graphically, insert into the end of the model
    void createWayPoint(internals::PointLatLng coord);

    //! When a waypoint is deleted graphically, delete from the model
    void deleteWayPoint(int number);

    //! When all the waypoints are deleted graphically, update the model
    void deleteAll();
private slots:

    //! Data in the model is changed, update the UI
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    //! Rows inserted into the model, update the UI
    void rowsInserted(const QModelIndex &parent, int first, int last);

    //! Rows removed from the model, update the UI
    void rowsRemoved(const QModelIndex &parent, int first, int last);

    //! The UI changed a waypoint, update the model
    void WPValuesChanged(WayPointItem *wp);

    //! When a row is changed, highlight the waypoint
    void currentRowChanged(QModelIndex, QModelIndex);

    //! When a list of waypoints are changed, select them in model
    void selectedWPChanged(QList<WayPointItem *>);

private:
    overlayType overlayTranslate(int type);
    void createOverlay(WayPointItem *from, WayPointItem *to, overlayType type, QColor color,
                       double radius);
    void createOverlay(WayPointItem *from, HomeItem *to, ModelMapProxy::overlayType type,
                       QColor color);
    TLMapWidget *myMap;
    FlightDataModel *model;
    void refreshOverlays();
    QItemSelectionModel *selection;
};

#endif // MODELMAPPROXY_H
