#include "MainWindow.h"
#include "HexDumpWidget.h"
#include <QMenuBar>
#include <QMenu>
#include <QSettings>
#include <QDockWidget>
#include <QCloseEvent>
#include <QApplication>  // 👈 ADD THIS LINE


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hexDump(new HexDumpWidget(this)) {
    setWindowTitle("Dockable Hex Dump App");
    resize(800, 600);

    setupMenu();
    setupDockWidgets();
    restoreLayout();
}

void MainWindow::setupMenu() {
    QMenu *viewMenu = menuBar()->addMenu("View");

    QAction *toggleThemeAction = new QAction("Toggle Dark Theme", this);
    toggleThemeAction->setCheckable(true);

    // Load previous theme setting
    QSettings settings("DockHexApp", "Settings");
    bool isDark = settings.value("darkTheme", true).toBool();
    toggleThemeAction->setChecked(isDark);
    applyTheme(isDark);

    connect(toggleThemeAction, &QAction::toggled, this, [=](bool checked) {
        applyTheme(checked);
        QSettings settings("DockHexApp", "Settings");
        settings.setValue("darkTheme", checked);
    });

    viewMenu->addAction(toggleThemeAction);
}

void MainWindow::applyTheme(bool dark) {
    QString darkStyle = R"(
        QWidget {
            background-color: #1e1e1e;
            color: #dcdcdc;
            font-family: Consolas, monospace;
            font-size: 13px;
        }
        QTextEdit {
            background-color: #2d2d2d;
            color: #00ffcc;
            padding: 8px;
            border: 1px solid #444;
        }
        QMenuBar, QMenu {
            background-color: #222;
            color: #fff;
        }
        QMenu::item:selected {
            background-color: #444;
        }
    )";

    QString lightStyle = ""; // default Qt light theme

    qApp->setStyleSheet(dark ? darkStyle : lightStyle);
}


void MainWindow::setupDockWidgets() {
    QDockWidget *dock = new QDockWidget("Hex Dump", this);
    dock->setWidget(hexDump);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainWindow::restoreLayout() {
    QSettings settings("YourOrg", "DockHexApp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
}

void MainWindow::saveLayout() {
    QSettings settings("YourOrg", "DockHexApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveLayout();
    QMainWindow::closeEvent(event);
}
