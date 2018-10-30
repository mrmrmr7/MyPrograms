#ifndef WORKWITHDATA_H
#define WORKWITHDATA_H


using namespace QtDataVisualization;

void DataSource::update(QSurface3DSeries *series)
{
    if (series && m_data.size()) {

        // Изменяем индекс выводимой поверхности
        m_index++;
        if (m_index > m_data.count() - 1)
            m_index = 0;

        QSurfaceDataArray array = m_data.at(m_index);
        int newRowCount = array.size();
        int newColumnCount = array.at(0)->size();

        // При старте программы или при изменении количество столбцов или строк
        // нужно переразметить m_resetArray
        if (!m_resetArray || series->dataProxy()->rowCount() != newRowCount
                || series->dataProxy()->columnCount() != newColumnCount) {
            m_resetArray = new QSurfaceDataArray();
            m_resetArray->reserve(newRowCount);
            for (int i(0); i < newRowCount; i++)
                m_resetArray->append(new QSurfaceDataRow(newColumnCount));
        }

        // Копирование элементов из array в m_resetArray
        for (int i(0); i < newRowCount; i++) {
            const QSurfaceDataRow &sourceRow = *(array.at(i));
            QSurfaceDataRow &row = *(*m_resetArray)[i];
            for (int j(0); j < newColumnCount; j++)
                row[j].setPosition(sourceRow.at(j).position());
        }

        // Сообщаем об изменении данных
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

#endif // WORKWITHDATA_H
