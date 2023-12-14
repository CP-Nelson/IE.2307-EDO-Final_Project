#include <stdio.h>
#define INPUT_SIZE 59
// Function to calculate the mean of an array
double calculate_mean(const double arr[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
    }
    return sum / size;
}

// Function to reduce variance by smoothing each row in a 2-D array
void reduce_variance_2d(double arr[][INPUT_SIZE], int rows, int cols, int window_size)
{
    if (window_size < 1)
    {
        printf("Error: Window size must be greater than or equal to 1.\n");
        return;
    }

    double smoothed_arr[rows][cols];

    // Apply smoothing to each row in the 2-D array
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int start = j - window_size / 2;
            int end = j + window_size / 2;

            // Ensure the window is within bounds
            start = (start < 0) ? 0 : start;
            end = (end >= cols) ? cols - 1 : end;

            // Calculate the mean of the elements in the window
            smoothed_arr[i][j] = calculate_mean(arr[i] + start, end - start + 1);
        }
    }

    // Copy the smoothed values back to the original array
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            arr[i][j] = smoothed_arr[i][j];
        }
    }
}

int main()
{
    // Example usage
    double values[][59] = {{1.95, 1.95, 1.94, 1.95, 1.95, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.94, 1.95, 1.94, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.94, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95, 1.95}, {1.85, 1.86, 1.85, 1.85, 1.85, 1.86, 1.86, 1.86, 1.86, 1.86, 1.86, 1.86, 1.86, 1.86, 1.86, 1.87, 1.87, 1.87, 1.87, 1.87, 1.88, 1.88, 1.88, 1.89, 1.89, 1.89, 1.89, 1.89, 1.89, 1.88, 1.88, 1.88, 1.88, 1.87, 1.88, 1.88, 1.88, 1.88, 1.88, 1.87, 1.87, 1.87, 1.86, 1.84, 1.84, 1.83, 1.83, 1.83, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.83, 1.82, 1.82, 1.82, 1.82}, {1.77, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.76, 1.77, 1.77, 1.77, 1.78, 1.77, 1.77, 1.77, 1.77, 1.77, 1.77, 1.77, 1.78, 1.77, 1.78, 1.78, 1.78, 1.78, 1.77, 1.77, 1.78, 1.77, 1.77, 1.78, 1.78, 1.78, 1.78, 1.78, 1.78, 1.77, 1.77, 1.78, 1.77, 1.77, 1.77, 1.77, 1.77, 1.77, 1.78, 1.79, 1.79, 1.79, 1.79, 1.79, 1.79, 1.80}, {1.63, 1.64, 1.64, 1.64, 1.64, 1.64, 1.64, 1.64, 1.64, 1.64, 1.63, 1.63, 1.63, 1.63, 1.63, 1.63, 1.64, 1.64, 1.63, 1.63, 1.63, 1.62, 1.62, 1.62, 1.62, 1.61, 1.61, 1.61, 1.61, 1.61, 1.61, 1.61, 1.62, 1.62, 1.62, 1.62, 1.62, 1.62, 1.62, 1.62, 1.62, 1.61, 1.61, 1.61, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.59, 1.59}, {1.53, 1.53, 1.53, 1.53, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.55, 1.55, 1.55, 1.55, 1.55, 1.55, 1.55, 1.55, 1.55, 1.55, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.54, 1.55, 1.55, 1.56, 1.55, 1.56, 1.56, 1.56, 1.56, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.56, 1.56, 1.56, 1.56, 1.56, 1.56, 1.56, 1.55, 1.55}, {1.40, 1.40, 1.39, 1.40, 1.40, 1.40, 1.40, 1.40, 1.39, 1.40, 1.41, 1.41, 1.41, 1.41, 1.40, 1.40, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.42, 1.42, 1.42, 1.43, 1.42, 1.42, 1.42, 1.42, 1.41, 1.41, 1.40, 1.41, 1.40, 1.41, 1.41, 1.41, 1.42, 1.42, 1.43, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.44, 1.45, 1.45, 1.45, 1.45, 1.45}};

    int rows = sizeof(values) / sizeof(values[0]);
    int cols = sizeof(values[0]) / sizeof(values[0][0]);

    printf("Original values:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%f ", values[i][j]);
        }
        printf("\n");
    }

    reduce_variance_2d(values, rows, cols, 8);

    printf("\nValues after reducing variance:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%.2f ", values[i][j]);
        }
        printf("\n");
    }

    return 0;
}