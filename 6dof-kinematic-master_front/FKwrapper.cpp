#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h> // Include the <pybind11/stl.h> header

// Include your original C++ header
#include "6dof-kinematic.hpp" // Replace with the actual header name

namespace py = pybind11;

std::vector<float> SolveFKWrapper(py::object inputJoint6D) {
    // Convert inputJoint6D to your C++ types if necessary
    DOF6Kinematic::Joint6D_t input;
    
    
    
    py::list inputList = py::cast<py::list>(inputJoint6D);

    if (inputList.size() != 6) {
        throw std::runtime_error("Input list must contain 6 elements");
    }

    input.a[0] = py::cast<float>(inputList[0]);
    input.a[1] = py::cast<float>(inputList[1]);
    input.a[2] = py::cast<float>(inputList[2]);
    input.a[3] = py::cast<float>(inputList[3]);
    input.a[4] = py::cast<float>(inputList[4]);
    input.a[5] = py::cast<float>(inputList[5]);
    // Extract the values for the constructor parameters from your Python objects
    float L_BS = 152.5; 
    float D_BS = 0; 
    float L_AM = 620; 
    float L_FA = 559; 
    float D_EW = 0; 
    float L_WT = 121; 

    // Create an instance of DOF6Kinematic with the constructor parameters
    DOF6Kinematic dof6Kinematic(L_BS, D_BS, L_AM, L_FA, D_EW, L_WT);
    
    // Call your original C++ function
    DOF6Kinematic::Pose6D_t output;
    dof6Kinematic.SolveFK(input, output);
    // Convert the result to a Python list
    std::vector<float> outputValues = {output.X, output.Y, output.Z, output.A, output.B, output.C};

    return outputValues;
}

PYBIND11_MODULE(FK_module, m) {
    m.def("SolveFK", &SolveFKWrapper, "Solve Forward Kinematics");
}
