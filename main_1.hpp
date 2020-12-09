#ifndef __DATA_MAIN_HPP__
#define __DATA_MAIN_HPP__


#include <vector>
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <string>
#include <boost/functional/hash.hpp>

// some useful types

typedef std::tuple<int, std::string> key_is;
typedef std::unordered_map<key_is, int, boost::hash<key_is> > UMAP_TUPLE_is_INT;
typedef std::unordered_map<key_is, double, boost::hash<key_is> > UMAP_TUPLE_is_DOUBLE;
typedef std::unordered_map<key_is, std::string, boost::hash<key_is> > UMAP_TUPLE_is_STRING;

// define the objective funcitons, assume types subject to changes

std::string k_0 = "BASECASE";
std::string label_k_0 = "BASECASE";

std::vector<std::string> K;
std::vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8};
std::vector<double> E;
std::vector<double> F_tau;
std::vector<double> F_theta;
std::vector<double> F_gamma;

std::vector<double> H;
std::vector<double> H_k_0;


std::vector<int> M = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

double s_tilde;

// arrays holding bus data 
std::vector<int> I;
std::vector<double> v_0;
std::vector<double> theta_0;
std::vector<double> vover;
std::vector<double> vunder;
std::vector<double> v_ct_over;
std::vector<double> v_ct_under;

// arrays holding load data
std::vector< std::tuple<int,std::string> > J;
std::vector< std::tuple<int,std::string> > J_k_0;
UMAP_TUPLE_is_INT iii;
UMAP_TUPLE_is_STRING id;
UMAP_TUPLE_is_DOUBLE p_l;
UMAP_TUPLE_is_DOUBLE q_l;

// arrays holding fixed shunt data 
std::vector<double> g_fs;
std::vector<double> b_fs;

// arrays holding generator data
std::vector<key_is> G;
UMAP_TUPLE_is_INT i_g;
UMAP_TUPLE_is_STRING id_g;
std::vector<double> p_g;
std::vector<double> q_g;
std::vector<double> q_t;
std::vector<double> p_t;
std::vector<double> p_b;
double x_g_on_0;





















#endif