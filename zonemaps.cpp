#include "zonemaps.h"

template<typename T>
zonemap<T>::zonemap(std::vector<T> _elements, size_t _num_elements_per_zone)
{
    elements = _elements;
    num_elements_per_zone = _num_elements_per_zone;
    num_zones = (elements.size()/num_elements_per_zone) + 1;
}

template<typename T>
void build()
{
    sort_elements();
    int j = 0;
    int end = start = 0;
    T cmax = elements[0];
    T cmin = elements[0];
    for(int i = 0; i < elements.size(); i++){
        if(cmax < elements[i]){
            cmax = elements[i];
        }
        if(cmin > elements[i]){
            cmin = elements[i];
        }
        if(i > 0 && i % num_elements_per_zone == 0){
            end = i;
            zone z;
            z.elements = {elements.begin() + start, elements.begin() + start + end}; // replace end
            z.max = cmax;
            z.min = cmin;
            z.size = end - start;
            zones.push_back(z);
            start = end + 1;
            j++;
            cmin = cmax = elements[start];
        } 
    }
}

template<typename T>
void sort_elements()
{
    for (int step = 0; step < elements.size(); step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (elements[i] < elements[min_idx])
                min_idx = i;
            }

        T temp = *element[min_idx];
        *element[min_idx] = *element[step];
        *element[step] = temp;
    }
}

template<typename T>
size_t zonemap<T>::query(T key)
{   
    std::vector<zone<T> probeZone;
    for(int i = 0; i < zones.size(); i++){
        if(zones[i].min < key && zones[i].max > key){
            probeZone.push_back(zones[i]);
        }
    }
    int ctr = 0;
    for(int i = 0; i < probeZone.size(); i++){
        for(int j = 0; j < probeZone[i].elements.size(); j++){
            if(key == probeZone[i].elements[j]){
                ctr++;
            }
        }
    }
    return ctr;
}

template<typename T>
std::vector<T> query(T low, T high){
    std::vector<T> ret;
    for(int i = 0; i < zones.size(); i++){
        if((zones[i].min < low && zones[i].max > low) || (zones[i].min < high && zones[i].max > high)){
            int start = (low > zones[i].min) ? -1 : 0;
            int end  = (high < zones[i].max) ? -1 : zones[i].elements.size();
            if(start == -1){
                for(int j = 0; j < zones[i].elements.size(); i++){
                    if(low == zones[i].elements[j]){
                        start = j;
                    }
                }
            }
            if(end == -1){
                for(int j = 0; j < zones[i].elements.size(); i++){
                    if(high == zones[i].elements[j]){
                        end = j;
                    }
                }
            }
            for(int j = start, j < end; j++){
                ret.push_back(zones[i].elements[j]);
            }
        }
    }
    return ret;
}