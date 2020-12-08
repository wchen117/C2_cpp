#ifndef __DATA_MAIN_HPP__
#define __DATA_MAIN_HPP__

#include <vector>
#include <unordered_map>
#include <iostream>
#include <math.h>

// define the objective funcitons, assume type double now

std::vector<double> I;
std::vector<double> A;
std::vector<double> G;
std::vector<double> Gr;
std::vector<double> E;
std::vector<double> Er;
std::vector<double> F;
std::vector<double> Fr;
std::vector<double> bl;
std::vector<double> K;
std::vector<double> H;
std::vector<double> N;

std::vector<double> lambda_p;
std::vector<double> lambda_q;
std::vector<double> lambda_s;

std::unordered_map<int, double> p_l;
std::unordered_map<int, double> q_l;
std::unordered_map<int, double> g_fs;
std::unordered_map<int, double> b_fs;
// in python code it was i
std::unordered_map<int, double> iii;
std::unordered_map<int, double> ie_o;
std::unordered_map<int, double> ie_d;
std::unordered_map<int, double> if_o;
std::unordered_map<int, double> if_d;
// in python code it was g
std::unordered_map<int, double> ggg;
// in python code it was b
std::unordered_map<int, double> bbb;
std::unordered_map<int, double> b_ch;
std::unordered_map<int, double> rover;
std::unordered_map<int, double> rover_k;
std::unordered_map<int, double> g_m;
std::unordered_map<int, double> b_m;
std::unordered_map<int, double> tau;
std::unordered_map<int, double> theta;
std::unordered_map<int, double> sover;
std::unordered_map<int, double> sover_k;
std::unordered_map<int, double> b_cs0;
std::unordered_map<int, double> bover_cs;
std::unordered_map<int, double> bunder_cs;
std::unordered_map<int, double> Hr;
// in python code it was p
std::unordered_map<int, double> ppp;
std::unordered_map<int, double> ccc;
std::unordered_map<int, double> alpha;

std::unordered_map<int, double> Ek;
std::unordered_map<int, double> Fk;
std::unordered_map<int, double> Gk;


std::unordered_map<int, double> ak;
std::unordered_map<int, double> bk;
std::unordered_map<int, double> Gk_p;

double stilde;
double None;










#endif