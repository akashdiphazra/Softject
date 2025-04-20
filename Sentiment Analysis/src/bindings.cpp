#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "classifier.hpp"

namespace py = pybind11;

PYBIND11_MODULE(sentiment_model, m) {
  py::class_<NaiveBayes>(m, "NaiveBayes")
      .def(py::init<>())
      .def("train", &NaiveBayes::train)
      .def("predict", &NaiveBayes::predict);
}
