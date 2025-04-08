#ifndef HEXDUMPWIDGET_H
#define HEXDUMPWIDGET_H

#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>


class HexDumpWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit HexDumpWidget(QWidget *parent = nullptr);
    void loadFile(const QString &filePath);

private slots:
    void openFile();

private:
    QTextEdit *textEdit;
    QPushButton *openButton;
    QString toHexDump(const QByteArray &data);
    void renderHexDump(const QByteArray &data);
};

#endif // HEXDUMPWIDGET_H
