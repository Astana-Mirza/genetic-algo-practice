#include <logger/log.h>
#include <QDateTime>

Log& Log::get_log()
{
    static Log instance;
    return instance;
}


void Log::critical(const QString& message)
{
    if (level_ >= Log::Critical)
    {
        write_to_all(message);
    }
}


void Log::info(const QString& message)
{
    if (level_ >= Log::Info)
    {
        write_to_all(message);
    }
}


void Log::debug(const QString& message)
{
    if (level_ >= Log::Debug)
    {
        write_to_all(message);
    }
}


void Log::write_to_all(const QString& message)
{
    for (auto& [name, logger] : loggers_)
    {
        logger->write_log("[" + QDateTime::currentDateTime().toString(Qt::RFC2822Date) +
                          "]    " + message + '\n');
    }
}


void Log::set_log_level(LogLevel level)
{
    level_ = level;
}


void Log::add_logger(const QString &name, std::unique_ptr<ILogger> &&logger)
{
    loggers_[name] = std::move(logger);
}


void Log::delete_logger(const QString &name)
{
    loggers_.erase(name);
}
