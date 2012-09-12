//////////////////////////////////////////////////////////////////////////
// License & Copyright
// ===================
// 
// Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////

// Standard Template Library //
#include <vector>
#include <iostream>

// fprint Lbirary //
#include <libfprint/fprint.h>

// boost::python //
#include "boost/python.hpp"
#include "boost/python/converter/builtin_converters.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"


using namespace std;
using namespace boost::python;


class Reader {
  public:
    Reader() {
        this->connected = false;
        int r = fp_init();
        if (r < 0) {
            PyErr_SetString(PyExc_RuntimeError, "Could not initialise fprint.");
            throw error_already_set(); 
        }

        this->discovered_devs = fp_discover_devs();
        if (!this->discovered_devs) {
            PyErr_SetString(PyExc_RuntimeError, "Cound not start device discovery.");
            throw error_already_set(); 
        }

        if (!this->discovered_devs[0]) {
            PyErr_SetString(PyExc_RuntimeError, "No finger print devices found.");
            throw error_already_set(); 
        }

        devs = 0;
        struct fp_dscv_dev *dev;
        for (int i=0; (dev = this->discovered_devs[i]); i++) {
            devs++;
        }

        // If only one device is found, automatically connect to it.
        if (devs == 1) {
            connect(0);
        }

        // Only 10 possible fingers (device limitation)
        for (int i=0; i<10; i++) {
            fp_print_data *print = NULL;
            prints.push_back(print);
        }
    };

    void del() {
        disconnect();
    };

  public:
    void connect(int index){ 
        if (this->connected) {
            PyErr_SetString(PyExc_RuntimeError, "Already connected to a device.");
            throw error_already_set(); 
        }
    
        this->ddev = this->discovered_devs[index];
        this->drv = fp_dscv_dev_get_driver(this->ddev);

        this->dev = fp_dev_open(this->ddev);
        fp_dscv_devs_free(this->discovered_devs);
        this->connected = true;
    };

    bool enroll(int digit) {
        int status = fp_enroll_finger(this->dev, &prints[digit]);
  
       if (status == 1) {
            return true;
        } else {
            return false;
        }
    };

    bool verify(int digit) {
        int status = fp_verify_finger(this->dev, prints[digit]);
        
        if (status == 1) {
            return true;
        } else {
            return false;
        }
    };

    void identify() {
        PyErr_SetString(PyExc_NotImplementedError, "Print ID is not currently supported.");
        throw error_already_set(); 
    };

    void disconnect() {
        if (this->dev) {
            fp_dev_close(this->dev);
        }
        fp_exit();
    };

    str driver_name() {
        if (this->connected) {
            return (str) fp_driver_get_full_name(this->drv);
        } 
        return "";
    };

    int enroll_stages() {
        if (this->connected) {
            return fp_dev_get_nr_enroll_stages(this->dev);
        }
        return 0;
    };

    bool enrolled(int digit) {
        if (this->prints[digit])  {
            return true; 
        }
        return false;
    };

  private:
    vector<fp_print_data*> prints;

    struct fp_dscv_dev *ddev;
    struct fp_dscv_dev **discovered_devs;
    struct fp_dev *dev;
    struct fp_driver *drv;

    int devs;
    bool connected;
};


BOOST_PYTHON_MODULE(libfprynt) {
    class_<Reader, Reader*>("Reader")
        .def("__del__", &Reader::del)
        .def("connect", &Reader::connect)
        .def("disconnect", &Reader::disconnect)
        .def("enroll", &Reader::enroll)
        .def("verify", &Reader::verify)
        .def("enrolled", &Reader::enrolled)
        .add_property("enroll_stages", &Reader::enroll_stages)
        .add_property("driver_name", &Reader::driver_name)
    ; 
}

