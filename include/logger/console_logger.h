#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include <abstract/ilogger.h>

//! @brief Логгер, записывающий логи в поток std::clog.
class ConsoleLogger : public ILogger
{
public:
    //! @brief Записать сообщение в лог.
    //! @param message сообщение для записи в лог.
    void write_log(const QString &message) override;
};

#endif // #ifndef CONSOLE_LOGGER_H
