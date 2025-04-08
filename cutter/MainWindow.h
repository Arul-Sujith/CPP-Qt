#pragma once

#include <QMainWindow>
#include <QPushButton>
#include "Disassembler.h"
#include "DisassemblyView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void toggleTheme();
    void openAndDisassembleFile();

private:
    bool darkTheme = true;
    Disassembler disassembler;
    DisassemblyView* view;
};
