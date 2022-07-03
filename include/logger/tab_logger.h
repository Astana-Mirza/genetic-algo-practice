#ifndef TAB_LOGGER_H
#define TAB_LOGGER_H

#include <abstract/ilogger.h>
#include <QPlainTextEdit>

//! @brief Логгер, записывающий логи во вкладку в окне программы.
class TabLogger : public ILogger
{
public:
    //! @brief Конструктор.
    //! @param tab_edit указатель на текстовое поле.
    TabLogger(QPlainTextEdit *tab_edit);

    //! @brief Записать сообщение в лог.
    //! @param message сообщение для записи в лог.
    void write_log(const QString &message) override;

private:
    QPlainTextEdit *tab_edit_;
};

#endif // #ifndef TAB_LOGGER_H
