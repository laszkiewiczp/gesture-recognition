#include "matlabArray.h"

coder::array<double, 2U> matlabArray(int n_samples, double accelData[][3])
{
  coder::array<double, 2U> result;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(n_samples, 3);

  // Loop over the array to initialize each element.
  for (int idx0 = 0; idx0 < result.size(0); idx0++) {
    for (int idx1 = 0; idx1 < 3; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + result.size(0) * idx1] = accelData[idx0][idx1];
    }
  }

  return result;
}