#include "DisassemblyView.h"

DisassemblyView::DisassemblyView(QWidget* parent)
    : QPlainTextEdit(parent) {
    setReadOnly(true);
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    setFrameStyle(QFrame::NoFrame);
    setWordWrapMode(QTextOption::NoWrap);
    setStyleSheet("background-color: transparent;"); // Background handled by MainWindow
}


void DisassemblyView::setInstructions(const QStringList& instructions) {
    clear();
    appendPlainText(instructions.join('\n'));
}
