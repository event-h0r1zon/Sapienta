#pragma once

#include <QWidget>
#include <vector>

#include <Eigen/Dense>

class QPaintEvent;

namespace velaris::render {

class VectorRendererWidget : public QWidget {
public:
    void setVectors(std::vector<Eigen::Vector3d> vectors);
    [[nodiscard]] const std::vector<Eigen::Vector3d>& vectors() const;
    explicit VectorRendererWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<Eigen::Vector3d> vectors_;
};

}  // namespace velaris::render
