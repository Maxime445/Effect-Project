#include "settingsdialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(
        const QList<QAudioDeviceInfo> &availableInputDevices,
        const QList<QAudioDeviceInfo> &availableOutputDevices,
        QWidget *parent) : QDialog(parent)
      , m_inputDeviceComboBox(new QComboBox(this))
      , m_outputDeviceComboBox(new QComboBox(this))
{
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->setSpacing(2);

    //Populate combo boxes

    QAudioDeviceInfo device;
    foreach (device, availableInputDevices)
        m_inputDeviceComboBox->addItem(device.deviceName(), QVariant::fromValue(device));
    foreach (device, availableOutputDevices)
        m_outputDeviceComboBox->addItem(device.deviceName(), QVariant::fromValue(device));

    //Initialize default devices
    if (!availableInputDevices.empty())
        m_inputDevice = availableInputDevices.front();
    if (!availableOutputDevices.empty())
        m_outputDevice = availableOutputDevices.front();

    //Add widgets to layout
    QHBoxLayout* inputDeviceLayout(new QHBoxLayout);
    QLabel *inputDeviceLabel = new QLabel(tr("Input Device"), this);
    inputDeviceLayout->addWidget(inputDeviceLabel);
    inputDeviceLayout->addWidget(m_inputDeviceComboBox);
    dialogLayout->addLayout(inputDeviceLayout);


    QHBoxLayout* outputDeviceLayout(new QHBoxLayout);
    QLabel *outputDeviceLabel = new QLabel(tr("Output Device"), this);
    outputDeviceLayout->addWidget(outputDeviceLabel);
    outputDeviceLayout->addWidget(m_outputDeviceComboBox);
    dialogLayout->addLayout(outputDeviceLayout);


    // Connect
    connect(m_inputDeviceComboBox, QOverload<int>::of(&QComboBox::activated),
           this, &SettingsDialog::inputDeviceChanged);
    connect(m_outputDeviceComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &SettingsDialog::outputDeviceChanged);

    // Add standard buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialogLayout->addWidget(buttonBox);

    // Connect standard buttons
    connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked,
            this, &SettingsDialog::accept);
    connect(buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked,
            this, &SettingsDialog::reject);

    setLayout(dialogLayout);

}

SettingsDialog::~SettingsDialog()
{

}

void SettingsDialog::inputDeviceChanged(int index)
{
    m_inputDevice = m_inputDeviceComboBox->itemData(index).value<QAudioDeviceInfo>();
}

void SettingsDialog::outputDeviceChanged(int index)
{
    m_outputDevice = m_outputDeviceComboBox->itemData(index).value<QAudioDeviceInfo>();
}