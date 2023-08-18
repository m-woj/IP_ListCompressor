#pragma once


#include <vector>


template<class EntityT>
class Purifier {
public:
    static void removeDuplicatesAndSort(std::vector<EntityT>& vec) {
        sort( vec.begin(), vec.end() );
        vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
    }
};