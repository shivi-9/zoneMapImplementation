#include "zonemaps.h"

/* Implementing the functions defined in the zonemaps.h header file in this file */

// Constructor of the zonemap class defined in the header file to initialize all the data members
template<typename T>
zonemap<T>::zonemap(std::vector<T> _elements, size_t _num_elements_per_zone)
{
    elements = _elements;
    num_elements_per_zone = _num_elements_per_zone;
    num_zones = (elements.size() + num_elements_per_zone - 1) / num_elements_per_zone;
    zones.resize(num_zones); // to ensure that there is enough space to store all the zones in the vector.
}

// This function builds the zonemap
template<typename T> 
void zonemap<T>::build()
{
    sort_elements(); // will sort the elements in elements vector
    int i = 0;
    int start = 0;
    int end = 0;
    while(i < num_zones){ // used to divide our elements vector into different zones of size num_elements_per_zone
        end = start + num_elements_per_zone - 1; // to calculate the exact range of elements to be added to the zone
        zones[i].elements = {elements.begin() + start, elements.begin() + end};
        zones[i].min = elements[start];
        zones[i].max = elements[end];
        zones[i].size = end - start;
        start = end + 1;
        i+=1;
    }
}

// This function sorts the elements of our data
template<typename T>
void zonemap<T>::sort_elements()
{
    std::sort(elements.begin(), elements.end());
}

// This function is used to count the number of times a given key appears in the data vector using our zonemaps
template<typename T>
size_t zonemap<T>::query(T key)
{   
    std::vector<zone<T> > probeZone;
    // Creating a probeZone list, which will contain all the zones that contains the key
    for(int i = 0; i < zones.size(); i++){
        if(zones[i].min < key && zones[i].max > key){
            probeZone.push_back(zones[i]);
        }
    }
    int ctr = 0; // To keep track of the number of times the key appears in the data
    // Looping through the probeZone vector and for each zone,
    // loop through its elements to check if the key matches any of the elements
    // If it does, the counter ctr is incremented
    for(int i = 0; i < probeZone.size(); i++){
        for(int j = 0; j < probeZone[i].elements.size(); j++){
            if(key == probeZone[i].elements[j]){
                ctr++;
            }
        }
    }
    // printf("%d : %d\n",key, ctr);
    return ctr;
}

// The function takes two arguments, lower and upper bounds of the range that the function will return elements from. 
// The function returns a vector that contains the elements using the zonemap that are within the specified range.
template<typename T>
std::vector<T> zonemap<T>::query(T low, T high){
    std::vector<T> ret;
    for(int i =0; i < zones.size(); i++){
        // Checking if the low or high lies in the current zonemap, if it does goes to the following for loop
        // else continues to increment the i
        if(high < zones[i].min || low > zones[i].max){
            continue;
        }
        // Looping through all the elements to see if it lies between low and high and adds it to ret vector if it does
        for(int j = 0; j < zones[i].elements.size(); j++){
            if(zones[i].elements[j] >= low && zones[i].elements[j] <= high){
                ret.push_back(zones[i].elements[j]);
            }
        }
    }
    // printf("%d, %d : %ld, %ld",low, high,ret.front(), ret.back());
    // printf("\n");
    return ret;
}