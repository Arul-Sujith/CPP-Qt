#include "MainWindow.h"
#include "DisassemblyView.h"
#include "DisassemblyHighlighter.h"
#include "Disassembler.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), darkTheme(true) {
    // Central widget setup
    auto* central = new QWidget;
    auto* layout = new QVBoxLayout(central);
    setCentralWidget(central);

	layout->setContentsMargins(8, 8, 8, 8);
	layout->setSpacing(4);
	
    // Disassembly view setup
    view = new DisassemblyView(this);
    new DisassemblyHighlighter(view->document());
    layout->addWidget(view);

    // Menu bar
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // File menu
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* openAction = fileMenu->addAction("Open File");
    connect(openAction, &QAction::triggered, this, &MainWindow::openAndDisassembleFile);

    // View menu
    QMenu* viewMenu = menuBar->addMenu("View");
    QAction* toggleThemeAction = viewMenu->addAction("Toggle Light/Dark");
    connect(toggleThemeAction, &QAction::triggered, this, &MainWindow::toggleTheme);

    resize(600, 400);
}

MainWindow::~MainWindow() = default;

void MainWindow::toggleTheme() {
    if (!darkTheme) {
        qApp->setStyleSheet(R"(
            QMainWindow {
                background-color: #1e1e1e;
                color: #cccccc;
            }
            QPlainTextEdit {
                background-color: #1e1e1e;
                color: #cccccc;
                font-family: Consolas, monospace;
                font-size: 14px;
            }
            QMenuBar {
                background-color: #2e2e2e;
                color: #ffffff;
            }
            QMenuBar::item:selected {
                background: #3e3e3e;
            }
            QMenu {
                background-color: #2e2e2e;
                color: #ffffff;
            }
            QMenu::item:selected {
                background-color: #444444;
            }
        )");
    } else {
        qApp->setStyleSheet(R"(
            QMainWindow {
                background-color: #ffffff;
                color: #000000;
            }
            QPlainTextEdit {
                background-color: #ffffff;
                color: #000000;
                font-family: Consolas, monospace;
                font-size: 14px;
            }
            QMenuBar {
                background-color: #f0f0f0;
                color: #000000;
            }
            QMenuBar::item:selected {
                background: #d0d0d0;
            }
            QMenu {
                background-color: #ffffff;
                color: #000000;
            }
            QMenu::item:selected {
                background-color: #eeeeee;
            }
        )");
    }

    darkTheme = !darkTheme;
}


void MainWindow::openAndDisassembleFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Binary File");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    QByteArray binaryData = file.readAll();
    file.close();

    auto lines = disassembler.disassemble(reinterpret_cast<const uint8_t*>(binaryData.constData()),
                                          binaryData.size(), 0x1000); // Base address

    view->clear();
    for (const auto& line : lines) {
        view->appendPlainText(QString::fromStdString(line));
    }
}

