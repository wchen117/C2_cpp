//
// Created by wchen on 3/22/21.
//

#ifndef GOC_CPP_UTILITY_HPP
#define GOC_CPP_UTILITY_HPP

template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element) {
    std::pair<bool, int> result;
    // Find given element in vector
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end()) {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    } else {
        result.first = false;
        result.second = -1;
    }
    return result;
}

#endif //GOC_CPP_UTILITY_HPP
