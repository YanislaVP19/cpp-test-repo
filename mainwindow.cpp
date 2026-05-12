#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    SetExtraKey(std::nullopt);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_key_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = cb;
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (!key.has_value() || key->empty()) {
        ui->tb_extra->hide();
    } else {
        ui->tb_extra->setText(QString::fromStdString(*key));
        ui->tb_extra->show();
    }
}

void MainWindow::on_tb_zero_clicked()
{
    digit_cb_(0);
}


void MainWindow::on_tb_one_clicked()
{
    digit_cb_(1);
}


void MainWindow::on_tb_two_clicked()
{
    digit_cb_(2);
}


void MainWindow::on_tb_three_clicked()
{
    digit_cb_(3);
}


void MainWindow::on_tb_four_clicked()
{
    digit_cb_(4);
}


void MainWindow::on_tb_five_clicked()
{
    digit_cb_(5);
}


void MainWindow::on_tb_six_clicked()
{
    digit_cb_(6);
}


void MainWindow::on_tb_seven_clicked()
{
    digit_cb_(7);
}


void MainWindow::on_tb_eight_clicked()
{
    digit_cb_(8);
}


void MainWindow::on_tb_nine_clicked()
{
    digit_cb_(9);
}


void MainWindow::on_tb_extra_clicked()
{
    control_key_cb_(ControlKey::EXTRA_KEY);
}


void MainWindow::on_tb_negate_clicked()
{
    control_key_cb_(ControlKey::PLUS_MINUS);
}


void MainWindow::on_tb_backspace_clicked()
{
    control_key_cb_(ControlKey::BACKSPACE);
}




void MainWindow::on_tb_add_clicked()
{
    operation_cb_(Operation::ADDITION);
}


void MainWindow::on_tb_substract_clicked()
{
    operation_cb_(Operation::SUBTRACTION);
}


void MainWindow::on_tb_multiplicate_clicked()
{
    operation_cb_(Operation::MULTIPLICATION);
}


void MainWindow::on_tb_divide_clicked()
{
    operation_cb_(Operation::DIVISION);
}


void MainWindow::on_tb_power_clicked()
{
    operation_cb_(Operation::POWER);
}


void MainWindow::on_tb_equal_clicked()
{
    control_key_cb_(ControlKey::EQUALS);
}


void MainWindow::on_tb_reset_clicked()
{
    control_key_cb_(ControlKey::CLEAR);
}


void MainWindow::on_tb_mc_clicked()
{
    control_key_cb_(ControlKey::MEM_CLEAR);
}


void MainWindow::on_tn_mr_clicked()
{
    control_key_cb_(ControlKey::MEM_LOAD);
}


void MainWindow::on_tb_ms_clicked()
{
    control_key_cb_(ControlKey::MEM_SAVE);
}


void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    QString text = ui->cmb_controller->currentText();
    ControllerType type;
    if (text == "uint8_t") {
        type = ControllerType::UINT8_T;
    } else if (text == "int") {
        type = ControllerType::INT;
    } else if (text == "int64_t") {
        type = ControllerType::INT64_T;
    } else if (text == "size_t") {
        type = ControllerType::SIZE_T;
    } else if (text == "double") {
        type = ControllerType::DOUBLE;
    } else if (text == "float") {
        type = ControllerType::FLOAT;
    } else if (text == "Rational") {
        type = ControllerType::RATIONAL;
    } else {
        return;
    }
    controller_cb_(type);
}

