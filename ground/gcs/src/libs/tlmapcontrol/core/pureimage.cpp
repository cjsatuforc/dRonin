/**
******************************************************************************
*
* @file       pureimage.cpp
* @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
* @author     Tau Labs, http://taulabs.org, Copyright (C) 2013
* @brief      
* @see        The GNU Public License (GPL) Version 3
* @defgroup   TLMapWidget
* @{
* 
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
*/
#include "pureimage.h"


 
namespace core {
PureImageProxy::PureImageProxy()
{

}

QPixmap PureImageProxy::FromStream(const QByteArray &array)
{
    return QPixmap::fromImage(QImage::fromData(array));
}
bool PureImageProxy::Save(const QByteArray &array, QPixmap &pic)
{
    pic=QPixmap::fromImage(QImage::fromData(array));
    return true;
}
}
