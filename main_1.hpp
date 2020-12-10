#ifndef __DATA_MAIN_HPP__
#define __DATA_MAIN_HPP__


#include <vector>
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <string>
#include <boost/functional/hash.hpp>
#include "data.hpp"

// some constants here
const double PI  = 3.141592653589793238463;

// some useful types

// key: tuple(int, string)
typedef std::tuple<int, std::string> key_is;
// key: tuple(int, int, string) 
typedef std::tuple<int, int, std::string> key_iis;
// unordered_map using tuple(int, string) as hash key
typedef std::unordered_map<key_is, int, boost::hash<key_is> > UMAP_TUPLE_is_INT;
typedef std::unordered_map<key_is, double, boost::hash<key_is> > UMAP_TUPLE_is_DOUBLE;
typedef std::unordered_map<key_is, std::string, boost::hash<key_is> > UMAP_TUPLE_is_STRING;
// unordered map using tuple(int, int, string) as hash key
typedef std::unordered_map<key_iis, int, boost::hash<key_iis> > UMAP_TUPLE_iis_INT;
typedef std::unordered_map<key_iis, double, boost::hash<key_iis> > UMAP_TUPLE_iis_DOUBLE;
typedef std::unordered_map<key_iis, std::string, boost::hash<key_iis> > UMAP_TUPLE_iis_STRING;

// define the objective funcitons, assume types subject to changes

std::string k_0 = "BASECASE";
std::string label_k_0 = "BASECASE";

std::vector<std::string> K;
std::vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8};

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
UMAP_TUPLE_is_DOUBLE p_g;
UMAP_TUPLE_is_DOUBLE q_g;
UMAP_TUPLE_is_DOUBLE q_g_over;
UMAP_TUPLE_is_DOUBLE q_g_under;
UMAP_TUPLE_is_DOUBLE p_g_over;
UMAP_TUPLE_is_DOUBLE p_g_under;
UMAP_TUPLE_is_DOUBLE x_g_on_0;

// arrays holding line (non-transformer branch data)
std::vector<key_iis> E;
UMAP_TUPLE_iis_INT i_e_o;
UMAP_TUPLE_iis_INT i_e_d;
UMAP_TUPLE_iis_STRING id_E;
UMAP_TUPLE_iis_DOUBLE g_e;
UMAP_TUPLE_iis_DOUBLE b_e;
UMAP_TUPLE_iis_DOUBLE b_e_ch;
UMAP_TUPLE_iis_DOUBLE r_e_over;
UMAP_TUPLE_iis_DOUBLE r_e_ct_over;
UMAP_TUPLE_iis_DOUBLE x_e_sw_0;

// functions to construct parameters using input from case.raw
void construct_bus(Data& local_data);
void construct_load(Data& local_data, double s_tilde_inverse);
void construct_fixed_shunt(Data& local_data, int Is, double s_tilde_inverse);
void construct_generator(Data& local_data, int Gs, double s_tilde_inverse);
void construct_nontransformerbranch(Data& local_data, double s_tilde_inverse);
void construct_transformer(Data& local_data, double s_tilde_inverse);



















#endif