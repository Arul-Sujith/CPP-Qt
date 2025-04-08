#include "calculator.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QStyle>
#include <QStyleFactory>
#include <QJSEngine>
#include <QJSValue>
#include <QComboBox>
#include <QLabel>
#include <QKeyEvent>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createUI();
    connectSignals();
    applyTheme();
}

Calculator::~Calculator() {}

void Calculator::createUI()
{
    display = new QLineEdit;
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(40);
    display->setStyleSheet("font-size: 18px;");

    undoButton = new QPushButton("Undo");
    clearButton = new QPushButton("Clear");
    clearButton->setStyleSheet("background-color: red; color: white;");

    modeSelector = new QComboBox;
    modeSelector->addItem("Basic");
    modeSelector->addItem("Advanced");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(undoButton);
    topLayout->addStretch();
    topLayout->addWidget(modeSelector);
    topLayout->addWidget(clearButton);

    // === Basic Buttons ===
    QGridLayout *grid = new QGridLayout;
    QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    int row = 0, col = 0;
    for (const QString &text : buttons) {
        QPushButton *btn = new QPushButton(text);
        btn->setFixedSize(60, 40);
        if (text == "=") {
            btn->setStyleSheet("background-color: green; color: white;");
            equalsButton = btn;
        }
        grid->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, &Calculator::buttonClicked);
        col++;
        if (col == 4) { col = 0; row++; }
    }

    // === Advanced Buttons ===
    advancedWidget = new QWidget(this);
    QGridLayout *advGrid = new QGridLayout(advancedWidget);
    QStringList advButtons = {"sin", "cos", "tan", "log", "√", "^", "(", ")"};

    row = col = 0;
    for (const QString &text : advButtons) {
        QPushButton *btn = new QPushButton(text);
        btn->setFixedSize(60, 40);
        advGrid->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, &Calculator::buttonClicked);
        col++;
        if (col == 4) { col = 0; row++; }
    }
    advancedWidget->setLayout(advGrid);
    advancedWidget->hide(); // default hidden

    // === Main Layout ===
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(display);
    mainLayout->addLayout(grid);
    mainLayout->addWidget(advancedWidget); // below basic layout

    setLayout(mainLayout);
    setWindowTitle("Qt Calculator");
}

void Calculator::connectSignals()
{
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearDisplay);
    connect(undoButton, &QPushButton::clicked, this, &Calculator::undoLast);
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::evaluateExpression);
    connect(modeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Calculator::switchMode);
}

void Calculator::clearDisplay()
{
    previousText = display->text();
    display->clear();
}

void Calculator::undoLast()
{
    display->setText(previousText);
}

void Calculator::evaluateExpression()
{
    previousText = display->text();
    QString expr = display->text();

    // Replace functions
    expr.replace("cos", "Math.cos");
    expr.replace("sin", "Math.sin");
    expr.replace("tan", "Math.tan");
    expr.replace("log", "Math.log");
    expr.replace("√", "Math.sqrt");
    expr.replace("^", "**");

    // Convert trig input from degrees to radians
    expr.replace(QRegularExpression("Math\\.cos\\(([^\\)]+)\\)"), "Math.cos(toRadians(\\1))");
    expr.replace(QRegularExpression("Math\\.sin\\(([^\\)]+)\\)"), "Math.sin(toRadians(\\1))");
    expr.replace(QRegularExpression("Math\\.tan\\(([^\\)]+)\\)"), "Math.tan(toRadians(\\1))");

    QJSEngine engine;
    engine.evaluate("function toRadians(deg) { return deg * Math.PI / 180; }");

    QJSValue result = engine.evaluate(expr);

    if (result.isError()) {
        display->setText("Syntax Error");
    } else {
        double finalResult = result.toNumber();
        if (qFuzzyCompare(finalResult + 1, 1)) {
            display->setText("0");
        } else {
            display->setText(QString::number(finalResult, 'g', 10));
        }
    }
}


void Calculator::buttonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString buttonText = clickedButton->text();

    if (buttonText == "=") {
        evaluateExpression(); // already connected, fallback
    } else {
        display->setText(display->text() + buttonText);
    }
}

void Calculator::switchMode(int index)
{
    if (index == 1) {
        advancedWidget->show();
    } else {
        advancedWidget->hide();
    }
}

void Calculator::applyTheme()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
    qApp->setPalette(darkPalette);
}

#include <QKeyEvent>

#include <QKeyEvent>  // include at top if not already

void Calculator::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QString keyText = event->text();

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        evaluateExpression();
    } else if (key == Qt::Key_Backspace) {
        undoLast();
    } else if (key == Qt::Key_Escape) {
        clearDisplay();
    
    } else if (QString("0123456789.+-*/()^").contains(keyText)) {
    
        display->setText(display->text() + keyText);
    } else if (keyText == "c") {
        display->setText(display->text() + "cos(");
    } else if (keyText == "s") {
        display->setText(display->text() + "sin(");
    } else if (keyText == "t") {
        display->setText(display->text() + "tan(");
    } else if (keyText == "l") {
        display->setText(display->text() + "log(");
    } else {
        QWidget::keyPressEvent(event);  // fallback
    }
}
