#pragma once
#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QWidget>
#include <QPushButton>

class ConfigurationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationWindow(QWidget* parent = nullptr);

signals:
    void configurationSelected(int config);

private slots:
    void onButtonClicked();

private:
    QPushButton* createConfigButton(const QString& text);
};

#endif // CONFIGURATIONWINDOW_H
