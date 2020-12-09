#include "main_1.hpp"
#include "data.hpp"
#include <string>
#include <iostream>
#include <typeinfo>
#include <math.h>


int main(int args, char** argv)
{
    const double PI  = 3.141592653589793238463;

    std::string data_folder = "./sample_data/ieee14/scenario_1/";
    std::string con_name = "case.con";
    std::string raw_name = "case.raw";
    std::string sup_name = "case.json";

    Data new_data;
    new_data.read(data_folder + raw_name,\
                  data_folder + sup_name, \
                  data_folder + con_name);

    //std::string write_raw_name = "test_write.raw";
    //std::string write_con_name = "test_write.con";
    //std::string write_sup_name = "test_write.sup";
    
    //new_data.write(write_raw_name, \
    //               write_con_name, \
    //               write_sup_name);

    // case identification data from raw
    s_tilde = new_data.raw.CaseIdentificationData.sbase;
    double s_tilde_inverse = 1.0 / s_tilde;
    

    // bus data from raw
    int Is = new_data.raw.buses.size();
    

    std::unordered_map<int, Bus>::iterator bus_it;
    
    for (bus_it=new_data.raw.buses.begin(); bus_it!=new_data.raw.buses.end(); bus_it++)
    {
        I.push_back(bus_it->second.i);
        v_0.push_back(bus_it->second.vm);
        theta_0.push_back(bus_it->second.va * PI / 180.0);
        vover.push_back(bus_it->second.nvhi);
        vunder.push_back(bus_it->second.nvlo);
        v_ct_over.push_back(bus_it->second.evhi);
        v_ct_over.push_back(bus_it->second.evlo);
    }

    
    // loads data from raw
    std::unordered_map<int, Load>::iterator load_it;
    for (load_it=new_data.raw.loads.begin(); load_it!=new_data.raw.loads.end(); load_it++)
    {
        std::tuple<int, std::string> tmp_j;
        tmp_j = std::make_tuple(load_it->second.i, load_it->second.id);
        J.push_back(tmp_j);
        iii.insert(std::make_pair(tmp_j, load_it->second.i));
        id.insert(std::make_pair(tmp_j, load_it->second.id));
        p_l.insert(std::make_pair(tmp_j, load_it->second.pl * s_tilde_inverse));
        q_l.insert(std::make_pair(tmp_j, load_it->second.ql * s_tilde_inverse));

        if (load_it->second.status == 1)
        {
            J_k_0.push_back(tmp_j);
        }
    }
    // missing: Having read and processed the load section, set:

    // initilize g_fs and b_fs to 0

    for (int idx=0; idx < Is; idx++)
    {
        g_fs.push_back(0.0);
        b_fs.push_back(0.0);
    }
    
    // fixed shunt data from raw
    std::unordered_map<int, FixedShunt>::iterator shunt_it;
    for(shunt_it=new_data.raw.shunts.begin(); shunt_it!=new_data.raw.shunts.end(); shunt_it++)
    {
        if (shunt_it->second.status == 1)
        {
            g_fs[shunt_it->second.i] = g_fs[shunt_it->second.i] + shunt_it->second.gl * s_tilde_inverse;
            b_fs[shunt_it->second.i] = b_fs[shunt_it->second.i] + shunt_it->second.bl * s_tilde_inverse;
           
        }

    }

    // generator data from raw
    int Gs = new_data.raw.generators.size();
    std::unordered_map<int, Generator>::iterator gen_it;

    for(gen_it=new_data.raw.generators.begin(); gen_it!=new_data.raw.generators.end(); gen_it++)
    {
        std::tuple<int, std::string> tmp_g;
        tmp_g = std::make_tuple(gen_it->second.i, gen_it->second.id);
        G.push_back(tmp_g);
        i_g.insert(std::make_pair(tmp_g, gen_it->second.i));
        id_g.insert(std::make_pair(tmp_g, gen_it->second.id));
        
       
        
    }
    

    

    
    
}
