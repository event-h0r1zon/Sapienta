#include "velaris/ui/MainWindow.hpp"

#include <QCursor>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QWidget>

#include "velaris/render/VectorRendererWidget.hpp"

namespace {

Eigen::Matrix3d RotationX(double angle) {
    Eigen::Matrix3d R;
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    R << 1, 0, 0,
         0, c, -s,
         0, s, c;
    return R;
}

Eigen::Matrix3d RotationY(double angle) {
    Eigen::Matrix3d R;
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    R << c, 0, s,
         0, 1, 0,
         -s, 0, c;
    return R;
}

Eigen::Matrix3d RotationZ(double angle) {
    Eigen::Matrix3d R;
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    R << c, -s, 0,
        s, c, 0,
         0, 0, 1;
    return R;
}

}

namespace velaris::ui {

MainWindow::MainWindow() {
    setWindowTitle("Eigen Vector Visualizer");

    auto* central = new QWidget(this);
    auto* layout = new QHBoxLayout(central);
    layout->setContentsMargins(10, 0, 0, 0);
    layout->setSpacing(5);

    auto* renderer = new render::VectorRendererWidget(this);
    renderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(renderer, 1);

    auto* sidePanel = new QWidget(this);
    sidePanel->setFixedWidth(260);
    sidePanel->setStyleSheet("background-color: #20232a; color: #f0f3ff;");

    auto* sideLayout = new QVBoxLayout(sidePanel);
    sideLayout->setContentsMargins(24, 24, 24, 24);
    sideLayout->setSpacing(16);

    auto* heading = new QLabel("Vector Operations", sidePanel);
    QFont headingFont = heading->font();
    headingFont.setPointSize(14);
    headingFont.setBold(true);
    heading->setFont(headingFont);
    sideLayout->addWidget(heading);

    auto rotateX = new QPushButton("Rotate X - 45 deg", sidePanel);
    auto rotateY = new QPushButton("Rotate Y - 45 deg", sidePanel);
    auto rotateZ = new QPushButton("Rotate Z - 45 deg", sidePanel);

    QObject::connect(rotateX, &QPushButton::clicked, [renderer]() {
        auto current_vectors = renderer->vectors();
        for (auto& vec : current_vectors) {
            vec = RotationX(M_PI / 4) * vec;
        }
        renderer->setVectors(std::move(current_vectors));
    });

    QObject::connect(rotateY, &QPushButton::clicked, [renderer]() {
        auto current_vectors = renderer->vectors();
        for (auto& vec : current_vectors) {
            vec = RotationY(M_PI / 4) * vec;
        }
        renderer->setVectors(std::move(current_vectors));
    });

    QObject::connect(rotateZ, &QPushButton::clicked, [renderer]() {
        auto current_vectors = renderer->vectors();
        for (auto& vec : current_vectors) {
            vec = RotationZ(M_PI / 4) * vec;
        }
        renderer->setVectors(std::move(current_vectors));
    });

    for (auto* button : {rotateX, rotateY, rotateZ}) {
        button->setCursor(Qt::PointingHandCursor);
        button->setMinimumHeight(40);
        sideLayout->addWidget(button);
    }

    auto* infoLabel = new QLabel("Renderer placeholder\nVector math TBD", sidePanel);
    infoLabel->setWordWrap(true);
    sideLayout->addStretch();
    sideLayout->addWidget(infoLabel);

    layout->addWidget(sidePanel);

    setCentralWidget(central);
}

} 
