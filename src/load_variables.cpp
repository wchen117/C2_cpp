#include <variables/load_variables.hpp>

LoadVariables::LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(10, name)
{
    load_ref_data = data_ptr;

    if (!load_ref_data->J_k.empty())
    {
        size_t size_jk = load_ref_data->J_k.size();
        p_jn_over.resize(size_jk);
        c_jn.resize(size_jk);
        p_jkn.resize(size_jk);
        size_t p_jn_counter = 0;
        
        
        for(size_t idx=0; idx<size_jk; idx++)
        {
            int j_num;
            std::string bus_i;
            std::tie (j_num, bus_i) = load_ref_data->J_k.at(idx);
            
            for (auto load : load_ref_data->new_data.sup.loads)
            {
                if (j_num == load.bus)
                {
                    for (auto cblock: load.cblocks)
                    {
                        p_jn_over.at(idx).push_back(cblock.pmax * load_ref_data->s_tilde_inverse);
                        c_jn.at(idx).push_back(cblock.c * load_ref_data->s_tilde_inverse);
                        p_jkn.at(idx).push_back(0.0);
                        p_jn_counter++;
                    }
                      
                }
            }
            
        }
        SetRows(p_jn_counter);
    }
    else {
        std::cout<<"J_k vector is empty, quit!"<<std::endl;
        exit(0);

    }

}
LoadVariables::~LoadVariables() {}

Eigen::VectorXd LoadVariables::GetValues() const 
{
    if  (GetRows())
    {
        Eigen::VectorXd tmp_x(GetRows());
        size_t num_j = p_jkn.size();
        size_t idx = 0;
        for(auto each_pj : p_jkn)
        {
            size_t each_pj_size = each_pj.size();

            for (auto each_p_jn : each_pj)
            {
                tmp_x(idx) = each_p_jn;
                idx++;
            }
        }

        return tmp_x;
    }
    
}
void LoadVariables::SetVariables(const Eigen::VectorXd &x) 
{
    size_t counter=0;
    for (size_t idx=0; idx<p_jkn.size(); idx++)
    {
        size_t pj_len = p_jkn.at(idx).size();
        for (size_t jdx=0; jdx<pj_len; jdx++)
        {
            p_jkn.at(idx).at(jdx) = x(counter);
            counter++;
        }
    }

}
LoadVariables::VecBound LoadVariables::GetBounds() const 
{
    VecBound load_bounds(GetRows());
    int counter = 0;
    for(auto each_pj : p_jn_over)
        {
            size_t each_pj_size = each_pj.size();

            for (auto each_p_jn : each_pj)
            {
                load_bounds.at(counter).upper_ = each_p_jn;
                load_bounds.at(counter).lower_ = 0.0;
                counter++;
            }
        }
    return load_bounds;

}
