void pushTemp(double *arr, double newTemp) {
    arr[0] = arr[1];
    arr[1] = arr[2];
    arr[2] = newTemp;
}

void swap(double &a, double &b) {
    double c = a;
    a = b;
    b = c;
}

void sortArr(double *arr) {
    if(arr[0] > arr[1]) swap(arr[0], arr[1]);
    if(arr[1] > arr[2]) swap(arr[1], arr[2]);
    if(arr[0] > arr[1]) swap(arr[0], arr[1]);
}

void calculateMedian(double *rawBuff, double *medianBuff) {
    sortArr(rawBuff);
    pushTemp(medianBuff, rawBuff[1]);
}

double getWeighterAverage(double *medianBuff) {
    double weight0 = 50, weight1 = 25, weight2 = 10;
    return (medianBuff[0] * weight0 + medianBuff[1] * weight1 + medianBuff[2] * weight2) / (weight1 + weight1 + weight2);
}