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

namespace py = pybind11;
int main() {
  // Prepare the data...
  const Eigen::VectorXd xv_data = Eigen::VectorXd::LinSpaced(10000, -4, 4);
  const Eigen::VectorXd yv_data =
      xv_data.unaryExpr([](double it) { return tgamma(it); });

  // Embed the interpreter in the current scope
  py::scoped_interpreter interp{};

  // Import the module, similar to `import matplotlib.pyplot as plt`
  auto plt = py::module::import("matplotlib.pyplot");

  // Pybind11 does namespace/member resolution by `().attr("name")`.
  // Bring in `plot` etc. like `from matplotlib.pyplot import plot`
  auto plot = plt.attr("plot");
  auto show = plt.attr("show");
  auto ylim = plt.attr("ylim");
  auto savefig = plt.attr("savefig");

  // Use the following py::array ctor to map an existing buffer
  // https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
  py::array xv(xv_data.size(), xv_data.data());
  py::array yv(yv_data.size(), yv_data.data());

  // plot and show!
  plot(xv, yv, "r--");
  ylim(-10, 10);
  savefig("res/readme.png");
  show();
}