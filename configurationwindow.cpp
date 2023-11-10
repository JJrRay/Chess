#include "configurationwindow.h"
#include <QVBoxLayout>
#include <QPushButton>


ConfigurationWindow::ConfigurationWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* config1Button = createConfigButton("Configuration 1");
    layout->addWidget(config1Button);
    connect(config1Button, &QPushButton::clicked, this, &ConfigurationWindow::onButtonClicked);

    QPushButton* config2Button = createConfigButton("Configuration 2");
    layout->addWidget(config2Button);
    connect(config2Button, &QPushButton::clicked, this, &ConfigurationWindow::onButtonClicked);

    QPushButton* config3Button = createConfigButton("Configuration 3");
    layout->addWidget(config3Button);
    connect(config3Button, &QPushButton::clicked, this, &ConfigurationWindow::onButtonClicked);
}

QPushButton* ConfigurationWindow::createConfigButton(const QString& text)
{
    QPushButton* button = new QPushButton(text, this);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return button;
}

void ConfigurationWindow::onButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int config = (clickedButton->text() == "Configuration 1") ? 1 : (clickedButton->text() == "Configuration 2") ? 2 : 3;
    emit configurationSelected(config);
}
