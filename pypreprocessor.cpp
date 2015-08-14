#include <python2.7/Python.h>
#include <algorithm>
#include <vector>
#include <boost/python.hpp>
#include <runtagdetector/python/conversion.h>
#include <runtagdetector/detector/markerdetector.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

namespace py = boost::python;

static py::tuple point_to_tuple(cv::Point2f point) {
    return py::make_tuple(point.x, point.y);
}

static py::list detect_marker_candidates(PyObject* mat) {
    NDArrayConverter converter;
    cv::Mat in = converter.toMat(mat);
    std::vector<nkdhny::PreprocessedCandidate> candidates;
    nkdhny::preprocess(in, candidates);

    py::list ret;

    for(nkdhny::PreprocessedCandidate c: candidates) {
        std::vector<py::tuple> pts(4);
        nkdhny::Marker marker = c.first;
        std::transform(marker.begin(), marker.end(), pts.begin(),
                       [](cv::Point2f p) { return point_to_tuple(p);});

        py::tuple bounding_box = py::make_tuple(
                pts[0], pts[1], pts[2], pts[3]
        );

        cv::Mat img = c.second;
        cv::Mat grey(img.size(), img.type());
        cv::threshold(img, grey, 125, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

        ret.append(py::make_tuple(bounding_box, py::object(py::handle<>(py::borrowed(converter.toNDArray(grey))))));
    }

    return ret;
}

BOOST_PYTHON_MODULE( preprocessor ) {

    py::def("candidates", detect_marker_candidates);
}
