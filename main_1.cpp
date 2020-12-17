#include "main_1.hpp"

#include <string>
#include <iostream>
#include <typeinfo>
#include <math.h>


int main(int args, char** argv)
{
    

    std::string data_folder = "./sample_data/ieee14/scenario_1/";
    std::string con_name = "case.con";
    std::string raw_name = "case.raw";
    std::string sup_name = "case.json";

    Data new_data;
    new_data.read(data_folder + raw_name,\
                  data_folder + sup_name, \
                  data_folder + con_name);

    // case identification data from raw
    s_tilde = new_data.raw.CaseIdentificationData.sbase;
    double s_tilde_inverse = 1.0 / s_tilde;
    
    // bus data from raw
    int Is = new_data.raw.buses.size();
    construct_bus(new_data);
   
    // load data from raw
    construct_load(new_data, s_tilde_inverse);
    
    // fixed shunt data from raw
    construct_fixed_shunt(new_data, Is, s_tilde_inverse);
   
    // generator data from raw
    int Gs = new_data.raw.generators.size();
    construct_generator(new_data, Gs, s_tilde_inverse);
    
    // line (or non-transformer branch) data from raw
    construct_nontransformerbranch(new_data, s_tilde_inverse);

    // transformer data from raw
    construct_transformer(new_data, s_tilde_inverse);

    // switch shunt data from raw
    construct_switched_shunt(new_data, s_tilde_inverse);
    
    // construct con 
    construct_con(new_data);

    // nothing needs to be done for the case.sup file 

}


void construct_bus(Data& new_data)
{
     // bus data from raw

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
}

void construct_load(Data& new_data, double s_tilde_inverse)
{
    // loads data from raw
    std::unordered_map<int, Load>::iterator load_it;
    for (load_it=new_data.raw.loads.begin(); load_it!=new_data.raw.loads.end(); load_it++)
    {
        // // hash key of tuple(int, string)
        key_is tmp_j;
        tmp_j = std::make_tuple(load_it->second.i, load_it->second.id);
        J.push_back(tmp_j);
        i_j.insert(std::make_pair(tmp_j, load_it->second.i));
        id.insert(std::make_pair(tmp_j, load_it->second.id));
        p_l.insert(std::make_pair(tmp_j, load_it->second.pl * s_tilde_inverse));
        q_l.insert(std::make_pair(tmp_j, load_it->second.ql * s_tilde_inverse));

        if (load_it->second.status == 1)
        {
            J_k_0.push_back(tmp_j);
        }
    }
    // J_i = {j \in J: i_j = i}, \any i \in I
    findIters(i_j, J_i);

    
    
    /**
    std::unordered_map<int, key_is>::iterator it2;

    for(it2=J_i.begin();it2!=J_i.end(); it2++)
    {
        std::cout<<it2->first<<std::endl;
    }
    **/

}

void construct_fixed_shunt(Data& new_data, int Is, double s_tilde_inverse)
{
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

}

void construct_generator(Data& new_data, int Gs, double s_tilde_inverse)
{
    std::unordered_map<int, Generator>::iterator gen_it;
    for(gen_it=new_data.raw.generators.begin(); gen_it!=new_data.raw.generators.end(); gen_it++)
    {
        // hash key of tuple(int, string)
        key_is tmp_g;
        tmp_g = std::make_tuple(gen_it->second.i, gen_it->second.id);
        G.push_back(tmp_g);
        i_g.insert(std::make_pair(tmp_g, gen_it->second.i));
        id_g.insert(std::make_pair(tmp_g, gen_it->second.id));
        p_g.insert(std::make_pair(tmp_g, gen_it->second.pg * s_tilde_inverse));
        q_g.insert(std::make_pair(tmp_g, gen_it->second.qg * s_tilde_inverse));
        q_g_over.insert(std::make_pair(tmp_g, gen_it->second.qt * s_tilde_inverse));
        q_g_under.insert(std::make_pair(tmp_g, gen_it->second.qb * s_tilde_inverse));
        p_g_over.insert(std::make_pair(tmp_g, gen_it->second.pt * s_tilde_inverse));
        p_g_under.insert(std::make_pair(tmp_g, gen_it->second.pb * s_tilde_inverse));
        x_g_on_0.insert(std::make_pair(tmp_g, gen_it->second.stat));
        
    }
    
    // G_k0 = G
    // G_i  = {g \in G: i_g = i} \any i in I
    // copy by value
    G_k0 = G;
    findIters(i_g, G_i);
    UMAP_TUPLE_is_INT::iterator it2;

    for(it2=G_i.begin();it2!=G_i.end(); it2++)
    {
        std::cout<<it2->second<<std::endl;
    }
    

}

void construct_nontransformerbranch(Data& new_data, double s_tilde_inverse )
{
    std::unordered_map<key_iis, NontransformerBranch, boost::hash<key_iis>>::iterator non_it;

    for(non_it= new_data.raw.nontransformerbranches.begin(); non_it!= new_data.raw.nontransformerbranches.end(); non_it++)
    {
        // hash key of tuple(int, int, string)
        key_iis tmp_n;
        double tmp_denom = std::pow(non_it->second.r, 2) + std::pow(non_it->second.x, 2);
        tmp_n = non_it->first;
        E.push_back(tmp_n);
        i_e_o.insert(std::make_pair(tmp_n, non_it->second.i));
        i_e_d.insert(std::make_pair(tmp_n, non_it->second.j));
        id_E.insert(std::make_pair(tmp_n, non_it->second.ckt));
        g_e.insert(std::make_pair(tmp_n, non_it->second.r/tmp_denom));
        b_e.insert(std::make_pair(tmp_n, - non_it->second.x/tmp_denom));
        b_e_ch.insert(std::make_pair(tmp_n, non_it->second.b));
        r_e_over.insert(std::make_pair(tmp_n, non_it->second.ratea * s_tilde_inverse));
        r_e_ct_over.insert(std::make_pair(tmp_n, non_it->second.ratec * s_tilde_inverse));
        x_e_sw_0.insert(std::make_pair(tmp_n, non_it->second.st));
    }



}

void construct_transformer(Data& new_data, double s_tilde_inverse)
{
    std::unordered_map<key_iis, Transformer, boost::hash<key_iis>>::iterator tran_it;
    std::unordered_map<int, TransformerImpedanceCorrectionTable>::iterator tcit_it;

    for(tran_it=new_data.raw.transformers.begin(); tran_it!=new_data.raw.transformers.end(); tran_it++)
    {
        // hash key of tuple(int, int, string)
        double tmp_denom = pow(tran_it->second.r12, 2) + pow(tran_it->second.x12, 2);
        key_iis tmp_f;
        tmp_f = tran_it->first;
        F.push_back(tmp_f);
        i_f_o.insert(std:: make_pair(tmp_f, tran_it->second.i));
        i_f_d.insert(std::make_pair(tmp_f, tran_it->second.j));
        id_F.insert(std::make_pair(tmp_f, tran_it->second.ckt));
        g_f_m.insert(std::make_pair(tmp_f, tran_it->second.mag1));
        b_f_m.insert(std::make_pair(tmp_f, tran_it->second.mag2));
        g_f_0.insert(std::make_pair(tmp_f, tran_it->second.r12 / tmp_denom));
        b_f_0.insert(std::make_pair(tmp_f, -tran_it->second.x12 / tmp_denom));
        tau_f_0.insert(std::make_pair(tmp_f, tran_it->second.windv1 / tran_it->second.windv2));
        theta_f_0.insert(std::make_pair(tmp_f, tran_it->second.ang1 * PI / 180.0));
        x_f_st_over.insert(std::make_pair(tmp_f, (tran_it->second.ntp1 - 1.0)/2.0));
        
        if (tran_it->second.cod1 == 1)
        {
            tau_f_over.insert(std::make_pair(tmp_f, tran_it->second.rma1));
            tau_f_under.insert(std::make_pair(tmp_f, tran_it->second.rma1));
            F_tau.push_back(tmp_f);
            theta_f_over.insert(std::make_pair(tmp_f, tran_it->second.rma1 * PI / 180.0));
            
        }
        else 
        {
            tau_f_over.insert(std::make_pair(tmp_f, tau_f_0[tmp_f]));
            tau_f_under.insert(std::make_pair(tmp_f, tau_f_0[tmp_f]));
        }
        
        double tmp_tau_f = (tau_f_over[tmp_f] - tau_f_under[tmp_f]) / 2.0;
        tau_f_st.insert(std::make_pair(tmp_f, tmp_tau_f / x_f_st_over[tmp_f]));
        tau_f_any.insert(std::make_pair(tmp_f, tmp_tau_f));

        if(tran_it->second.cod1 == 3)
        {
            theta_f_over.insert(std::make_pair(tmp_f, tran_it->second.rma1 * PI / 180));
            theta_f_under.insert(std::make_pair(tmp_f, tran_it->second.rma1 * PI / 180));
            F_theta.push_back(tmp_f);
            
        }
        else 
        {
            theta_f_over.insert(std::make_pair(tmp_f, theta_f_0[tmp_f]));
            theta_f_under.insert(std::make_pair(tmp_f, theta_f_0[tmp_f]));
        }
    
        int tmp_i; int tmp_j; std::string tmp_ckt;
        std::tie(tmp_i, tmp_j, tmp_ckt) = tmp_f;
        
        if (tran_it->second.tab1 != 0)
        {
            
            F_gamma.push_back(tmp_f);
            
            for(tcit_it=new_data.raw.TFICTs.begin(); tcit_it!=new_data.raw.TFICTs.end();tcit_it++)
            {
                if(tcit_it->second.i == tran_it->second.tab1)
                {
                        for(int idx=0; idx<tcit_it->second.f.size(); idx++)
                        {
                            key_iisi tmp_fm = std::make_tuple(tmp_i, tmp_j, tmp_ckt, idx+1);
                            gamma_f_m.insert(std::make_pair(tmp_fm, tcit_it->second.f.at(idx)));
                    
                        } 
                    
                        if(tran_it->second.cod1 == 1)
                        {
                            for(int idx=0; idx<tcit_it->second.t.size(); idx++)
                            {
                                key_iisi tmp_fm = std::make_tuple(tmp_i, tmp_j, tmp_ckt, idx+1);
                                tau_f_m.insert(std::make_pair(tmp_fm, tcit_it->second.t.at(idx)));
                        

                            } 

                        }
                        else if(tran_it->second.cod1 == 3)
                        {
                            for(int idx=0; idx<tcit_it->second.t.size(); idx++)
                            {
                                key_iisi tmp_fm = std::make_tuple(tmp_i, tmp_j, tmp_ckt, idx+1);
                                theta_f_m.insert(std::make_pair(tmp_fm, tcit_it->second.t.at(idx) * PI / 180.0));
                            }

                        }
                }
            }
        }

        double tmp_theta_f = (theta_f_over[tmp_f] - theta_f_under[tmp_f]) / 2.0;
        theta_f_st.insert(std::make_pair(tmp_f, tmp_theta_f/x_f_st_over[tmp_f]));
        theta_f_any.insert(std::make_pair(tmp_f, tmp_theta_f));
        s_f_over.insert(std::make_pair(tmp_f, tran_it->second.rata1 * s_tilde_inverse));
        s_f_ct_over.insert(std::make_pair(tmp_f, tran_it->second.ratc1 * s_tilde_inverse));
        x_f_sw_0.insert(std::make_pair(tmp_f, tran_it->second.stat));


        

    }
}

void construct_switched_shunt(Data& new_data, double s_tilde_inverse)
{
    std::unordered_map<int, SwitchedShunt>::iterator ss_it;
    for(ss_it=new_data.raw.switchedshunts.begin(); ss_it!=new_data.raw.switchedshunts.end(); ss_it++)
    {
        H.push_back(ss_it->second.i);
        i_h.insert(std::make_pair(ss_it->second.i, ss_it->second.i));
        b_h_cs0.insert(std::make_pair(ss_it->second.i, ss_it->second.binit));
        NBL = ss_it->second.n.size();
        // so this for loop is A_h
        for(int idx=1; idx<=NBL; idx++)
        {
            key_ii tmp_ha;
            tmp_ha = std::make_tuple(ss_it->second.i, idx);
            x_ha_st_over.insert(std::make_pair(tmp_ha, ss_it->second.n.at(idx-1)));
            b_ha_st.insert(std::make_pair(tmp_ha, ss_it->second.b.at(idx-1) * s_tilde_inverse));
            
        }

        if (ss_it->second.stat == 1)
        {
            H_k0.push_back(ss_it->second.i);
        }
        
    }

}

void construct_con(Data& new_data)
{
    for(int idx=0; idx<new_data.con.contingencies.size(); idx++)
    {
        if (!new_data.con.contingencies.at(idx).branch_out_events.empty())
        {
            //std::cout<<new_data.con.contingencies.at(idx).branch_out_events[0].i<<std::endl;

        }
    }
    

}


