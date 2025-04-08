#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HexDumpWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;

private:
    HexDumpWidget *hexDump;

    void setupMenu();
    void setupDockWidgets();
    void restoreLayout();
    void saveLayout();

    void applyTheme(bool dark); // 👈 ADD THIS LINE
};

#endif // MAINWINDOW_H
