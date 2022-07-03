#ifndef ILOGGER_H
#define ILOGGER_H

#include <QString>

//! @brief Интерфейс логгера.
class ILogger
{
public:
    //! @brief Записать сообщение в лог.
    //! @param message сообщение для записи в лог.
    virtual void write_log(const QString& message) = 0;
};

#endif // #ifndef ILOGGER_H
