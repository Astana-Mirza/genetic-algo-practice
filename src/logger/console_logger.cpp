#include <logger/console_logger.h>
#include <iostream>

void ConsoleLogger::write_log(const QString &message)
{
    std::clog << message.toStdString();
}
