#include <logger/tab_logger.h>

TabLogger::TabLogger(QPlainTextEdit *tab_edit):
    tab_edit_(tab_edit) {}

void TabLogger::write_log(const QString &message)
{
    tab_edit_->moveCursor(QTextCursor::End);
    tab_edit_->insertPlainText(message);
}
