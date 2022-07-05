#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <abstract/ilogger.h>

#include <QFile>
#include <QTextStream>

//! @brief Логгер, записывающий логи в файл.
class FileLogger : public ILogger
{
public:
    //! @brief Конструктор с открытием файла.
    //! @param filename имя файла.
    FileLogger(const QString& filename);

    //! @brief Записать сообщение в лог.
    //! @param message сообщение для записи в лог.
    void write_log(const QString &message) override;

private:
    QFile log_file_;        //! < файл лога.
    QTextStream stream_;    //! < поток для записи в файл.
};

#endif // #ifndef FILE_LOGGER_H
