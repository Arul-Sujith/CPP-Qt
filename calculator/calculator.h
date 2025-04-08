#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void buttonClicked();
    void clearDisplay();
    void undoLast();
    void evaluateExpression();
    void switchMode(int index);
    void applyTheme();

private:
    QLineEdit *display;
    QComboBox *modeSelector;
    QPushButton *equalsButton;
    QPushButton *clearButton;
    QPushButton *undoButton;
    QString previousText;

    QWidget *advancedWidget; // <-- added for advanced layout

    void createUI();
    void connectSignals();

protected:
    void keyPressEvent(QKeyEvent *event) override;

};

#endif // CALCULATOR_H
