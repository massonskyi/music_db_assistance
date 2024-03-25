#include <iostream>
#include <format>
#include "../includes/functiontools.h"

namespace ft{
    void print_info::operator()(const std::string& info) {
        std::cout << info << std::endl;
    }


    int get_mp3_info_py(const std::string& filename) {
        Py_Initialize();  // Initialize Python interpreter

        // Import the Python module
        PyObject* mp3_tools_module = PyImport_ImportModule("scripts/mp3tools");
        if (!mp3_tools_module) {
            PyErr_Print();  // Print Python error if module not found
            return 1;
        }

        // Get the function object
        PyObject* get_mp3_info_func = PyObject_GetAttrString(mp3_tools_module, "get_mp3_info");
        if (!get_mp3_info_func) {
            PyErr_Print();  // Print Python error if function not found
            return 1;
        }

        // Call the function with the filename
        PyObject* result = PyObject_CallFunction(get_mp3_info_func, "s", filename.c_str());
        if (!result) {
            PyErr_Print();  // Print Python error if function call fails
            return 1;
        }

        // Extract the title and artist from the returned dictionary
        PyObject* title_obj = PyDict_GetItemString(result, "title");
        PyObject* artist_obj = PyDict_GetItemString(result, "artist");


        const char* title_cstr = PyUnicode_AsUTF8(title_obj);
        const char* artist_cstr = PyUnicode_AsUTF8(artist_obj);
        // Check for conversion errors
        if (!title_cstr || !artist_cstr) {
            PyErr_Print();  // Print Python error if conversion fails
            Py_DECREF(result);
            Py_DECREF(get_mp3_info_func);
            Py_DECREF(mp3_tools_module);
            Py_Finalize();
            return 1;
        }
        // Use the converted C strings
        std::string title(title_cstr);
        std::string artist(artist_cstr);

        // Print or use the retrieved information
        std::cout << "Title: " << title << std::endl;
        std::cout << "Artist: " << artist << std::endl;

        Py_DECREF(result);
        Py_DECREF(get_mp3_info_func);
        Py_DECREF(mp3_tools_module);
        Py_Finalize();  // Finalize Python interpreter
        return 0;
    }
}