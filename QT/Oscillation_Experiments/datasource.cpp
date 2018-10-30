#include "datasource.h"
#include "membrana.h"

Membrana m;

using namespace QtDataVisualization;

Q_DECLARE_METATYPE(QSurface3DSeries *)

void DataSource::generateData(int cacheCount, int rowCount, int columnCount,
                              float xMin, float xMax, float yMin, float yMax,
                              float zMin, float zMax)
{
    steps s(cacheCount, rowCount, columnCount, xMin, xMax, yMin, yMax,zMin, zMax);

    setPrimaryData(cacheCount,rowCount,columnCount);

    for (int i = 0; i < cacheCount; i++) {
        QSurfaceDataArray &cache = m_data[i];
        for (int j = 0; j < rowCount; j++)
        {
            QSurfaceDataRow &layer = *(cache[j]);
            for (int k = 0; k < columnCount; k++)
                layer[k] = QVector3D(k/m.scale,m.layers[i][k][j],j/m.scale);
        }
    }
}
