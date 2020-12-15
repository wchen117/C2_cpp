#ifndef __DATA_MAIN_HPP__
#define __DATA_MAIN_HPP__


#include <vector>
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <string>
#include "typedefinition.hpp"
#include "data.hpp"


// define the objective funcitons, assume types subject to changes

std::string k_0 = "BASECASE";
std::string label_k_0 = "BASECASE";

std::vector<std::string> K;
std::vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8};

std::vector<double> H;
std::vector<double> H_k_0;


std::vector<int> M = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

double s_tilde;

// vectors holding bus data 
std::vector<int> I;
std::vector<double> v_0;
std::vector<double> theta_0;
std::vector<double> vover;
std::vector<double> vunder;
std::vector<double> v_ct_over;
std::vector<double> v_ct_under;

// vectors and maps holding load data
std::vector< std::tuple<int,std::string> > J;
std::vector< std::tuple<int,std::string> > J_k_0;
UMAP_TUPLE_is_INT iii;
UMAP_TUPLE_is_STRING id;
UMAP_TUPLE_is_DOUBLE p_l;
UMAP_TUPLE_is_DOUBLE q_l;

// arrays holding fixed shunt data 
std::vector<double> g_fs;
std::vector<double> b_fs;

// vectors and maps holding generator data
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

// vectors and maps holding line (non-transformer branch data)
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

// vectors and maps holding transformer data
std::vector<key_iis> F;
std::vector<key_iis> F_tau;
std::vector<key_iis> F_theta;
std::vector<key_iis> F_gamma;
UMAP_TUPLE_iis_INT i_f_o;
UMAP_TUPLE_iis_INT i_f_d;
UMAP_TUPLE_iis_STRING id_F;
UMAP_TUPLE_iis_DOUBLE g_f_m;
UMAP_TUPLE_iis_DOUBLE b_f_m;
UMAP_TUPLE_iis_DOUBLE g_f_0;
UMAP_TUPLE_iis_DOUBLE b_f_0;
UMAP_TUPLE_iis_DOUBLE tau_f_0;
UMAP_TUPLE_iis_DOUBLE theta_f_0;
UMAP_TUPLE_iis_DOUBLE x_f_st_over;
UMAP_TUPLE_iis_DOUBLE tau_f_over;
UMAP_TUPLE_iis_DOUBLE tau_f_under;
UMAP_TUPLE_iis_DOUBLE tau_f_st;
UMAP_TUPLE_iis_DOUBLE tau_f_any;
UMAP_TUPLE_iis_DOUBLE theta_f_over;
UMAP_TUPLE_iis_DOUBLE theta_f_under;
UMAP_TUPLE_iis_DOUBLE theta_f_st;
UMAP_TUPLE_iis_DOUBLE theta_f_any;
UMAP_TUPLE_iis_DOUBLE s_f_over;
UMAP_TUPLE_iis_DOUBLE s_f_ct_over;
UMAP_TUPLE_iis_DOUBLE x_f_sw_0;

// vectors and maps holding Transformer Impedance Correction Table data
double NUMM;
UMAP_TUPLE_iisi_DOUBLE gamma_f_m;
UMAP_TUPLE_iisi_DOUBLE tau_f_m;
UMAP_TUPLE_iisi_DOUBLE theta_f_m;

// functions to construct parameters using input from case.raw
void construct_bus(Data& local_data);
void construct_load(Data& local_data, double s_tilde_inverse);
void construct_fixed_shunt(Data& local_data, int Is, double s_tilde_inverse);
void construct_generator(Data& local_data, int Gs, double s_tilde_inverse);
void construct_nontransformerbranch(Data& local_data, double s_tilde_inverse);
void construct_transformer(Data& local_data, double s_tilde_inverse);
void construct_switchedshunt(Data& local_data, double s_tilde_inverse);




















#endif