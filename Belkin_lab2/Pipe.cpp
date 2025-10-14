#include "Pipe.h"

Pipe::Pipe(int id,  const std::string& name, float length, int diameter, bool repair)
    : id(id), name(name), length(length), diameter(diameter), repair(repair) {
};