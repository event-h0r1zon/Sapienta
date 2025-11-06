#include "velaris/render/VectorRendererWidget.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QString>

#include <algorithm>
#include <array>
#include <cmath>

namespace velaris::render {

VectorRendererWidget::VectorRendererWidget(QWidget* parent)
    : QWidget(parent), vectors_{
        Eigen::Vector3d(1.0, 0.0, 0.0),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, 0.0, 1.0)
    } {}

const std::vector<Eigen::Vector3d>& VectorRendererWidget::vectors() const {
    return vectors_;
}

void VectorRendererWidget::setVectors(std::vector<Eigen::Vector3d> vectors) {
    vectors_ = std::move(vectors);
    update();
}

void VectorRendererWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), QColor(18, 20, 28));

        const QPointF center = rect().center();
    const double scale = std::min(width(), height()) / 3.5;

    const Eigen::Matrix3d view =
        (Eigen::AngleAxisd(-0.6, Eigen::Vector3d::UnitY()) *
         Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitX()))
            .toRotationMatrix();
    const Eigen::Matrix<double, 2, 3> projector =
        (Eigen::Matrix<double, 2, 3>() << 1, 0, 0,
                                          0, 1, 0)
            .finished();

    const auto project = [&](const Eigen::Vector3d& vector) {
        const Eigen::Vector2d projected = projector * view * vector;
        return QPointF(center.x() + projected.x() * scale,
                       center.y() - projected.y() * scale);
    };

    const QPointF origin = project(Eigen::Vector3d::Zero());
    static const std::array<QColor, 3> axisColors{
        QColor(220, 80, 80),   // X
        QColor(90, 200, 110),  // Y
        QColor(80, 150, 240)   // Z
    };
    static const std::array<QString, 3> axisLabels{
        QStringLiteral("X"),
        QStringLiteral("Y"),
        QStringLiteral("Z")
    };

    static const std::array<Eigen::Vector3d, 3> kBasis{
        Eigen::Vector3d(1.0, 0.0, 0.0),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, 0.0, 1.0)
    };

    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));

    for (std::size_t i = 0; i < kBasis.size(); ++i) {
        const QPointF endPoint = project(kBasis[i]);
        painter.drawLine(origin, endPoint);
        painter.drawText(endPoint + QPointF(6, 14), axisLabels[i]);
    }

    for (std::size_t i = 0; i < vectors_.size(); ++i) {
        const auto& vector = vectors_[i];
        const QPointF endPoint = project(vector);

        const QColor color = i < axisColors.size() ? axisColors[i] : QColor(200, 200, 220);
        painter.setPen(QPen(color, 2));

        painter.drawLine(origin, endPoint);
        painter.drawText(endPoint + QPointF(8, -8),
                         QStringLiteral("%1 [%2, %3, %4]")
                             .arg(i < axisLabels.size() ? axisLabels[i] : QStringLiteral("V%1").arg(i + 1))
                             .arg(vector.x(), 0, 'f', 2)
                             .arg(vector.y(), 0, 'f', 2)
                             .arg(vector.z(), 0, 'f', 2));
    }
}

}
