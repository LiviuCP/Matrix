#ifndef MATRIX_TEMPLATE_SPECIALIZATIONS_H
#define MATRIX_TEMPLATE_SPECIALIZATIONS_H

#include <string>

#include "matrix.h"

template<>
Matrix<std::string>::operator bool() const
{
    bool result{false};

    if (m_pBaseArrayPtr)
    {
        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col].size() != 0)
                {
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

#ifdef QT

#include <QPointF>

template<>
Matrix<QPointF>::operator bool() const
{
    bool result{false};

    if (m_pBaseArrayPtr)
    {
        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (!m_pBaseArrayPtr[row][col].isNull())
                {
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

#endif


#endif // MATRIX_TEMPLATE_SPECIALIZATIONS_H
