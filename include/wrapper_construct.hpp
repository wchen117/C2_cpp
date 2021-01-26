#ifndef __WRAPPER_CONSTRUCT_HPP__
#define __WRAPPER_CONSTRUCT_HPP__
#include <vector>
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <string>
#include "typedefinition.hpp"
#include "data.hpp"

class Wrapper_Construct
{
    public:
    Data new_data;
    std::string con_name = "case.con";
    std::string raw_name = "case.raw";
    std::string sup_name = "case.json";
    
    Wrapper_Construct(std::string input_path="./sample_data/ieee14/scenario_1/");
    ~Wrapper_Construct();

    // model parameters
    std::string k_0 = "BASECASE";
    std::string label_k_0 = "BASECASE";
    std::vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> M = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    double s_tilde;
    double s_tilde_inverse;
    // sizes of the data
    // number of buses
    size_t Is;
    // number of generators
    size_t Gs;
    // number of lines (non-transformer branch)
    size_t Es;
    // number of transformers
    size_t Fs;
    // number of K (cases?)
    size_t Ks;
    // number of pcblocks and qcblocks Np and Nq
    size_t Np;
    size_t Nq;
    std::vector<size_t> N;
    // vectors holding bus data
    std::vector<int> I;
    std::vector<double> v_0;
    std::vector<double> theta_0;
    std::vector<double> vover;
    std::vector<double> vunder;
    std::vector<double> v_ct_over;
    std::vector<double> v_ct_under;
    // vectors and maps holding load data
    std::vector<key_is> J;
    std::vector<key_is> J_k0;
    std::vector<key_is> J_k;
    UMAP_TUPLE_is_INT J_i;
    UMAP_TUPLE_is_INT i_j;
    UMAP_TUPLE_is_STRING id;
    UMAP_TUPLE_is_DOUBLE p_l;
    UMAP_TUPLE_is_DOUBLE q_l;
    // arrays holding fixed shunt data
    std::vector<double> g_fs;
    std::vector<double> b_fs;
    // vectors and maps holding generator data
    std::vector<key_is> G;
    std::vector<key_is> G_k;
    std::vector<key_is> G_k0;
    UMAP_TUPLE_is_INT G_i;
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
    std::vector<key_iis> E_k;
    std::vector<key_iis> E_k0;
    UMAP_TUPLE_iis_INT E_i_o;
    UMAP_TUPLE_iis_INT E_i_d;
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
    std::vector<key_iis> F_k;
    std::vector<key_iis> F_k0;
    UMAP_TUPLE_iis_INT F_i_o;
    UMAP_TUPLE_iis_INT F_i_d;
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
    // vectors and maps holding switched shunt data
    std::vector<int> H;
    std::unordered_map<int, int> i_h;
    std::unordered_map<int, int> H_i;
    std::unordered_map<int, double> b_h_cs0;
    int NBL;
    std::unordered_map<int, int> A_h;
    UMAP_TUPLE_ii_DOUBLE x_ha_st_over;
    UMAP_TUPLE_ii_DOUBLE b_ha_st;
    std::vector<int> H_k0;
    std::vector<int> H_k;
    // vectors and maps holding con data
    std::vector<std::string> K;
    std::vector<std::string> label_k;

    // functions to construct parameters using input from case.raw
    void construct_bus();
    void construct_load();
    void construct_fixed_shunt();
    void construct_generator();
    void construct_nontransformerbranch();
    void construct_transformer();
    void construct_switched_shunt();
    void construct_con();

    // template to find J_i, G_i, etc
    template <typename T1>
    void findIters(T1 target, T1 &target_i)
    {
        typename T1::iterator it1;
        for (it1 = target.begin(); it1 != target.end(); it1++)
        {
            for (int idx = 0; idx < I.size(); idx++)
            {
                if (it1->second == I.at(idx))
                {
                    target_i.insert(std::make_pair(it1->first, I.at(idx)));
                }
            }
        }
    }
    // template to print a 2d vector
    template <class T>
    void printVector(std::vector<std::vector<T>> const &matrix)
    {
        for (std::vector<T> row : matrix)
        {
            for (T val : row)
            {
                std::cout << val << " ";
            }
            std::cout << '\n';
        }
    }
    // function to print tuple
    void printtuple(const std::tuple<int, int, std::string> &tmp_key);
    // vectors holding variables in bus objectives
    double z_ik;
    std::vector<double> x_vec;
    // number of constrains
    size_t num_g = 0;
    // number of variables, essentailly length of x_vec
    size_t num_x = 0;
    std::vector<size_t> Nj_size_list;
    // function related to ipopt implementation
    void construct_size_and_bounds();
    void onstruct_g_vector();
    void get_Nj_size();
    void get_num_constraints();
};
#endif