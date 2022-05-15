#ifndef TOPOLOGY_API_DEVICE_H
#define TOPOLOGY_API_DEVICE_H

class device{
private:
    double defaultValue;
    double max;
    double min;
public:
    device();
    device(float defaultV, float min, float max);

    // Setters
    void setDefault(double defaultValue);
    void setMin(double min);
    void setMax(double max);

    // Getters
    double getDefault();
    double getMin();
    double getMax();
};

#endif //TOPOLOGY_API_DEVICE_H
