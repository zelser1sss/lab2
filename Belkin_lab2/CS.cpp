#include "CS.h"

CS::CS(const std::string& name, int k_cex, int k_cex_in_work, const std::string& type)
    : name(name), k_cex(k_cex), k_cex_in_work(k_cex_in_work), type(type) {
};

float CS::getUnusedPercent() const {
    if (k_cex == 0) return 0.0f;
    return (static_cast<float>(k_cex - k_cex_in_work) / k_cex) * 100;
};

bool CS::startWorkshops(int count) {
    if (k_cex_in_work + count <= k_cex) {
        k_cex_in_work += count;
        return true;
    };
    return false;
};

bool CS::stopWorkshops(int count) {
    if (k_cex_in_work - count >= 0) {
        k_cex_in_work -= count;
        return true;
    };
    return false;
};