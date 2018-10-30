#include "datasource.h"

using namespace QtDataVisualization;


Q_DECLARE_METATYPE(QSurface3DSeries *)

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(-1),
    m_resetArray(nullptr)
{
    //! [4]
    qRegisterMetaType<QSurface3DSeries *>();
    //! [4]
}

DataSource::~DataSource()
{
    clearData();
}


void DataSource::update(QSurface3DSeries *series)
{
    if (series && m_data.size()) {
        // Each iteration uses data from a different cached array
        m_index++;
        if (m_index > m_data.count() - 1)
            m_index = 0;

        QSurfaceDataArray array = m_data.at(m_index);
        int newRowCount = array.size();
        int newColumnCount = array.at(0)->size();

        // If the first time or the dimensions of the cache array have changed,
        // reconstruct the reset array
        if (!m_resetArray || series->dataProxy()->rowCount() != newRowCount || series->dataProxy()->columnCount() != newColumnCount) {
            m_resetArray = new QSurfaceDataArray();
            m_resetArray->reserve(newRowCount);
            for (int i(0); i < newRowCount; i++)
                m_resetArray->append(new QSurfaceDataRow(newColumnCount));
        }

        // Copy items from our cache to the reset array
        for (int i(0); i < newRowCount; i++) {
            const QSurfaceDataRow &sourceRow = *(array.at(i));
            QSurfaceDataRow &row = *(*m_resetArray)[i];
            for (int j(0); j < newColumnCount; j++)
                row[j].setPosition(sourceRow.at(j).position());
        }

        // Notify the proxy that data has changed
        series->dataProxy()->resetArray(m_resetArray);
    }
}

void DataSource::clearData()
{
    for (int i(0); i < m_data.size(); i++) {
        QSurfaceDataArray &array = m_data[i];
        for (int j(0); j < array.size(); j++)
            delete array[j];
        array.clear();
    }
}

void DataSource::setPrimaryData(double cacheCount, double rowCount, double columnCount)
{

    if (!cacheCount || !rowCount || !columnCount)
        return;

    clearData();

    m_data.resize(cacheCount);

    for (int i(0); i < cacheCount; i++) {
        QSurfaceDataArray &array = m_data[i];
        array.reserve(rowCount);
        for (int j(0); j < rowCount; j++)
            array.append(new QSurfaceDataRow(columnCount));
    }
}

