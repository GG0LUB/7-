#ifndef TEST_POLYNOMIAL_H
#define TEST_POLYNOMIAL_H

void testPolynomialDefaultConstructor();
void testPolynomialParameterizedConstructor();
void testPolynomialCopyConstructor(); // Должна быть объявлена
void testPolynomialEvaluate();
void testPolynomialToString();
void testPolynomialCount(); // Должна быть объявлена
void testPolynomialInputOutput();
void testPolynomialSaveToTextFile();
void testPolynomialLoadFromTextFile();
void testArrayBasedPolynomial();
void testArrayBasedPolynomialEvaluate();
void testStringBasedPolynomial();
void testHeapAllocation();
void testLocalObjects();
void testEvaluateWithHeapObjects();
void testRAII();
void testMemoryAllocationFailure();
void testOutOfRangeException();
void testDivisionByZero();
void testInvalidPolynomialCreation();
void testUninitializedCoefficients();
void testArrayBasedPolynomialToString();

#endif  // TEST_POLYNOMIAL_H
