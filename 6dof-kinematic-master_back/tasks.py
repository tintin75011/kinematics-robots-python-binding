import invoke
import pathlib
import sys
import os
import shutil
import re
import glob


on_win = sys.platform.startswith("win")

@invoke.task
def clean(c):
    """Remove any built objects"""
    for file_pattern in (
        "*.o",
        "*.so",
        "*.obj",
        "*.dll",
        "*.exp",
        "*.lib",
        "*.pyd",
        "cffi_example*",  # Is this a dir?
        "cython_wrapper.cpp",
    ):
        for file in glob.glob(file_pattern):
            os.remove(file)
    for dir_pattern in "Release":
        for dir in glob.glob(dir_pattern):
            shutil.rmtree(dir)

def print_banner(msg):
    print("==================================================")
    print("= {} ".format(msg))




@invoke.task()
def build_kin(c):
    """Build the shared library for the sample C++ code"""
    print_banner("Building C++ Library")
    print_banner("1")
    invoke.run(
        "g++ -O3 -Wall -Werror -shared -std=c++11 -fPIC 6dof-kinematic.cpp "
        "-o libcpp6dof-kinematic.so "
    )
    print("* Complete")


def compile_python_module(cpp_name, extension_name):
    print_banner("3")
    invoke.run(
        "g++ -O3 -Wall -Werror -shared -std=c++11 -fPIC "
        "`python3 -m pybind11 --includes` "
        "-I . "
        "{0} "
        "-o {1}`python3-config --extension-suffix` "
        "-L. -lcpp6dof-kinematic -Wl,-rpath,.".format(cpp_name, extension_name)
    )


@invoke.task(build_kin)
def build_pybind11(c):
    """Build the pybind11 wrapper library"""
    print_banner("Building PyBind11 Module")
    print_banner("2")
    compile_python_module("IKwrapper.cpp", "FK_module")
    print("* Complete")


@invoke.task(build_pybind11)
def test_Bkin(c):
    """Run the script to test PyBind11"""
    print_banner("Testing PyBind11 Module")
    invoke.run("python3 Bkin.py", pty=True)



def all(c):
    """Build and run all tests"""
    pass

