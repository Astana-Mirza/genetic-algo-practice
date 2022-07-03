#ifndef LOG_H
#define LOG_H

#include <abstract/ilogger.h>

#include <QString>
#include <map>
#include <memory>

//! @brief Класс-синглтон для работы с логами.
class Log
{
public:
    //! @brief Уровни логирования.
    enum LogLevel
    {
        NoLog,      //! < логирование отключено.
        Critical,   //! < критический - самые важные сообщения.
        Info,       //! < информация - основная информация о работе программы.
        Debug       //! < отладка - наиболее подробная информация.
    };

    //! @brief Статический метод для получения единственного экземпляра класса.
    static Log& get_log();

    Log(const Log& other) = delete;
    Log(Log&& other)      = delete;

    //! @brief Записать в лог критическое сообщение.
    //! @param message сообщение.
    void critical(const QString& message);

    //! @brief Записать в лог сообщение с информацией.
    //! @param message сообщение.
    void info(const QString& message);

    //! @brief Записать в лог отладочное сообщение.
    //! @param message сообщение.
    void debug(const QString& message);

    //! @brief Установить уровень логирования.
    //! @param level уровень логирования.
    void set_log_level(LogLevel level);

    //! @brief Добавить логгер, который будет записывать приходящие сообщения.
    //! @param name имя логгера.
    //! @param logger указатель на логгер.
    void add_logger(const QString& name, std::unique_ptr<ILogger>&& logger);

    //! @brief Удалить логгер с данными именем, если он есть.
    //! @param name имя логгера.
    void delete_logger(const QString& name);
private:
    Log() = default;
    void write_to_all(const QString& message);

    std::map<QString, std::unique_ptr<ILogger>> loggers_;   //! < логгеры с их именами.
    LogLevel level_ = Info;                                 //! < текущий уровень логирования.
};

#endif // #ifndef LOG_H
