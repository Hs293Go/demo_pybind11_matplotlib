// Copyright (c) 2022 hs293go
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <pybind11/attr.h>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include <Eigen/Dense>
#include <cmath>

#define IMPORT_FROM(m, fn) auto fn = m.attr(#fn);

namespace py = pybind11;
using namespace pybind11::literals;
int main() {
  const Eigen::VectorXd xv_data = Eigen::VectorXd::LinSpaced(10000, -4, 4);
  const Eigen::VectorXd yv_data =
      xv_data.unaryExpr([](double it) { return tgamma(it); });

  py::scoped_interpreter interp{};
  auto sns = py::module::import("seaborn");
  IMPORT_FROM(sns, set_style);
  set_style("darkgrid");

  auto plt = py::module::import("matplotlib.pyplot");
  IMPORT_FROM(plt, plot);
  IMPORT_FROM(plt, show);
  IMPORT_FROM(plt, ylim);
  IMPORT_FROM(plt, legend);
  IMPORT_FROM(plt, xlabel);
  IMPORT_FROM(plt, ylabel);
  IMPORT_FROM(plt, title);
  IMPORT_FROM(plt, savefig);

  py::array xv(xv_data.size(), xv_data.data());
  py::array yv(yv_data.size(), yv_data.data());

  plot(xv, yv, "--", "linewidth"_a = 3,
       "color"_a = py::make_tuple(0, 0.4, 0.8, 0.6),
       "label"_a = "Function Value");
  ylim(py::make_tuple(-10, 10));
  xlabel("x");
  ylabel(R"($f(x) = \gamma(x)$)");
  title(R"(Gamma Function: $\gamma(z) = \int_0^\infty x^{z-1} e^{-x} dx$)",
        "fontsize"_a = 18);
  savefig("res/detailed.png");
  show();
}