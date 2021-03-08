#ifndef __TYPE_DEFINITION_HPP__
#define __TYPE_DEFINITION_HPP__

//this file includes useful type definitions and constants

// we use boost library to implement unordered_map with sets as hash keys
#include <boost/functional/hash.hpp>
#include <boost/multi_array.hpp>


// some constants here
const double PI  = 3.141592653589793238463;

// some useful types

// key: tuple(int, string)
typedef std::tuple<int, std::string> key_is;
// key: tuple(int, int, string) 
typedef std::tuple<int, int, std::string> key_iis;
// key: tuple(int, int)
typedef std::tuple<int, int> key_ii;
// key: tuple(int, int, string, int)
typedef std::tuple<int, int, std::string, int> key_iisi;

// unordered_map using tuple(int, int) as hash key
typedef std::unordered_map<key_ii, int, boost::hash<key_ii> > UMAP_TUPLE_ii_INT;
typedef std::unordered_map<key_ii, double, boost::hash<key_ii> > UMAP_TUPLE_ii_DOUBLE;
typedef std::unordered_map<key_ii, std::string, boost::hash<key_ii> > UMAP_TUPLE_ii_STRING;

// unordered_map using tuple(int, string) as hash key
typedef std::unordered_map<key_is, int, boost::hash<key_is> > UMAP_TUPLE_is_INT;
typedef std::unordered_map<key_is, double, boost::hash<key_is> > UMAP_TUPLE_is_DOUBLE;
typedef std::unordered_map<key_is, std::string, boost::hash<key_is> > UMAP_TUPLE_is_STRING;

// unordered map using tuple(int, int, string) as hash key
typedef std::unordered_map<key_iis, int, boost::hash<key_iis> > UMAP_TUPLE_iis_INT;
typedef std::unordered_map<key_iis, double, boost::hash<key_iis> > UMAP_TUPLE_iis_DOUBLE;
typedef std::unordered_map<key_iis, std::string, boost::hash<key_iis> > UMAP_TUPLE_iis_STRING;
// unordered map using tuple(int, int, string, int) as hash key
typedef std::unordered_map<key_iisi, int, boost::hash<key_iisi> > UMAP_TUPLE_iisi_INT;
typedef std::unordered_map<key_iisi, double, boost::hash<key_iisi> > UMAP_TUPLE_iisi_DOUBLE;
typedef std::unordered_map<key_iisi, std::string, boost::hash<key_iisi> > UMAP_TUPLE_iisi_STRING;


// two dimensional double vector
typedef std::vector< std::vector<double> > twoD_vector_double;
typedef std::vector< std::vector< std::vector<double> > > threeD_vector_double;

// related to Eigen


#endif