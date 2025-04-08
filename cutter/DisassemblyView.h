#pragma once
#include <QPlainTextEdit>

class DisassemblyView : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit DisassemblyView(QWidget* parent = nullptr);
    void setInstructions(const QStringList& instructions);
};
