#ifndef DISASSEMBLYHIGHLIGHTER_H
#define DISASSEMBLYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class DisassemblyHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit DisassemblyHighlighter(QTextDocument* parent = nullptr);

protected:
    void highlightBlock(const QString& text) override;

private:
    struct HighlightRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightRule> rules;
};

#endif // DISASSEMBLYHIGHLIGHTER_H
