#include "wrapper_construct.hpp"
#include <iostream>
Wrapper_Construct::Wrapper_Construct(std::string input_path){
    new_data.read(input_path + raw_name,\
                  input_path + sup_name, \
                  input_path + con_name);

    s_tilde = new_data.raw.CaseIdentificationData.sbase; 
    s_tilde_inverse = 1.0 / s_tilde;

    // bus data from raw
    Is = new_data.raw.buses.size();
    construct_bus();
    
    // load data from raw
    construct_load();
    
    // fixed shunt data from raw
    construct_fixed_shunt();
    
    // generator data from raw
    Gs = new_data.raw.generators.size();
    construct_generator();
    
    Es = new_data.raw.nontransformerbranches.size();
    // line (or non-transformer branch) data from raw
    construct_nontransformerbranch();

    // transformer data from raw
    Fs = new_data.raw.transformers.size();
    construct_transformer();
    
    // switch shunt data from raw
    construct_switched_shunt();

    // construct con 
    construct_con();

    // if need sup data directly access new_data.sup
    Np = new_data.sup.sup_doc["pcblocks"].Size();
    Nq = new_data.sup.sup_doc["qcblocks"].Size();

}

Wrapper_Construct::~Wrapper_Construct(){}

void Wrapper_Construct::construct_bus()
{
     // bus data from raw

    std::unordered_map<int, Bus>::iterator bus_it;
    
    for (bus_it=new_data.raw.buses.begin(); bus_it!=new_data.raw.buses.end(); bus_it++)
    {
        I.push_back(bus_it->second.i);
        v_0.insert(std::make_pair(bus_it->second.i, bus_it->second.vm));
        theta_0.insert(std::make_pair(bus_it->second.i, bus_it->second.va * PI / 180.0));
        vover.insert(std::make_pair(bus_it->second.i, bus_it->second.nvhi));
        vunder.insert(std::make_pair(bus_it->second.i, bus_it->second.nvlo));
        v_ct_over.insert(std::make_pair(bus_it->second.i, bus_it->second.evhi));
        v_ct_under.insert(std::make_pair(bus_it->second.i, bus_it->second.evlo));
    }
}
void Wrapper_Construct::construct_load()
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
            J_k0.push_back(tmp_j);
        }
    }
    // J_i = {j \in J: i_j = i}, \any i \in I
    findIters(i_j, J_i);

}

void Wrapper_Construct::construct_fixed_shunt()
{
     // initilize g_fs and b_fs to 0
     /**
    for (int idx=0; idx < Is; idx++)
    {
        g_fs.push_back(0.0);
        b_fs.push_back(0.0);
    }
      **/
    
    // fixed shunt data from raw
    std::unordered_map<int, FixedShunt>::iterator shunt_it;
    for(shunt_it=new_data.raw.shunts.begin(); shunt_it!=new_data.raw.shunts.end(); shunt_it++)
    {
        g_fs.insert(std::make_pair(shunt_it->second.i, 0.0));
        b_fs.insert(std::make_pair(shunt_it->second.i, 0.0));
        if (shunt_it->second.status == 1)
        {
            g_fs[shunt_it->second.i] = g_fs[shunt_it->second.i] + shunt_it->second.gl * s_tilde_inverse;
            b_fs[shunt_it->second.i] = b_fs[shunt_it->second.i] + shunt_it->second.gl * s_tilde_inverse;
        }

    }

}

void Wrapper_Construct::construct_generator()
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
    
    /**
    UMAP_TUPLE_is_INT::iterator it2;

    for(it2=G_i.begin();it2!=G_i.end(); it2++)
    {
        std::cout<<it2->second<<std::endl;
    }
    **/
    
}
void Wrapper_Construct::construct_nontransformerbranch()
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

    // E_k0 = E
    // E_i_o = {e \in E: i_e_o = i} \any i \in I
    // E_i_d = {e \in E: i_e_d = i} \any i \in I
    E_k0 = E;
    findIters(i_e_o, E_i_o);
    findIters(i_e_d, E_i_d);

}

void Wrapper_Construct::construct_transformer()
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
    // F_k0 = F
    // F_i_o = {f \in F: i_f_o = i} \any i in I
    // F_i_d = {f \in F: i_f_d = i} \any i in I
    F_k0 = F;
    findIters(F_i_o, i_f_o);
    findIters(F_i_d, i_f_d);

}
void Wrapper_Construct::construct_switched_shunt()
{
    std::unordered_map<int, SwitchedShunt>::iterator ss_it;
    for(ss_it=new_data.raw.switchedshunts.begin(); ss_it!=new_data.raw.switchedshunts.end(); ss_it++)
    {
        // ss_it->second.i = i and h
        H.push_back(ss_it->second.i);
        i_h.insert(std::make_pair(ss_it->second.i, ss_it->second.i));
        b_h_cs0.insert(std::make_pair(ss_it->second.i, ss_it->second.binit * s_tilde_inverse));
        NBL = ss_it->second.n.size();
        // this loop through a \in A_h
        for(int idx=1; idx<=NBL; idx++)
        {

            key_ii tmp_ha;
            tmp_ha = std::make_tuple(ss_it->second.i, idx);
            A_h.insert(std::make_pair(tmp_ha, idx));
            x_ha_st_over.insert(std::make_pair(tmp_ha, ss_it->second.n.at(idx-1)));
            b_ha_st.insert(std::make_pair(tmp_ha, ss_it->second.b.at(idx-1) * s_tilde_inverse));

            
        }

        if (ss_it->second.stat == 1)
        {
            H_k0.push_back(ss_it->second.i);
        }
        
    }

    // H_i = {h \in H: i_h = i} \any i in I
    findIters(H_i, i_h);

}

void Wrapper_Construct::construct_con()
{
    // first copy vectors: Ek = E, Fk = F, Jk = Jk0 and Hk = Hk0
    // at this point E, F, J_k0 and H_k0 should be occupied

    assert(!E.empty());
    assert(!F.empty());
    assert(!J_k0.empty());
    assert(!H_k0.empty());

    E_k = E;
    F_k = F;
    G_k = G;
    J_k = J_k0;
    H_k = H_k0;
    

    for(size_t idx=0; idx<new_data.con.contingencies.size(); idx++)
    {
        K.push_back(new_data.con.contingencies.at(idx).label);
        label_k.push_back(new_data.con.contingencies.at(idx).label);
        //  these are the branch out event
        if (!new_data.con.contingencies.at(idx).branch_out_events.empty())
        {
            key_iis tmp_key;
            tmp_key = std::make_tuple(new_data.con.contingencies.at(idx).branch_out_events[0].i, \
                                      new_data.con.contingencies.at(idx).branch_out_events[0].j, \
                                      // the ckt number in case.con file is not surronded by \'\' marks
                                      "'" + new_data.con.contingencies.at(idx).branch_out_events[0].ckt + "'");

            for (size_t jdx=0; jdx<E.size(); jdx++)
            {
                if (tmp_key == E.at(jdx))
                {
                    E_k.erase(find(E_k.begin(), E_k.end(), tmp_key));
                }
            }

            for (size_t jdx=0; jdx<F.size(); jdx++)
            {
                if (tmp_key == F.at(jdx))
                {
                    F_k.erase(find(F_k.begin(), F_k.end(), tmp_key));
                }
            }

        }
        // these are the Generator Out-of-Service Event
        else if (!new_data.con.contingencies.at(idx).generator_out_events.empty())
        {
            key_is tmp_key;
            tmp_key = std::make_tuple(new_data.con.contingencies.at(idx).generator_out_events[0].i,\
                                      "'" + new_data.con.contingencies.at(idx).generator_out_events[0].id + "'");
            for (size_t kdx=0; kdx<G.size(); kdx++)
            {
                if(tmp_key == G.at(kdx))
                {
                    G_k.erase(find(G_k.begin(), G_k.end(), G.at(kdx)));
                }
            }
            
            
        }

        // having read and processed the contingency file, set
        // J_k = J_k0 \any k \in K \ {k0}
        // H_k = H_k0 \any k \in K \ {k0}
  
        assert(!J_k0.empty());
        assert(!H_k0.empty());
        J_k = J_k0;
        H_k = H_k0;




    }


}

void Wrapper_Construct::printtuple(const std::tuple<int, int, std::string>& tmp_key)
{
    int a, b;
    std::string c;
    std::tie(a, b,c) = tmp_key;
    std::cout<<a<<","<<b<<","<<c<<std::endl;
    //std::cout<<typeid(c).name()<<std::endl;
}

void Wrapper_Construct::construct_size_and_bounds()
{
    
    assert(x_vec.empty());
    assert(!K.empty());
    assert(!I.empty());
    assert(!new_data.sup.pcblocks.empty());

    size_t Np = new_data.sup.pcblocks.size();
    size_t Nq = new_data.sup.qcblocks.size();

    std::vector<size_t> Nj_size_list;
    get_Nj_size();
    get_num_constraints();
    std::cout<<Np<<std::endl;
    
    // variables are arranged in x_vect in the following order:
    // p_ikn+, p_ikn-, q_ikn+, q_ikn-, z_ik (scalar), 
    // p_jkn, z_jk (scalar)
    // s_enk+, z_ek (scalar)
    // s_fnk+, z_fk (scalar)
    // p_gnk, z_gk (scalar)

    // variable length: p_ikn+, p_ikn-: Np
    // q_ikn+, q_ikn-: Nq

    //x_vec.resize(2*Np+2*Nq+1+Nj_max+1+);

    
}

void Wrapper_Construct::get_Nj_size()
{
    
    for (size_t idx=0; idx<new_data.sup.loads.size(); idx++)
    {
        Nj_size_list.push_back(new_data.sup.loads.at(idx).cblocks.size());
    }
    
    std::sort(Nj_size_list.begin(), Nj_size_list.end());
    size_t Nj_max = Nj_size_list.back();


}

void Wrapper_Construct::get_num_constraints()
{
 // number of constraints from sec 3.1.1
    for (size_t idx=0; idx<I.size(); idx++)
    {
       num_g++;
    }
    // number of constraints from sec 3.1.2
    for (size_t jdx=0; jdx<J_k.size(); jdx++)
    {
        num_g++;
    }
    // number of constraints from sec 3.1.3
    for (size_t kdx=0; kdx<E_k.size(); kdx++)
    {
        num_g++;
    }

}

