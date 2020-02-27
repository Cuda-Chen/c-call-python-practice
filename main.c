#include <Python.h>

#include <stdio.h>

int add(int a, int b)
{
    PyObject *pModule, *pFunc, *pArgs, *pKargs = NULL, *pRes;
    int result;

    // import `speedup` module and `add` function
    pModule = PyImport_Import(PyUnicode_FromString("speedup"));
    pFunc = PyObject_GetAttrString(pModule, "add");

    // pack arguments to PyObject
    pArgs = Py_BuildValue("ii", a, b);

    // invode the function
    pRes = PyObject_Call(pFunc, pArgs, pKargs);

    // check if invoke failed
    if(pRes == NULL)
        return -1;
    result = PyLong_AsLong(pRes);

    // free
    Py_DECREF(pModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pKargs);
    Py_DECREF(pRes);

    return result;
}

int main()
{
    // initialize Python intepretor
    Py_Initialize();

    // set Python search path
    PySys_SetPath(Py_DecodeLocale(".", NULL));

    // invode add function
    printf("%d\n", add(1, 2));
    
    // free the allocated resources
    Py_Finalize();

    return 0;
}
