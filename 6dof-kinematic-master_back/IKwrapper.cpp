#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h> // Include the <pybind11/stl.h> header

// Include your original C++ header
#include "6dof-kinematic.hpp" // Replace with the actual header name

namespace py = pybind11;

std::vector<float> SolveFKWrapper(py::object inputPose6D) {
    // Convert inputJoint6D to your C++ types if necessary
    DOF6Kinematic::Pose6D_t input;
    py::list inputList = py::cast<py::list>(inputPose6D);

    if (inputList.size() != 6) {
        throw std::runtime_error("Input list must contain 6 elements");
    }

    input.X = py::cast<float>(inputList[0]);
    input.Y = py::cast<float>(inputList[1]);
    input.Z = py::cast<float>(inputList[2]);
    input.A = py::cast<float>(inputList[3]);
    input.B = py::cast<float>(inputList[4]);
    input.C = py::cast<float>(inputList[5]);
    
    float L_BS = 152.5; 
    float D_BS = 0; 
    float L_AM = 620; 
    float L_FA = 559; 
    float D_EW = 0; 
    float L_WT = 121; 

    // Create an instance of DOF6Kinematic with the constructor parameters
    DOF6Kinematic dof6Kinematic(L_BS, D_BS, L_AM, L_FA, D_EW, L_WT);
    
    
    DOF6Kinematic::Joint6D_t lastJoint6D;
    DOF6Kinematic::IKSolves_t outputSolves;
    // Call your original C++ function
    dof6Kinematic.SolveIK(input, lastJoint6D, outputSolves);
    

    // Convert the result 
    std::vector<float> outputValues = {outputSolves.config[0].a[0],outputSolves.config[0].a[1],outputSolves.config[0].a[2],outputSolves.config[0].a[3],outputSolves.config[0].a[4],outputSolves.config[0].a[5]};
    
    return outputValues;
}

PYBIND11_MODULE(FK_module, m) {
    m.def("SolveFK", &SolveFKWrapper, "Solve Forward Kinematics");
}
