#include "test.h"
#include <iostream>
#include "test_circular_queue.h"

int main() {
    /*testPolynomialDefaultConstructor();
    testPolynomialParameterizedConstructor();
    testPolynomialCopyConstructor();
    testPolynomialCount();
    testPolynomialSaveToTextFile();
    testPolynomialLoadFromTextFile();
    testArrayBasedPolynomial();
    testStringBasedPolynomial();*/
    testCircularQueueExceptions();
    /*testHeapAllocation();
    testLocalObjects();
    testEvaluateWithHeapObjects();
    testRAII();*/
    testMemoryAllocationFailure();
    testOutOfRangeException();
    testDivisionByZero();
    testInvalidPolynomialCreation();
    testUninitializedCoefficients();
    testStringBasedPolynomialToString();
    testArrayBasedPolynomialToString();
    testCircularQueueOrder();
    testPolynomialToString();
    testCircularQueueAddRemove();
    testCircularQueueTempl();


    std::cout << "All tests passed!" << std::endl;
    return 0;
}
