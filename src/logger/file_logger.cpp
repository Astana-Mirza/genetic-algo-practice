#include <logger/file_logger.h>
#include <stdexcept>

FileLogger::FileLogger(const QString& filename):
    log_file_(filename)
{
    if (!log_file_.open(QFile::OpenModeFlag::Append))
    {
        throw std::runtime_error{QObject::tr("Cannot open file").toStdString()};
    }
    stream_.setDevice(&log_file_);
}

void FileLogger::write_log(const QString &message)
{
    stream_ << message;
    stream_.flush();
}
