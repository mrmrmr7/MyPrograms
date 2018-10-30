/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtDataVisualization/QSurface3DSeries>
using namespace QtDataVisualization;

struct steps
{
    int cacheCount;
    int rowCount;
    int columnCount;
    float xMin;
    float xMax;
    float yMin;
    float yMax;
    float zMin;
    float zMax;

  float x(float v)
  {
      float res;
      res = v * (xMax - xMin) / ((float)columnCount - 1.f);
      return res;
  }


  float y(float v)
  {
      float res;
      res = v * (yMax - yMin) / ((float)cacheCount - 1.f);
      return res;
  }

  float z(float v)
  {
      float res;
      res = v * (zMax - zMin) / ((float)rowCount - 1.f);
      return res;
  }

  steps(int _cacheCount, int _rowCount, int _columnCount,
        float _xMin, float _xMax, float _yMin, float _yMax,
        float _zMin, float _zMax)
  {
      cacheCount = _cacheCount;
      rowCount = _rowCount;
      columnCount = _columnCount;
      xMin = _xMin;
      xMax = _xMax;
      yMin = _yMin;
      yMax = _yMax;
      zMin = _zMin;
      zMax = _zMax;
  }
};

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);
    virtual ~DataSource();

    //! [0]
public Q_SLOTS:
    void generateData(int cacheCount, int rowCount, int columnCount,
                      float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

    void setPrimaryData(double,double,double);

    void update(QSurface3DSeries *series);
    //! [0]
private:
    void clearData();
    QVector<QSurfaceDataArray> m_data;
    int m_index;
    QSurfaceDataArray *m_resetArray;
};

#endif
