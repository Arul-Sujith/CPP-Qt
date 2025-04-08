#include "HexDumpWidget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QScrollBar>
#include <QDebug>
#include <QWidget>

HexDumpWidget::HexDumpWidget(QWidget *parent) : QDockWidget("Hex Dump", parent) {
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);

    openButton = new QPushButton("Open File", this);
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    layout->addWidget(openButton);
    layout->addWidget(textEdit);
    layout->setContentsMargins(4, 4, 4, 4);

    container->setLayout(layout);
    setWidget(container);

    connect(openButton, &QPushButton::clicked, this, &HexDumpWidget::openFile);
}

void HexDumpWidget::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File");
    if (filePath.isEmpty()) {
        qDebug() << "[INFO] No file selected.";
        return;
    }

    qDebug() << "[INFO] File selected:" << filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        qDebug() << "[INFO] File size:" << data.size();

        if (data.size() > 1024 * 1024) {
            qDebug() << "[WARN] File too large, truncating to 1MB.";
            data = data.left(1024 * 1024);
        }

        renderHexDump(data);
    } else {
        qDebug() << "[ERROR] Failed to open file.";
    }
}

void HexDumpWidget::renderHexDump(const QByteArray &data) {
    textEdit->clear();
    QTextCursor cursor = textEdit->textCursor();

    QTextCharFormat offsetFormat, hexFormat, asciiFormat;

    offsetFormat.setForeground(QColor("#FFA500"));  // Orange
    hexFormat.setForeground(QColor("#00FFFF"));     // Cyan
    asciiFormat.setForeground(QColor("#7CFC00"));   // Green

    int dataSize = data.size();

    for (int i = 0; i < dataSize; i += 16) {
        cursor.insertText(QString("%1  ").arg(i, 8, 16, QLatin1Char('0')).toUpper(), offsetFormat);

        for (int j = 0; j < 16; ++j) {
            if (i + j < dataSize) {
                uchar byte = static_cast<uchar>(data[i + j]);
                cursor.insertText(QString("%1 ").arg(byte, 2, 16, QLatin1Char('0')).toUpper(), hexFormat);
            } else {
                cursor.insertText("   ");
            }
        }

        cursor.insertText("  ");

        for (int j = 0; j < 16; ++j) {
            if (i + j < dataSize) {
                uchar byte = static_cast<uchar>(data[i + j]);
                QChar ch = (byte >= 32 && byte <= 126) ? QChar(byte) : '.';
                cursor.insertText(ch, asciiFormat);
            } else {
                cursor.insertText(" ");
            }
        }

        cursor.insertBlock();
    }

    textEdit->verticalScrollBar()->setValue(0);
}
