#include "Device.h"


device::device() {

}

device::device(float defaultV, float min, float max) {
    this->defaultValue = defaultV;
    this->min = min;
    this->max = max;
}

void device::setDefault(double defaultValue) {
    this->defaultValue = defaultValue;
}

void device::setMin(double min) {
    this->min = min;
}

void device::setMax(double max) {
    this->max = max;
}

double device::getDefault() {
    return this->defaultValue;
}

double device::getMin() {
    return this->min;
}

double device::getMax() {
    return this->max;
}
