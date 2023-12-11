#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// define neural network paramaters
#define INPUT_SIZE 59
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.01
#define EPOCHS 10000

// define ReLU activated function）
double activation(double x)
{
    return (x > 0) ? x : 0.0;
}

// define neural network weights and bias
double weights[INPUT_SIZE];
double bias;
double training_data[][INPUT_SIZE] = {{1.96, 1.95, 1.95, 1.94, 1.94, 1.94, 1.93, 1.96, 1.94, 1.94, 1.93, 1.93, 1.94, 1.94, 1.95, 1.95, 1.95, 1.94, 1.93, 1.93, 1.94, 1.95, 1.95, 1.95, 1.94, 1.94, 1.94, 1.93, 1.94, 1.95, 1.95, 1.93, 1.94, 1.94, 1.94, 1.94, 1.96, 1.95, 1.96, 1.94, 1.94, 1.94, 1.94, 1.94, 1.95, 1.95, 1.96, 1.94, 1.95, 1.94, 1.94, 1.94, 1.94, 1.96, 1.96, 1.95, 1.94, 1.94, 1.94}, {1.83, 1.85, 1.85, 1.88, 1.86, 1.87, 1.83, 1.85, 1.85, 1.86, 1.86, 1.88, 1.85, 1.87, 1.88, 1.84, 1.86, 1.87, 1.84, 1.9, 1.9, 1.88, 1.88, 1.89, 1.89, 1.86, 1.91, 1.89, 1.92, 1.87, 1.87, 1.9, 1.86, 1.84, 1.89, 1.88, 1.87, 1.89, 1.89, 1.86, 1.92, 1.84, 1.87, 1.85, 1.85, 1.82, 1.8, 1.79, 1.81, 1.82, 1.86, 1.85, 1.82, 1.8, 1.81, 1.82, 1.79, 1.84, 1.84}, {1.74, 1.75, 1.75, 1.81, 1.78, 1.74, 1.78, 1.75, 1.77, 1.74, 1.73, 1.77, 1.75, 1.77, 1.77, 1.77, 1.75, 1.81, 1.81, 1.77, 1.74, 1.79, 1.73, 1.76, 1.78, 1.77, 1.82, 1.79, 1.77, 1.78, 1.77, 1.77, 1.74, 1.78, 1.78, 1.78, 1.79, 1.8, 1.76, 1.75, 1.82, 1.79, 1.76, 1.78, 1.79, 1.77, 1.75, 1.74, 1.78, 1.78, 1.78, 1.78, 1.78, 1.76, 1.82, 1.79, 1.81, 1.81, 1.78}, {1.6, 1.63, 1.63, 1.61, 1.68, 1.66, 1.66, 1.66, 1.64, 1.63, 1.6, 1.6, 1.62, 1.66, 1.64, 1.65, 1.63, 1.65, 1.6, 1.64, 1.63, 1.62, 1.64, 1.62, 1.62, 1.6, 1.59, 1.59, 1.63, 1.62, 1.61, 1.6, 1.63, 1.65, 1.59, 1.61, 1.65, 1.64, 1.6, 1.63, 1.61, 1.59, 1.63, 1.6, 1.6, 1.6, 1.6, 1.59, 1.6, 1.59, 1.58, 1.61, 1.62, 1.61, 1.59, 1.58, 1.61, 1.59, 1.59}, {1.55, 1.53, 1.53, 1.5, 1.53, 1.54, 1.53, 1.57, 1.55, 1.54, 1.55, 1.52, 1.51, 1.55, 1.57, 1.57, 1.56, 1.55, 1.55, 1.55, 1.53, 1.55, 1.54, 1.55, 1.53, 1.55, 1.53, 1.53, 1.52, 1.52, 1.57, 1.55, 1.56, 1.56, 1.51, 1.55, 1.57, 1.57, 1.56, 1.55, 1.57, 1.57, 1.55, 1.57, 1.59, 1.59, 1.55, 1.55, 1.56, 1.56, 1.58, 1.56, 1.59, 1.55, 1.55, 1.57, 1.56, 1.54, 1.54}, {1.41, 1.38, 1.4, 1.41, 1.4, 1.37, 1.39, 1.4, 1.41, 1.4, 1.4, 1.38, 1.39, 1.44, 1.44, 1.4, 1.41, 1.39, 1.39, 1.4, 1.39, 1.44, 1.4, 1.43, 1.41, 1.43, 1.47, 1.43, 1.38, 1.44, 1.4, 1.39, 1.39, 1.41, 1.41, 1.4, 1.37, 1.44, 1.43, 1.44, 1.39, 1.43, 1.47, 1.42, 1.44, 1.48, 1.47, 1.43, 1.43, 1.42, 1.44, 1.43, 1.44, 1.44, 1.49, 1.46, 1.44, 1.43, 1.44}};
double targets[] = {0, 20, 40, 60, 80, 90};

// initialize NN paramaters
void initialize()
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        weights[i] = 3.0 * 2 - 1; // initialize random weights
    }
    bias = 3.0 * 2 - 1; // initialize random bias
}

// neural network forward propagation
double predict(double inputs[])
{
    double output = 0;
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        output += weights[i] * inputs[i];
    }
    output += bias;
    return activation(output);
}

// Train a neural network
void train(double inputs[], double target)
{
    double prediction = predict(inputs);
    double error = target - prediction;
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        weights[i] += LEARNING_RATE * error * inputs[i];
    }
    bias += LEARNING_RATE * error;
}

void test_print(void)
{
    printf("test works\n");
}

void training_process(void)
{
    for (int epoch = 0; epoch < EPOCHS; epoch++)
    {
        for (int i = 0; i < sizeof(training_data) / sizeof(training_data[0]); i++)
        {
            train(training_data[i], targets[i]);
        }
    }
}

void prediction_process(void)
{
    for (int i = 0; i < sizeof(training_data) / sizeof(training_data[0]); i++)
    {
        double prediction = predict(training_data[i]);
        printf("Input: [%lf, %lf], Target: %lf, Prediction: %lf\n",
               training_data[i][0], training_data[i][1], targets[i], prediction);
        printf("Weights: %f\n", weights[i]);
    }
}