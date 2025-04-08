#include "DisassemblyHighlighter.h"
#include <QTextCharFormat>
#include <QRegularExpression>

DisassemblyHighlighter::DisassemblyHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {

    QTextCharFormat addressFormat;
    addressFormat.setForeground(QColor("#808080")); // Gray
    rules.append({ QRegularExpression(R"(^0x[0-9a-fA-F]+)"), addressFormat });

    QTextCharFormat mnemonicFormat;
    mnemonicFormat.setForeground(QColor("#FFA500")); // Orange
    mnemonicFormat.setFontWeight(QFont::Bold);
    rules.append({ QRegularExpression(R"(\b[a-zA-Z]{2,7}\b)"), mnemonicFormat });

    QTextCharFormat operandFormat;
    operandFormat.setForeground(QColor("#87CEFA")); // Light Blue
    rules.append({ QRegularExpression(R"(\b(eax|ebx|ecx|edx|r\d+|rsp|rbp|rip|esi|edi)\b)"), operandFormat });

    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor("#dcdcaa")); // Light Yellow
    rules.append({ QRegularExpression(R"(0x[0-9a-fA-F]+|\b\d+\b)"), numberFormat });

    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor("#6A9955")); // Green
    rules.append({ QRegularExpression(R"(;.*$)"), commentFormat });
}

void DisassemblyHighlighter::highlightBlock(const QString& text) {
    for (const auto& rule : rules) {
        QRegularExpressionMatchIterator matchIt = rule.pattern.globalMatch(text);
        while (matchIt.hasNext()) {
            QRegularExpressionMatch match = matchIt.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
