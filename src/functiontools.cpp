#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../includes/functiontools.h"
#include "../includes/hpp/out.hpp"
#include <python3.11/Python.h>

namespace ft{
    std::string copy_file_to_buffer_python(const std::string& filepath) {
        Py_Initialize();
        PyRun_SimpleString("import sys\n"
                           "sys.path.append('/home/user064/CLionProjects/music_db/scripts')");
        PyRun_SimpleString("print(sys.path)\nprint('version script 0.1')");
        PyObject* pModule = PyImport_ImportModule("mp3tools");
        if (pModule) {
            PyObject* pFunction = PyObject_GetAttrString(pModule, "copy_file_to_buffer");
            if (pFunction && PyCallable_Check(pFunction)) {
                PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(filepath.c_str()));
                PyObject* pResult = PyObject_CallObject(pFunction, pArgs);
                if (pResult) {
                    const char* result = PyUnicode_AsUTF8(pResult);
                    std::string file_buffer(result);
                    Py_DECREF(pResult);
                    return file_buffer;
                }
                Py_DECREF(pArgs);
            }
            Py_DECREF(pModule);
        }
        return "";
    }
    std::string move_file_to_directory_python(const std::string& filepath, const std::string& dest_dir) {
        Py_Initialize();
        PyRun_SimpleString("import sys\n"
                           "sys.path.append('/home/user064/CLionProjects/music_db/scripts')");
        PyRun_SimpleString("print(sys.path)\nprint('version script 0.1')");
        PyObject * pModule = PyImport_ImportModule("mp3tools");
        if (pModule) {
            PyObject * pFunction = PyObject_GetAttrString(pModule, "move_file_to_directory");
            if (pFunction && PyCallable_Check(pFunction)) {
                PyObject * pArgs = PyTuple_Pack(2, PyUnicode_FromString(filepath.c_str()),
                                                PyUnicode_FromString(dest_dir.c_str()));
                PyObject * pResult = PyObject_CallObject(pFunction, pArgs);
                if (pResult) {
                    const char *result = PyUnicode_AsUTF8(pResult);
                    std::string new_filepath(result);
                    Py_DECREF(pResult);
                    return new_filepath;
                }
                Py_DECREF(pArgs);
            }
            Py_DECREF(pModule);
        }
        return "";
    }
    std::string move_file_from_buffer_to_directory_python(const std::string& file_buffer,const std::string& filename) {
        Py_Initialize();
        PyRun_SimpleString("import sys\n"
                           "sys.path.append('/home/user064/CLionProjects/music_db/scripts')");

        PyObject *pModule = PyImport_ImportModule("mp3tools");
        if (pModule) {
            PyObject *pFunction = PyObject_GetAttrString(pModule, "move_file_from_buffer");
            if (pFunction && PyCallable_Check(pFunction)) {
                PyObject *pArgs = Py_BuildValue("ss", file_buffer.c_str(), filename.c_str());
                PyObject *pResult = PyObject_CallObject(pFunction, pArgs);
                if (pResult) {
                    const char *result = PyUnicode_AsUTF8(pResult);
                    std::string new_filepath(result);
                    Py_DECREF(pResult);
                    return new_filepath;
                }
                Py_DECREF(pArgs);
            }
            Py_DECREF(pModule);
        }
        return "";
    }
    std::vector<std::pair<const char *, const char *>> get_metadata_from_mp3(const std::string& filepath) {
        Py_Initialize();
        PyRun_SimpleString("import sys\n"
                           "sys.path.append('/home/user064/CLionProjects/music_db/scripts')");
        PyRun_SimpleString("print(sys.path)\nprint('version script 0.1')");
        PyObject* pModule = PyImport_ImportModule("mp3tools");
        if (pModule) {
            PyObject* pFunction = PyObject_GetAttrString(pModule, "get_metadata_from_file");
            if (pFunction && PyCallable_Check(pFunction)) {
                PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(filepath.c_str())); // Replace "path_to_mp3_file" with the actual file path
                PyObject* pResult = PyObject_CallObject(pFunction, pArgs);
                if (pResult) {
                    PyObject *pKeys = PyDict_Keys(pResult);
                    PyObject *pValues = PyDict_Values(pResult);

                    Py_ssize_t size = PyList_Size(pKeys);
                    std::vector<std::pair<const char*, const char*>> metadata(size);
                    for (Py_ssize_t i = 0; i < size; ++i) {
                        PyObject* pKey = PyList_GetItem(pKeys, i);
                        PyObject* pValue = PyList_GetItem(pValues, i);

                        const char* key = PyUnicode_AsUTF8(pKey);
                        const char* value = PyUnicode_AsUTF8(pValue);

                        // out::print(std::format("Metadata: {} = {}", key, value));

                        metadata[i].first = key;
                        metadata[i].second = value;
                    }
                    Py_DECREF(pKeys);
                    Py_DECREF(pValues);
                    Py_DECREF(pResult);
                    if(!metadata.empty())
                        return metadata;
                }
                Py_DECREF(pFunction);
            }
            Py_DECREF(pModule);
        }
        Py_Finalize();

        return {};
    }
}